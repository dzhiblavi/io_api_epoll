#ifndef DTHREAD_DTHREAD_H
#define DTHREAD_DTHREAD_H

#include <pthread.h>
#include <functional>
#include <cassert>
#include <thread>

class dthread {
public:
    typedef pthread_t native_handle_type;

private:
    template <typename... Types>
    using decayed_tuple = typename std::tuple<typename std::decay<Types>::type...>;

    template <typename Tuple>
    struct invoker {
        template <typename>
        struct result;
        template <typename F, typename... Args>
        struct result<std::tuple<F, Args...>> : std::__invoke_result<F, Args...> {};

    public:
        Tuple t;

    private:
        template <size_t... ind>
        typename result<Tuple>::type invoke_impl_(std::index_sequence<ind...>) {
            return std::invoke(std::get<ind>(t)...);
        }

    public:
        typename result<Tuple>::type operator()() {
            return invoke_impl_(std::make_index_sequence<std::tuple_size_v<Tuple>>());
        }
    };

    template <typename F, typename... Args>
    static invoker<decayed_tuple<F, Args...>> make_invoker(F&& f, Args&&... args) {
        return { decayed_tuple<F, Args...>(std::forward<F>(f), std::forward<Args>(args)...) };
    }

    struct inv_instance_base {
        virtual ~inv_instance_base() {};
        virtual void run() = 0;
    };

    template <typename C>
    struct inv_instance : inv_instance_base {
    private:
        C func;

    public:
        inv_instance(C&& f)
            : func(std::forward<C>(f))
        {}

        void run() {
            func();
        }
    };

    using inv_instance_ptr = std::unique_ptr<inv_instance_base>;

    template <typename C>
    inv_instance_ptr make_inv_instance(C&& f) {
        return inv_instance_ptr{ new inv_instance<C>(std::forward<C>(f)) };
    }

    static void* thread_run(void* inv_p);

    void start_thread(inv_instance_ptr up);

private:
    native_handle_type tid_ = 0;

public:
    template <typename F, typename... Args
            , typename = std::enable_if_t<std::is_invocable_v<F, Args...>>>
    explicit dthread(pthread_attr_t* attr, F&& func, Args&&... args) {
        start_thread(make_inv_instance(make_invoker(std::forward<F>(func), std::forward<Args>(args)...)));
    }

    template <typename F, typename... Args
            , typename = std::enable_if_t<std::is_invocable_v<F, Args...>>>
    explicit dthread(F&& func, Args&&... args)
        : dthread(nullptr, std::forward<F>(func), std::forward<Args>(args)...)
    {}

    dthread() = default;
    dthread(native_handle_type tid) noexcept;
    dthread(dthread&& t) noexcept;
    dthread& operator=(dthread&& t) noexcept;
    ~dthread();

    void join();
    void detach();
    [[nodiscard]] bool joinable() const noexcept;
    [[nodiscard]] native_handle_type native_handle() const noexcept;
};

#endif //DTHREAD_DTHREAD_H

 #include "getaddrinfo_server.h"

namespace {
std::mutex cerr_m;

#if GACHI_LOGLEVEL > 0
bool errlog_impl_() noexcept {
    try {
        std::cerr << std::endl;
        return false;
    } catch (...) {
        return true;
    }
}

template <typename T, typename... Args>
bool errlog_impl_(T&& t, Args&&... args) noexcept {
    try {
        std::cerr << t << " ";
        return errlog_impl_(std::forward<Args>(args)...);
    } catch (...) {
        return true;
    }
}

template <typename... Args>
bool errlog(Args&&...args) noexcept {
    std::unique_lock<std::mutex> lg(cerr_m);
    try {
        return errlog_impl_(std::forward<Args>(args)...);
    } catch (...) {
        return true;
    }
}
#else
#define errlog(...)
#endif

std::string fail_message(std::string const& hostname, std::string const& why) {
    std::stringstream resstr;
    resstr << "[failed to resolve '" << hostname << "']";
    return resstr.str();
}

std::string form_response(std::string const& host) {
    auto hs = ipv4::address::getaddrinfo(host);

    std::stringstream resstr;
    resstr << host << "::{";
    for (auto it = hs.begin(); it != hs.end(); ++it) {
        resstr << it->to_string();
        if (std::next(it) != hs.end())
            resstr << ", ";
        else
            resstr << "}";
    }
    return resstr.str();
}

#ifdef GACHI_USE_DTHREAD
/*
 * creates instance of dthread with custom stack size
 * stack is allocated on *stack_addr using posix_memalign
 * stack_size_pages is treated as a number of pages, which size is equal to getpagesize()
 *
 * TODO: decrease number of system calls by making attr a static variable
 * */
template <typename F, typename... Args>
dthread make_thread(size_t stack_size_pages, void** stack_addr, F&& f, Args&&... args) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int ps = getpagesize();
    posix_memalign(stack_addr, ps, ps * stack_size_pages);

    if (pthread_attr_setstack(&attr, &stack_addr, ps * 10))
        throw std::runtime_error("failed to change stack_size");

    auto ret = dthread(&attr, std::forward<F>(f), std::forward<Args>(args)...);
    pthread_attr_destroy(&attr);

    return ret;
}
#endif

size_t last_id = 0;
size_t gen_unique_id() {
    return ++last_id;
}

#ifdef TERM_CONTROL
void clear_terminal_screen() {
    if (!cur_term) {
        int result;
        setupterm(nullptr, STDOUT_FILENO, &result);
        if (result <= 0) return;
    }
    putp(tigetstr("clear"));
}
#endif
}

namespace ipv4 {
getaddrinfo_server::client_connection_::worker_thread_::worker_thread_(client_connection_* conn)
    : conn(conn)
    , is_working(false)
    , quit(false)
    , failbit(false)
    , th(
#ifdef GACHI_USE_DTHREAD
    make_thread(GACHI_CONNECTION_THREAD_STACK_SIZE, &stack,
#endif
    [this] {
        for (;;) {
            is_working = false;
            std::unique_lock<std::mutex> lg(tm);
            cv.wait(lg, [this] {
                return quit || !tasks.empty();
            });
            is_working = true;
            if (quit)
                break;

            auto hostname = std::move(tasks.front());
            tasks.pop();
            lg.unlock();

            std::string res;
            try {
                try {
                    res = form_response(hostname);
                } catch (ipv4::error const &e) {
                    res = fail_message(hostname, e.what());
                } catch (...) {
                    res = fail_message(hostname, "unknown reason");
                }
            } catch (...) {
#if GACHI_LOGLEVEL & 1
                errlog("ERROR");
#endif
                failbit = true;
            }

            if (quit)
                break;

            try {
                std::unique_lock<std::mutex> lg_res(rm);
                results += res + "\r\n";

                if (!this->conn->sock.has_on_write()) {
                    this->conn->sock.set_on_write([this] {
                        this->conn->process_write();
                    });
                }
            } catch (...) {
#if GACHI_LOGLEVEL & 1
                errlog("ERROR");
#endif
                failbit = true;
            }
        }
    })
#ifdef GACHI_USE_DTHREAD
    )
#endif
{}

getaddrinfo_server::client_connection_::worker_thread_::~worker_thread_() {
    {
        std::unique_lock<std::mutex> lg(tm);
        quit = true;
//        kill(th.native_handle(), SIGINT);
    }
    cv.notify_one();
    th.join();
#ifdef GACHI_USE_DTHREAD
    free(stack);
#endif
}

void getaddrinfo_server::client_connection_::worker_thread_::add_task(std::string const& hostname) {
    {
        std::unique_lock<std::mutex> lg(tm);
        tasks.push(hostname);
    }
    cv.notify_one();
}

bool getaddrinfo_server::client_connection_::worker_thread_::fail() const noexcept {
    return failbit;
}

void getaddrinfo_server::client_connection_::process_read() {
    try {
#if GACHI_LOGLEVEL & 4
        errlog("on_read()");
#endif
        int r = sock.recv(buff, GACHI_BUFFSIZE);
        if (r < 0) {
            if (errno == EINTR)
                return;
            IPV4_EXC(std::to_string(errno));
        }
#ifdef NET_POLL_POLL
        if (r == 0) {
            std::cerr << "disconnect from read()" << std::endl;
            disconnect();
            return;
        }
#endif

        int start_point = (int)saved_buff.size();
        saved_buff += std::string(buff, buff + r);

        int st = 0;
        for (int i = std::max(0, start_point - 1); i < (int)saved_buff.size() - 1; ++i) {
            if (saved_buff[i] == '\r' && saved_buff[i + 1] == '\n') {
                std::string host(saved_buff.data() + st, saved_buff.data() + i);
#if GACHI_LOGLEVEL & 8
                errlog("adding task: '" + host + "'");
#endif
                w.add_task(host);
                st = i + 2;
            }
        }
        if (st != (int)saved_buff.size()) {
            saved_buff = saved_buff.substr(st);
#if GACHI_LOGLEVEL & 4
            errlog("\033[41mnot full receive\033[0m:\t'", saved_buff, "'");
#endif
        } else {
            saved_buff.clear();
        }

        timr.reset(timer::clock_t::now() + std::chrono::seconds(GACHI_TIMEOUT));
    } catch (std::exception const& e) {
#if GACHI_LOGLEVEL & 1
        failbit |= errlog("on_read() failed:", e.what());
#endif
        reset_buffer();
    } catch (...) {
#if GACHI_LOGLEVEL & 1
        failbit |= errlog("on_read() failed with unknown error");
#endif
        reset_buffer();
    }
}

void getaddrinfo_server::client_connection_::process_write() {
    std::unique_lock<std::mutex> lg(w.rm);
    try {
#if GACHI_LOGLEVEL & 4
        errlog("\033[31mon_write():\033[0m", w.results.size());
#endif
        if (w.results.empty()) {
            sock.set_on_write({});
            return;
        }

        int r = sock.send(w.results.c_str(), w.results.size());

        if (r > 0)
            timr.reset(timer::clock_t::now() + std::chrono::seconds(GACHI_TIMEOUT));

        if (r == (int) w.results.size()) {
            w.results.clear();
            sock.set_on_write({});
        } else if ((r >= 0 && r < (int) w.results.size()) || (r < 0 && errno == EINTR)) {
            r = std::max(r, 0);
            w.results = w.results.substr(r);
#if GACHI_LOGLEVEL & 4
            errlog("\033[41mnot full write\033[0m:\t'", w.results, "'");
#endif
        } else {
            IPV4_EXC(std::to_string(errno));
        }
    } catch (std::exception const& e) {
#if GACHI_LOGLEVEL & 1
        failbit |= errlog("on_write() failed:", e.what());
#endif
        reset_buffer();
    } catch (...) {
#if GACHI_LOGLEVEL & 1
        failbit |= errlog("on_write() failed with unknown error");
#endif
        reset_buffer();
    }
}

void getaddrinfo_server::client_connection_::reset_buffer() noexcept {
    sock.set_on_write({});
}

void getaddrinfo_server::client_connection_::disconnect() {
#if GACHI_LOGLEVEL & 2
    errlog("on_disconnect()");
#endif
    srv->cl.erase(this);
}

getaddrinfo_server::client_connection_::client_connection_(io_api::io_context& ctx, ipv4::getaddrinfo_server *server)
    : unique_id(gen_unique_id())
    , srv(server)
    , sock(server->ssock.accept(
    [this] {
        disconnect();
    },
    [this] {
        process_read();
    }, {}))
    , w(this)
    , timr(&ctx.get_timer(), timer::clock_t::now() + std::chrono::seconds(GACHI_TIMEOUT),
    [this, server, &ctx] {
#if GACHI_LOGLEVEL & 2
        errlog("\033[41mtimer_callback()\033[0m");
#endif
        if (is_idle()) {
            server->cl.erase(this);
        } else {
#if GACHI_LOGLEVEL & 2
            errlog("decided not to break connection");
#endif
            timr.reset(ctx.get_timer(), timer::clock_t::now() + std::chrono::seconds(GACHI_TIMEOUT));
        }
    })
{}

bool getaddrinfo_server::client_connection_::client_connection_::is_idle() const noexcept {
    return !w.is_working;
}

getaddrinfo_server::getaddrinfo_server(io_api::io_context &ctx, const ipv4::endpoint &ep)
    : ssock(ctx, ep
    , [this, &ctx] {
#if GACHI_LOGLEVEL & 2
        errlog("on_connect()");
#endif
        auto cc = new client_connection_(ctx, this);
        cl.emplace(cc, std::unique_ptr<client_connection_>(cc));
    }) {}
}

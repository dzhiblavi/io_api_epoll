#include "dthread.h"

dthread::dthread(native_handle_type tid) noexcept
    : tid_(tid)
{}

void* dthread::thread_run(void* inv_p) {
    inv_instance_ptr pt { static_cast<inv_instance_base*>(inv_p) };
    pt->run();
    return nullptr;
}

void dthread::start_thread(inv_instance_ptr up) {
    if (pthread_create(&tid_, nullptr, thread_run, up.get()))
        throw std::runtime_error("start_thread() failed");
    up.release();
}

dthread::~dthread() {
    assert(!joinable());
}

dthread::dthread(dthread&& t) noexcept {
    std::swap(tid_, t.tid_);
}

dthread& dthread::operator=(dthread&& t) noexcept {
    assert(!joinable());
    std::swap(tid_, t.tid_);
    return *this;
}

void dthread::join() {
    assert(joinable());
    if (pthread_join(tid_, nullptr))
        throw std::runtime_error("failed to join a thread");
    tid_ = 0;
}

void dthread::detach() {
    pthread_detach(tid_);
    tid_ = 0;
}

[[nodiscard]] bool dthread::joinable() const noexcept {
    return tid_ != 0;
}

[[nodiscard]] dthread::native_handle_type dthread::native_handle() const noexcept {
    return tid_;
}


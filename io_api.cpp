//
// dzhiblavi
//

#include "io_api.h"

namespace {
volatile bool* quit = nullptr;

void signal_handler(int signal) {
    assert(quit);
    *quit = true;
}

int api_epoll_create() {
    int efd = epoll_create(IPV4_EPOLL_MAX);
    if (efd < 0)
        IPV4_EXCEPTION(std::to_string(errno));
    return efd;
}

int api_epoll_wait(int efd, epoll_event* data, size_t size, int timeout) {
    int nfd = epoll_wait(efd, data, size, timeout);
//    if (nfd < 0)
//        IPV4_EXCEPTION(std::to_string(errno));
    return nfd;
}

void api_epoll_ctl(int efd, int op, int fd, epoll_event* event) {
    int r = epoll_ctl(efd, op, fd, event);
    if (r < 0)
        IPV4_EXCEPTION(std::to_string(errno));
}
}

namespace io_api {
void io_context::ep_add_(int fd, epoll_event* event) {
    api_epoll_ctl(efd_.fd(), EPOLL_CTL_ADD, fd, event);
}

void io_context::ep_remove_(int fd, epoll_event* event) {
    api_epoll_ctl(efd_.fd(), EPOLL_CTL_DEL, fd, event);
}

void io_context::ep_modify_(int fd, epoll_event* event) {
    api_epoll_ctl(efd_.fd(), EPOLL_CTL_MOD, fd, event);
}

io_context::io_context() {
    efd_ = unique_fd(api_epoll_create());
}

io_context::io_context(io_context&& rhs) noexcept {
    swap(*this, rhs);
}

io_context& io_context::operator=(io_context&& rhs) noexcept {
    swap(*this, rhs);
    return *this;
}

void io_context::exec() {
    quit = &quit_;
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);
    std::signal(SIGPIPE, SIG_IGN);

    std::array<epoll_event, IPV4_EPOLL_MAX> events{};
    for (;;) {
        if (quit_)
            return;

        std::cerr << "wait()" << std::endl;
        int nfd = api_epoll_wait(efd_.fd(), events.data(), events.size(), 1000);
        if (nfd < 0) {
            if (errno == EINTR)
                nfd = 0;
            else
                IPV4_EXC_DEB(std::to_string(nfd));
        }
        std::cerr << "wait() ok" << std::endl;

        for (auto it = events.begin(); it != events.begin() + nfd; ++it)
            static_cast<io_unit *>(it->data.ptr)->callback(it->events);
    }
}

void swap(io_context& a, io_context& b) noexcept {
    std::swap(a.efd_, b.efd_);
}

io_context* io_unit::context() noexcept {
    return ctx_;
}

io_context const* io_unit::context() const noexcept {
    return ctx_;
}

void io_unit::reconf_events(uint32_t events) {
    if (!ctx_)
        return;
    events_ = events;
    epoll_event event{events_, this};
    ctx_->ep_modify_(fd_, &event);
}

io_unit::io_unit(io_api::io_context *ctx, uint32_t events, int fd, io_api::io_unit::callback_t callback)
    : ctx_(ctx)
    , events_(events)
    , fd_(fd)
    , callback_(std::move(callback))
{
    epoll_event event{events_, this};
    ctx_->ep_add_(fd_, &event);
}

io_unit::io_unit(io_api::io_unit&& rhs) noexcept {
    swap(*this, rhs);
}

io_unit& io_unit::operator=(io_api::io_unit&& rhs) noexcept {
    swap(*this, rhs);
    return *this;
}

io_unit::~io_unit() {
    if (!ctx_)
        return;
    epoll_event event{events_, this};
    ctx_->ep_remove_(fd_, &event);
}

void io_unit::callback(uint32_t events) {
    assert(callback_);
    callback_(events);
}

void io_unit::configure_callback(io_api::io_unit::callback_t fn) noexcept {
    callback_.swap(fn);
}

void swap(io_unit& a, io_unit& b) noexcept {
    std::swap(a.ctx_, b.ctx_);
    std::swap(a.events_, b.events_);
    std::swap(a.fd_, b.fd_);
    std::swap(a.callback_, b.callback_);
    a.reconf_events(a.events_);
    b.reconf_events(b.events_);
}
} // namespace io_api

#include "io_api.h"

namespace {
volatile bool* quit = nullptr;
volatile int evn = -1;

void signal_handler(int) {
    if (evn == -1) return;
    ::eventfd_write(evn, 0);
}

void bsignal_handler(int) {
    if (!quit) return;
    *quit = true;
}

int api_epoll_create() {
    int efd = epoll_create(100000);
    if (efd < 0)
        IPV4_EXC(std::to_string(errno));
    return efd;
}

int api_epoll_wait(int efd, epoll_event* data, size_t size, int timeout) {
    return epoll_wait(efd, data, size, timeout);
}

void api_epoll_ctl(int efd, int op, int fd, epoll_event* event) {
    int r = epoll_ctl(efd, op, fd, event);
    if (r < 0)
        IPV4_EXC(std::to_string(errno));
}

void create_notifier(int efd) {
    epoll_event notifier{};
    evn = eventfd(0, 0);
    if (evn < 0)
        IPV4_EXC(std::to_string(errno));
    notifier.events = EPOLLIN;
    notifier.data.fd = evn;
    api_epoll_ctl(efd, EPOLL_CTL_ADD, evn, &notifier);
}
}

namespace io_api {
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
//    std::signal(SIGINT, signal_handler);
//    std::signal(SIGTERM, signal_handler);
    bool quitf = false;
    quit = &quitf;
    std::signal(SIGINT, bsignal_handler);
    std::signal(SIGTERM, bsignal_handler);

//    create_notifier(efd_.fd());
//    unique_fd event_uq(evn);

    std::array<epoll_event, IPV4_EPOLL_MAX> events{};
    for (;;) {
        if (quitf)goto end;
        int nfd = api_epoll_wait(efd_.fd(), events.data(), events.size(), call_and_timeout());
        if (quitf) goto end;

        if (nfd < 0) {
            if (errno == EINTR) {
                goto end;
            } else {
                IPV4_EXC(std::to_string(nfd));
            }
        }

        for (auto it = events.begin(); it != events.begin() + nfd; ++it) {
            if (quitf) goto end;
//            if (it->data.fd == evn) goto end;
            static_cast<io_unit *>(it->data.ptr)->callback(it->events);
        }
    }

end:
    evn = -1;
}

timer& io_context::get_timer() {
    return tm;
}

int io_context::call_and_timeout() {
    if (tm.empty())
        return -1;

    timer::clock_t::time_point now = timer::clock_t::now();
    tm.callback(now);

    if (tm.empty())
        return -1;
    return std::chrono::duration_cast<std::chrono::milliseconds>(tm.top() - now).count();
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

void io_unit::reconfigure_events(uint32_t events) {
    if (!ctx_) return;
    events_ = events;
    epoll_event event{events_, {this}};
    api_epoll_ctl(ctx_->efd_.fd(), EPOLL_CTL_MOD, fd_, &event);
}

io_unit::io_unit(io_api::io_context *ctx, uint32_t events, int fd, io_api::io_unit::callback_t callback)
    : ctx_(ctx)
    , events_(events)
    , fd_(fd)
    , callback_(std::move(callback))
{
    epoll_event event{events_, {this}};
    api_epoll_ctl(ctx_->efd_.fd(), EPOLL_CTL_ADD, fd_, &event);
}

io_unit::io_unit(io_api::io_unit&& rhs) noexcept {
    swap(*this, rhs);
}

io_unit& io_unit::operator=(io_api::io_unit&& rhs) noexcept {
    swap(*this, rhs);
    return *this;
}

io_unit::~io_unit() {
    if (!ctx_) return;
    epoll_event event{events_, {this}};
    api_epoll_ctl(ctx_->efd_.fd(), EPOLL_CTL_DEL, fd_, &event);
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
    a.reconfigure_events(a.events_);
    b.reconfigure_events(b.events_);
}
} // namespace io_api

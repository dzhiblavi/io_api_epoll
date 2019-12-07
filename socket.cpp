#include "socket.h"

namespace {
int sock_create(int domain, int type, int proto) {
    int s = socket(domain, type, proto);
    if (s < 0)
        IPV4_EXC(std::to_string(errno));
    return s;
}

int sock_recv(int sockfd, void* buff, size_t maxlen) {
    return recv(sockfd, buff, maxlen, 0);
}

int sock_send(int sockfd, void const* buff, size_t len) {
    return send(sockfd, buff, len, 0);
}

void sock_connect(int fd, ipv4::endpoint const& ep) {
    sockaddr_in ad{};

    ad.sin_family = AF_INET;
    ad.sin_port = ep.port();
    ad.sin_addr.s_addr = ep.net_addr();

    int r = connect(fd, reinterpret_cast<sockaddr const*>(&ad), sizeof ad);
    if (r < 0)
        IPV4_EXC(std::to_string(errno));
}

void sock_bind(int fd, ipv4::endpoint const& ep) {
    sockaddr_in ad {};

    ad.sin_family = AF_INET;
    ad.sin_port = ep.port();
    ad.sin_addr.s_addr = ep.net_addr();

    int er = bind(fd, reinterpret_cast<sockaddr const*>(&ad), sizeof ad);
    if (er < 0)
        IPV4_EXC(std::to_string(errno));
}

void sock_listen(int fd, int maxq) {
    if (listen(fd, maxq) < 0)
        IPV4_EXC(std::to_string(errno));
}

int sock_accept(int fd) {
    int s = accept4(fd, nullptr, nullptr, SOCK_NONBLOCK);
    if (s < 0)
        IPV4_EXC(std::to_string(errno));
    return s;
}
}

namespace ipv4 {
int basic_socket::recv(void* buff, size_t max_len) {
    return sock_recv(fd_.fd(), buff, max_len);
}

int basic_socket::send(void const* buff, size_t max_len) {
    return sock_send(fd_.fd(), buff, max_len);
}

basic_socket::basic_socket(unique_fd&& fd)
    : fd_(std::move(fd))
{}

basic_socket::basic_socket(endpoint const& ep, bool non_block)
    : fd_(sock_create(AF_INET, SOCK_STREAM | (non_block ? SOCK_NONBLOCK : 0u), 0))
{
    sock_connect(fd_.fd(), ep);
}

uint32_t socket::events_() const noexcept {
    return EPOLLRDHUP
        | (on_read_ ? EPOLLIN : 0)
        | (on_write_ ? EPOLLOUT : 0);
}

std::function<void(uint32_t)> socket::configure_callback_() noexcept {
    return [this](uint32_t flags) {
        bool cur_destroyed = false;
        bool* old_destroyed = destroyed_;
        destroyed_ = &cur_destroyed;
        if ((flags & EPOLLERR)
            || (flags & EPOLLRDHUP)
            || (flags & EPOLLHUP)) {
            this->on_disconnect_();
            if (cur_destroyed)
                return;
        }
        if (flags & EPOLLIN) {
            this->on_read_();
            if (cur_destroyed)
                return;
        }
        if (flags & EPOLLOUT)
            this->on_write_();
        destroyed_ = old_destroyed;
    };
}

socket::socket(io_api::io_context& ctx, unique_fd&& fd, callback_t const& on_disconnect)
    : socket(ctx, std::move(fd), on_disconnect, callback_t{}, callback_t{})
{}

socket::socket(io_api::io_context& ctx, unique_fd&& fd, callback_t on_disconnect
                                                      , callback_t on_read
                                                      , callback_t on_write)
    : basic_socket(std::move(fd))
    , on_disconnect_(std::move(on_disconnect))
    , on_read_(std::move(on_read))
    , on_write_(std::move(on_write))
    , unit_(&ctx, events_(), fd_.fd(), configure_callback_())
    , destroyed_(nullptr)
{}

socket::socket(io_api::io_context& ctx, endpoint const& ep, callback_t const& on_disconnect)
    : socket(ctx, ep, on_disconnect, callback_t{}, callback_t{})
{}

socket::socket(io_api::io_context& ctx, endpoint const& ep, callback_t const& on_disconnect
                                                          , callback_t const& on_read
                                                          , callback_t const& on_write)
        : socket(ctx, unique_fd(sock_create(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)),
                on_disconnect, on_read, on_write)
{
    sock_connect(fd_.fd(), ep);
}

socket::~socket() {
    if (destroyed_ != nullptr)
        *destroyed_ = true;
}

socket::socket(ipv4::socket&& b) noexcept
    : basic_socket(std::move(b.fd_))
    , unit_(std::move(b.unit_))
    , on_disconnect_(std::move(b.on_disconnect_))
    , on_read_(std::move(b.on_read_))
    , on_write_(std::move(b.on_write_))
{
    std::swap(destroyed_, b.destroyed_);
    unit_.configure_callback(configure_callback_());
}

socket& socket::operator=(ipv4::socket&& rhs) noexcept {
    if (this == &rhs)
        return *this;
    swap(*this, rhs);
    return *this;
}

void socket::set_on_read(callback_t on_read) {
    on_read_.swap(on_read);
    unit_.reconfigure_events(events_());
}

void socket::set_on_write(callback_t on_write) {
    on_write_.swap(on_write);
    unit_.reconfigure_events(events_());
}

void swap(socket& a, socket& b) noexcept {
    swap(a.fd_, b.fd_);
    std::swap(a.on_disconnect_, b.on_disconnect_);
    std::swap(a.on_read_, b.on_read_);
    std::swap(a.on_write_, b.on_write_);
    swap(a.unit_, b.unit_);
    std::swap(a.destroyed_, b.destroyed_);
    a.unit_.configure_callback(a.configure_callback_());
    b.unit_.configure_callback(b.configure_callback_());
}

server_socket::server_socket(io_api::io_context& ctx, endpoint const& addr, callback_t on_connected)
    : fd_(sock_create(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0))
    , on_connected_(std::move(on_connected))
    , unit_(&ctx, EPOLLIN, fd_.fd(), [this](uint32_t flags) {
        if (flags == EPOLLIN)
            on_connected_();
    })
{
    sock_bind(fd_.fd(), addr);
    sock_listen(fd_.fd(), SSOCK_MAX_LISTEN);
}

socket server_socket::accept(callback_t const& on_disconnect) {
    int fd = sock_accept(fd_.fd());
    return socket(*unit_.context(), unique_fd(fd), on_disconnect);
}

socket server_socket::accept(callback_t const& on_disconnect
                           , callback_t const& on_read
                           , callback_t const& on_write) {
    int fd = sock_accept(fd_.fd());
    return socket(*unit_.context(), unique_fd(fd), on_disconnect, on_read, on_write);
}
} // namespace ipv4
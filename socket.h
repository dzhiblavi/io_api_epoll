//
// dzhiblavi
//

#ifndef WEB_CRACKER_SOCKET_H
#define WEB_CRACKER_SOCKET_H

#define SSOCK_MAX_LISTEN 20000

#include <functional>
#include <sys/socket.h>
#include <cstring>
#include <cassert>

#include "ipv4_exception.h"
#include "unique_fd.h"
#include "address.h"
#include "io_api.h"

namespace ipv4 {
class basic_socket {
protected:
    unique_fd fd_;

protected:
    explicit basic_socket(unique_fd&&);

public:
    explicit basic_socket(endpoint const& ep);

    basic_socket(basic_socket const&) = delete;
    basic_socket& operator=(basic_socket const&) = delete;

    basic_socket(basic_socket&&) noexcept = default;
    basic_socket& operator=(basic_socket&&) noexcept = default;

    int recv(void* buff, size_t max_len);
    int send(void const* buff, size_t maxlen);
};

class socket : private basic_socket {
    friend class server_socket;

public:
    typedef std::function<void()> callback_t;

private:
    callback_t on_disconnect_;
    callback_t on_read_{};
    callback_t on_write_{};
    io_api::io_unit unit_;
    bool *destroyed_ = nullptr;

private:
    [[nodiscard]] uint32_t events_() const noexcept;
    [[nodiscard]] std::function<void(uint32_t)> configure_callback_() noexcept;

    socket(io_api::io_context& ctx, unique_fd&& fd, callback_t on_disconnect);
    socket(io_api::io_context& ctx, unique_fd&& fd, callback_t on_disconnect
                                                  , callback_t on_read
                                                  , callback_t on_write);
public:
    ~socket();

    socket(socket const&) = delete;
    socket& operator=(socket const&) = delete;

    socket(socket&&) noexcept;
    socket& operator=(socket&&) noexcept;

    void set_on_read(callback_t on_read);
    void set_on_write(callback_t on_write);

    using basic_socket::recv;
    using basic_socket::send;

    static socket connect(io_api::io_context& ctx, endpoint const& ep, callback_t const& on_disconnect);
    friend void swap(socket&, socket&) noexcept;
};

class server_socket {
public:
    typedef std::function<void()> callback_t;

private:
    unique_fd fd_;
    callback_t on_connected_;
    io_api::io_unit unit_;

public:
    server_socket(io_api::io_context& ctx, endpoint const& addr, callback_t on_connect);

    socket accept(callback_t const& on_disconnect);
    socket accept(callback_t const& on_disconnect
                , callback_t const& on_read
                , callback_t const& on_write);
};
} // namespace ipv4

#endif //WEB_CRACKER_SOCKET_H
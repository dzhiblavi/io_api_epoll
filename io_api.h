#ifndef WEB_CRACKER_IO_API_H
#define WEB_CRACKER_IO_API_H

#define IPV4_EPOLL_MAX 2000

#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <functional>
#include <array>
#include <iostream>
#include <cassert>
#include <csignal>

#include "ipv4_exception.h"
#include "unique_fd.h"

namespace io_api {
class io_context {
    friend struct io_unit;

private:
    unique_fd efd_;

public:
    io_context();
    io_context(io_context const&) = delete;
    io_context& operator=(io_context const&) = delete;

    io_context(io_context&&) noexcept;
    io_context& operator=(io_context&&) noexcept;

    void exec();
    friend void swap(io_context&, io_context&) noexcept;
};

struct io_unit {
public:
    typedef std::function<void(uint32_t)> callback_t;

private:
    io_context* ctx_ = nullptr;
    uint32_t events_ = 0;
    int fd_ = -1;
    callback_t callback_{};

public:
    io_unit(io_context* ctx, uint32_t events, int fd, callback_t callback);
    ~io_unit();

    io_unit(io_unit const&) = delete;
    io_unit& operator=(io_unit const&) = delete;

    io_unit(io_unit&&) noexcept;
    io_unit& operator=(io_unit&&) noexcept;

    [[nodiscard]] io_context* context() noexcept;
    [[nodiscard]] io_context const* context() const noexcept;

    void reconfigure_events(uint32_t events);
    void configure_callback(callback_t) noexcept;
    void callback(uint32_t events);

    friend void swap(io_unit&, io_unit&) noexcept;
};
} // namespace io_api

#endif //WEB_CRACKER_IO_API_H

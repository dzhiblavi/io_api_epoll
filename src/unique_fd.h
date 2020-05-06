#ifndef NET_UNIQUE_FD_H
#define NET_UNIQUE_FD_H

#include <unistd.h>
#include <algorithm>
#include <iostream>

class unique_fd {
    int fd_ = -1;

public:
    unique_fd() noexcept = default;
    explicit unique_fd(int fd) noexcept;
    ~unique_fd();

    unique_fd(unique_fd const&) = delete;
    unique_fd& operator=(unique_fd const&) = delete;

    unique_fd(unique_fd&&) noexcept;
    unique_fd& operator=(unique_fd&&) noexcept;

    [[nodiscard]] int native_handle() const noexcept;

    friend void swap(unique_fd&, unique_fd&) noexcept;
};

#endif // NET_UNIQUE_FD_H
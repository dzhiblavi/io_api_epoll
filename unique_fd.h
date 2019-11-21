//
// dzhiblavi
//

#ifndef WEB_CRACKER_UNIQUE_FD_H
#define WEB_CRACKER_UNIQUE_FD_H

#include <unistd.h>
#include <algorithm>

class unique_fd {
    int fd_ = -1;

public:
    unique_fd() noexcept = default;
    unique_fd(int fd) noexcept;
    ~unique_fd();

    unique_fd(unique_fd const&) = delete;
    unique_fd& operator=(unique_fd const&) = delete;

    unique_fd(unique_fd&&) noexcept;
    unique_fd& operator=(unique_fd&&) noexcept;

    [[nodiscard]] int fd() const noexcept;

    friend void swap(unique_fd&, unique_fd&) noexcept;
};

#endif //WEB_CRACKER_UNIQUE_FD_H

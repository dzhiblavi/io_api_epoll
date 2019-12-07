#ifndef WEB_CRACKER_ADDRESS_H
#define WEB_CRACKER_ADDRESS_H

#include <cstdint>
#include <string>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>

#include "ipv4_exception.h"
#include "unique_fd.h"

namespace ipv4 {
struct address {
private:
    uint32_t addr_ = 0;

public:
    address() noexcept = default;
    explicit address(uint32_t) noexcept;
    explicit address(std::string const&);

    [[nodiscard]] uint32_t net_addr() const noexcept;
    [[nodiscard]] static address resolve(std::string const& host);
    [[nodiscard]] static address any() noexcept;
};

struct endpoint {
private:
    uint32_t addr_ = 0;
    uint16_t port_ = 0;

public:
    endpoint() noexcept = default;
    endpoint(uint32_t, uint16_t) noexcept;
    endpoint(std::string const&, uint16_t);
    endpoint(address const&, uint16_t) noexcept;

    [[nodiscard]] uint32_t net_addr() const noexcept;
    [[nodiscard]] uint16_t port() const noexcept;
};
} // namespace ipv4

#endif //WEB_CRACKER_ADDRESS_H

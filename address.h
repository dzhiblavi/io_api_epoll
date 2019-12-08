#ifndef WEB_CRACKER_ADDRESS_H
#define WEB_CRACKER_ADDRESS_H

#include <cstdint>
#include <string>
#include <sys/types.h>
#include <netdb.h>
#include <list>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>

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
    [[nodiscard]] std::string to_string() const;

    [[nodiscard]] static address any() noexcept;
    [[nodiscard]] static address resolve(std::string const& host);
    [[nodiscard]] static std::list<address> getaddrinfo(std::string const& hostname);
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
    [[nodiscard]] std::string to_string() const;
};

std::ostream& operator<<(std::ostream& os, address const& addr);
std::ostream& operator<<(std::ostream& os, endpoint const& ep);
} // namespace ipv4

#endif //WEB_CRACKER_ADDRESS_H

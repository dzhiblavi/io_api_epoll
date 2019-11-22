//
// dzhiblavi
//

#include "address.h"

#include <vector>
#include <sstream>
#include <cstring>

namespace {
uint32_t try_resolve(std::string const& host) {
    hostent* hst = gethostbyname(host.c_str());
    if (hst == nullptr || hst->h_addr == nullptr)
        IPV4_EXC_DEB("failed to resolve: " + host);
    uint32_t ret = 0;
    memcpy((char*)&ret, hst->h_addr, hst->h_length);
    return ret;
}
}

namespace ipv4 {
address::address(uint32_t addr) noexcept
    : addr_(addr)
{}

address::address(std::string const& host)
    : addr_(try_resolve(host))
{}

uint32_t address::net_addr() const noexcept {
    return addr_;
}
address address::resolve(std::string const& host) {
    return address(host);
}

endpoint::endpoint(uint32_t addr, uint16_t port) noexcept
    : addr_(addr)
    , port_(htons(port))
{}

endpoint::endpoint(std::string const& host, uint16_t port)
    : addr_(try_resolve(host))
    , port_(htons(port))
{}

endpoint::endpoint(address const& addr, uint16_t port) noexcept
    : addr_(addr.net_addr())
    , port_(htons(port))
{}

uint32_t endpoint::net_addr() const noexcept {
    return addr_;
}

uint16_t endpoint::port() const noexcept {
    return port_;
}

address address::any() noexcept {
    return address(INADDR_ANY);
}
} // namespace ipv4
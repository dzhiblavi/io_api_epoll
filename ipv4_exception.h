//
// dzhiblavi
//

#ifndef WEB_CRACKER_IPV4_EXCEPTION_H
#define WEB_CRACKER_IPV4_EXCEPTION_H

#include <string>
#include <stdexcept>

#define DEBUG
#define IPV4_EXC_DEB(X) throw ipv4::exception(std::string("IPV4 EXC: ") + X \
                        + " in function: " + __func__ + "(...)" \
                        + " on line: " + std::to_string(__LINE__))

#ifdef DEBUG
#define IPV4_EXCEPTION(X) IPV4_EXC_DEB(X)
#else
#define IPV4_EXCEPTION(X) ipv4::throw_exception(X);
#endif

namespace ipv4 {
class exception : std::runtime_error {
public:
    using std::runtime_error::runtime_error;
    using std::runtime_error::what;
};

void throw_exception(std::string const& what);
} // namespace ipv4

#endif //WEB_CRACKER_IPV4_EXCEPTION_H

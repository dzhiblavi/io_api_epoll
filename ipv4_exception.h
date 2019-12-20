#ifndef WEB_CRACKER_IPV4_EXCEPTION_H
#define WEB_CRACKER_IPV4_EXCEPTION_H

#include <string>
#include <stdexcept>

#define IPV4_EXC(X) throw ipv4::exception(std::string("IPV4 EXC: ") + X \
                        + " in function: " + __func__ + "(...)" \
                        + " on line: " + std::to_string(__LINE__))

namespace ipv4 {
class exception : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
    using std::runtime_error::what;
};
} // namespace ipv4

#endif //WEB_CRACKER_IPV4_EXCEPTION_H

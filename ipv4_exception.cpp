//
// dzhiblavi
//

#include "ipv4_exception.h"

namespace ipv4 {
void throw_exception(std::string const &what) {
    throw exception("IPV4 ERROR: " + what);
}
} // namespace ipv4
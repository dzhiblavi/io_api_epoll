//
// Created by dzhiblavi on 21.11.2019.
//

#include "ipv4_exception.h"

namespace ipv4 {
void throw_exception(std::string const &what) {
    throw exception("IPV4 ERROR: " + what);
}
} // namespace ipv4
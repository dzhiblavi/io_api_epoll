#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include "address.h"
#include "io_api.h"
#include "socket.h"
#include "io_api.h"
#include "http_request.h"

int main() {
    try {
        http_request req("api.vk.com");
        req.set_type("GET /method/users.get?user_id=102352294&access_token=4cbc7ce256bab708102fb44bb37c1def2e81460dd98ef81f8e9c846e2c1e04ead5891742e12a0e88c2b5c&v=5.52");
        req.set_param("Host", "api.vk.com");
        req.set_param("User-agent", "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.97 Safari/537.36");
        std::cout << req.request();
    } catch (ipv4::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
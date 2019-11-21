#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include "address.h"
#include "io_api.h"
#include "basic_socket.h"
#include "io_api.h"

int main() {
    try {
        io_api::io_context ctx;

        ipv4::basic_socket sock = ipv4::basic_socket::connect(ctx, ipv4::endpoint(ipv4::address::resolve("codeforces.com"), 80), []{});

        std::stringstream req;
        req << "GET /profile/dzhiblavi" << " HTTP/1.1\r\n"
            << "Host: codeforces.com\r\n"
            << "\r\n\r\n";
        std::string reqs = req.str();

        char buff[2048];
        int total = 0;

        sock.set_on_read([&]{
            std::cerr << "READ" << std::endl;
            int r = sock.recv(buff, 2048);
            buff[r] = 0;
            std::cout << buff << std::flush;
        });

        sock.set_on_write([&]{
            std::cerr << "WRITE" << std::endl;
            while (total < reqs.size())
                total += sock.send(reqs.data() + total, reqs.size() - total);

            sock.set_on_write(std::function<void()>());
        });

        ctx.exec();
    } catch (ipv4::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
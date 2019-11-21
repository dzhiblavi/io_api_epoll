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

        ipv4::basic_server_socket serv1(ctx, ipv4::endpoint(ipv4::address::any(), 1239), [&serv1]{
            std::cerr << "Server 1: connected" << std::endl;
            serv1.accept([] {
                std::cerr << "Server 1: disconnect" << std::endl;
            });
        });

        ipv4::basic_server_socket serv2(ctx, ipv4::endpoint(ipv4::address::any(), 2239), [&serv2]{
            std::cerr << "Server 2: connected" << std::endl;
            serv2.accept([] {
                std::cerr << "Server 2: disconnect" << std::endl;
            });
        });

        ctx.exec();
    } catch (...) {
        std::cout << "main() failed" << '\n';
    }
    return 0;
}
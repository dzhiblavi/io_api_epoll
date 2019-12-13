#include <string>
#include <iostream>

#include "address.h"
#include "io_api.h"
#include "getaddrinfo_server.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: ./server <port>" << std::endl;
        return 0;
    }
    try {
        io_api::io_context ctx;
        ipv4::getaddrinfo_server server(ctx, ipv4::endpoint(ipv4::address::any(), atoi(argv[1])));
        ctx.exec();
    } catch (ipv4::exception const& e) {
        std::cerr << "main() failed : " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "main() failed" << std::endl;
    }
    return 0;
}
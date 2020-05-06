#include <string>
#include <iostream>

#include "src/address.h"
#include "src/io_api.h"
#include "getaddrinfo_server.h"

int main(int argc, char** argv) {
    WSADATA wsaData;
    int iResult;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    if (argc != 2) {
        std::cerr << "usage: ./server <port>" << std::endl;
        return 1;
    }
    try {
        io_api::io_context ctx;
        ipv4::getaddrinfo_server server(ctx, ipv4::endpoint(ipv4::address::any(), atoi(argv[1])));
        ctx.exec();
    } catch (ipv4::error const& e) {
        std::cerr << "main() failed : " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "main() failed" << std::endl;
    }
    return 0;
}
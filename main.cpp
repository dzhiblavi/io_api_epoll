#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <condition_variable>
#include <arpa/inet.h>

#include "address.h"
#include "io_api.h"
#include "socket.h"
#include "io_api.h"
#include "echo_server.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: ./server <host name>" << std::endl;
        return 0;
    }
    auto list = ipv4::address::getaddrinfo(argv[1]);
    for (auto const& addr : list) {
        std::cout << addr << std::endl;
    }
    return 0;
}
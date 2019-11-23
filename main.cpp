#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include "address.h"
#include "io_api.h"
#include "socket.h"
#include "io_api.h"
#include "echo_server.h"

int main(int argc, char** argv) {
    try {
        io_api::io_context ctx;
        ipv4::echo_server serv(ctx, ipv4::endpoint(ipv4::address::any(), atoi(argv[1])));

        ctx.exec();
    } catch (ipv4::exception const& e) {
        std::cerr << "main() failed: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "main() failed with unknown exception" << std::endl;
    }
    return 0;
}
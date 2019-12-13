#include <fstream>

#include "../gtest/gtest.h"

#include "socket.h"
#include "io_api.h"

TEST(basic, simple1) {
    io_api::io_context ctx;
    io_api::io_context ctx2;
    io_api::io_context ctx3;
    ctx = std::move(ctx2);
    ctx2 = std::move(ctx3);
    swap(ctx, ctx2);
}

TEST(basic, simple2) {
    io_api::io_context ctx;
    for (int i = 0; i < 100; ++i)
        io_api::io_unit unit(&ctx, 0, 0, [](uint32_t) {});
}

//TEST(basic, simple3) {
//    std::ifstream fin("/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/hosts2.txt");
//    if (fin.fail())
//        std::cerr << "failed to open file [simple3]" << std::endl;
//    std::string host;
//    while (fin >> host) {
//        try {
//            auto list = ipv4::address::getaddrinfo(host);
//            std::cout << host << ": {";
//            for (auto it = list.begin(); it != list.end(); ++it)
//                std::cout << *it << (std::next(it) == list.end() ? "}\n" : "\n");
//        } catch (...) {
//            std::cerr << "failed to resolve: " << host << std::endl;
//        }
//    }
//}

TEST(getaddrinfo, single_spam) {
    std::ifstream fin("/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/hosts2.txt");
    if (fin.fail())
        std::cerr << "failed to open file [simple3]" << std::endl;

    ipv4::basic_socket sock(ipv4::endpoint(ipv4::address::any(), 3333));

    std::string host;
    while (fin >> host) {
        auto hhost = host + "\r\n";
        sock.send(hhost.c_str(), hhost.size());
    }
    char buff[65536];
    int cur = 0;
    for (;;) {
        int r = sock.recv(buff + cur, 65536 - cur);
        if (r == 0)
            break;
        cur += r;
    }
    for (int i = 0, st = 0; i < cur - 1; ++i) {
        if (buff[i] == '\r' && buff[i + 1] == '\n') {
            std::string returned(buff + st, buff + i);
            st = i + 2;
            std::cerr << "resolved: " << returned << std::endl;
        }
    }
}

TEST(getaddrinfo, multiple_spam) {
    std::ifstream fin("/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/hosts2.txt");
    if (fin.fail())
        std::cerr << "failed to open file [simple3]" << std::endl;

    std::vector<ipv4::basic_socket> vec;

    std::string host;
    while (fin >> host) {
        auto hhost = host + "\r\n";
        vec.emplace_back(ipv4::endpoint(ipv4::address::any(), 3333));
        vec.back().send(hhost.c_str(), hhost.size());
    }
    char buff[1024];
    for (auto& sock : vec) {
        int cur = 0;
        for (;;) {
            int r = sock.recv(buff + cur, 65536 - cur);
            if (r == 0)
                break;
            cur += r;
        }
        for (int i = 0, st = 0; i < cur - 1; ++i) {
            if (buff[i] == '\r' && buff[i + 1] == '\n') {
                std::string returned(buff + st, buff + i);
                st = i + 2;
                std::cout << "resolved: " << returned << std::endl;
            }
        }
    }
}
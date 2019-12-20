#include <algorithm>
#include <fstream>
#include <mutex>
#include <thread>
#include <atomic>
#include <map>

#include "../gtest/gtest.h"

#include "socket.h"
#include "io_api.h"

#define CLIENT_BUFF_SIZE 128

int max_read = 180;
std::mutex error_log_mutex;

void errlog(std::string const& what) {
    std::unique_lock<std::mutex> lg(error_log_mutex);
    std::cerr << what << std::endl;
}

std::vector<std::string> hosts;

#ifdef GACHI_TEST_GAI_API
std::map<std::string, std::string> hhosts;
#endif

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

TEST(routine, load_file) {
    std::ifstream fin("/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/hosts2.txt");
    if (fin.fail())
        std::cerr << "failed to open file [simple3]" << std::endl;
    std::string host;
    int k = 0;
    while (fin >> host && k < max_read) {
        ++k;
        hosts.push_back(host);
    }
}

#ifdef GACHI_TEST_GAI_API
TEST(basic, getaddrinfo_api) {
    std::ifstream fin("/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/hosts2.txt");
    if (fin.fail())
        std::cerr << "failed to open file [simple3]" << std::endl;
    int k = 0;
    while (k < max_read) {
        ++k;
        try {
            auto list = ipv4::address::getaddrinfo(hosts[k]);
            std::vector<std::string> vec;
            for (auto const& ad : list)
                vec.push_back(ad.to_string());
            sort(vec.begin(), vec.end());
            std::stringstream ss;
            ss << "{";
            for (auto it = vec.begin(); it != vec.end(); ++it)
                ss << *it << (std::next(it) == vec.end() ? "}" : ", ");
            hhosts[hosts[k]] = ss.str();
        } catch (...) {
//            std::cerr << "failed to resolve: " << host << std::endl;
        }
    }
}
#endif

std::thread create_spammer(std::mutex& fm, int& fmk, int part, std::atomic_int& total) {
    return std::thread([&fm, &fmk, part, &total] {
        try {
            // send
            std::vector<std::string> lhosts(part);
            {
                std::unique_lock<std::mutex> lg(fm);
                for (int i = 0; i < part; ++i)
                    lhosts[i] = hosts[fmk++] + "\r\n";
            }
            ipv4::basic_socket sock(ipv4::endpoint(ipv4::address::any(), 3333));
            for (auto const &host : lhosts)
                // hope that all hostname would be sent
                sock.send(host.c_str(), host.size());

            // receive
            char buff[CLIENT_BUFF_SIZE];
            int n = 0;
            int offset = 0;
            while (n < part) {
                int r = sock.recv(buff + offset, CLIENT_BUFF_SIZE - offset);
                buff[offset + r] = '\0';
                if (r == 0)
                    break;
                if (r < 0)
                    continue;
                int st = 0;
                for (int i = 0; i < offset + r - 1; ++i) {
                    if (buff[i] == '\r' && buff[i + 1] == '\n') {
                        std::string returned(buff + st, buff + i);
//                            errlog("resolved: " + returned);
                        if (returned[0] != '[') {
                            std::string hm, res;
                            int j = 0;
                            while (!(returned[j] == ':' && returned[j + 1] == ':')) {
                                ++j;
                            }
                            hm = std::string(returned.data(), returned.data() + j);
                            res = returned.substr(j + 2);
//                                errlog("parsed: " + hm + "->" + res);
//                                EXPECT_EQ(hhosts[hm], res);
                        }
                        st = i + 2;
                        ++n;
                        ++total;
                    }
                }
                if (st != offset + r) {
                    errlog("\033[41mNONFULL RECEIVE\033[0m");
                    std::memmove(buff, buff + st, offset + r - st);
                    offset = offset + r - st;
                } else {
                    offset = 0;
                }
            }
        } catch (ipv4::exception const& e) {
            errlog(e.what());
        }
    });
}

void random_spam(int nconnections) {
    std::mutex fm;
    int fmk = 0;
    std::vector<std::thread> t;
    int nt = 0;
    std::atomic_int total(0);
    int part_size = max_read / nconnections;
    for (int cn = 0; cn < nconnections; ++cn) {
        t.emplace_back(create_spammer(fm, fmk, part_size, total));
        nt += part_size;
    }
    for (auto& th : t)
        th.join();
    EXPECT_EQ(part_size * nconnections, total.load());
}

TEST(getaddrinfo, different_uniform_spam) {
    for (int i = 1; i <= max_read; i += 4) {
        errlog("\033[43mstarting\033[0m:\t" + std::to_string(i));
        random_spam(i);
    }
}

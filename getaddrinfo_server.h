#ifndef WEB_CRACKER_GETADDRINFO_SERVER_H
#define WEB_CRACKER_GETADDRINFO_SERVER_H

#include <thread>
#include <mutex>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <condition_variable>

#include "address.h"
#include "io_api.h"
#include "socket.h"
#include "timer.h"

namespace ipv4 {
class getaddrinfo_server {
    struct client_connection_;

public:
    server_socket ssock;
    std::map<client_connection_*, std::unique_ptr<client_connection_>> cl;

public:
    getaddrinfo_server(io_api::io_context&, endpoint const&);
};

struct getaddrinfo_server::client_connection_ {
    struct worker_thread_ {
        typedef std::string result_t;

    public:
        explicit worker_thread_(client_connection_*);
        ~worker_thread_();

        void add_task(std::string const&);
        bool fail() const noexcept;

    public:
        std::queue<std::string> tasks;
        result_t results;

        client_connection_* conn;
        bool quit;
        bool failbit;
        std::condition_variable cv;
        std::mutex tm;
        std::mutex rm;
        std::thread th;
    };

    explicit client_connection_(io_api::io_context& ctx, getaddrinfo_server*);

    socket sock;
    worker_thread_ w;
    timer_unit timer;
};
}

#endif //WEB_CRACKER_GETADDRINFO_SERVER_H

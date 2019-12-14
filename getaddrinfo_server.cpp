#include "getaddrinfo_server.h"

namespace {
std::string fail_message(std::string const& hostname, std::string const& why) {
    std::stringstream resstr;
    resstr << "[failed to resolve : "
           << why << "]: '" << hostname << "'\n";
    return resstr.str();
}

std::string form_response(std::list<ipv4::address> const& hs) {
    std::stringstream resstr;
    resstr << "{";
    for (auto it = hs.begin(); it != hs.end(); ++it) {
        resstr << it->to_string();
        if (std::next(it) != hs.end())
            resstr << ", ";
        else
            resstr << "}\n";
    }
    return resstr.str();
}
}

namespace ipv4 {
getaddrinfo_server::client_connection_::worker_thread_::worker_thread_(client_connection_* conn)
    : conn(conn)
    , quit(false)
    , failbit(false)
    , th(
    [this] {
        for (;;) {
            std::unique_lock<std::mutex> lg(tm);
            cv.wait(lg, [this] {
                return quit || !tasks.empty();
            });
            if (quit)
                break;

            auto hostname = std::move(tasks.front());
            tasks.pop();
            lg.unlock();

            std::string res;
            try {
                res = form_response(address::getaddrinfo(hostname));
            } catch (ipv4::exception const &e) {
                res = fail_message(hostname, e.what());
            } catch (...) {
                res = fail_message(hostname, "unknown reason");
            }

            if (quit)
                break;

            try {
                {
                    std::unique_lock<std::mutex> lg_res(rm);
                    results += res + "\r\n";
                }

                if (!this->conn->sock.has_on_write()) {
                    this->conn->sock.set_on_write([this] {
                        std::cerr << "\033[31mon_write():\033[0m" << results.size() << std::endl;

                        if (results.empty()) {
                            std::unique_lock<std::mutex> lg(rm);
                            this->conn->sock.set_on_write({});
                            return;
                        }

                        int r = this->conn->sock.send(results.c_str(), results.size());
                        if (r == (int) results.size()) {
                            std::unique_lock<std::mutex> lg(rm);
                            results.clear();
                            this->conn->sock.set_on_write({});
                        } else if ((r >= 0 && r < (int) results.size()) || (r < 0 && errno == EINTR)) {
                            r = std::max(r, 0);
                            std::unique_lock<std::mutex> lg(rm);
                            results = results.substr(r);
                        } else {
                            IPV4_EXC(std::to_string(errno));
                        }
                    });
                }
            } catch (...) {
                // doing nothing about this; let client repeat his request
                failbit = true;
            }
        }
    })
{}

getaddrinfo_server::client_connection_::worker_thread_::~worker_thread_() {
    {
        std::unique_lock<std::mutex> lg(tm);
        quit = true;
        kill(th.native_handle(), SIGINT);
    }
    cv.notify_one();
    th.join();
}

void getaddrinfo_server::client_connection_::worker_thread_::add_task(std::string const& hostname) {
    {
        std::unique_lock<std::mutex> lg(tm);
        tasks.push(hostname);
    }
    cv.notify_one();
}

bool getaddrinfo_server::client_connection_::worker_thread_::fail() const noexcept {
    return failbit;
}


getaddrinfo_server::client_connection_::client_connection_(io_api::io_context& ctx, ipv4::getaddrinfo_server *server)
    : sock(server->ssock.accept(
    [this, server] {
        std::cerr << "on_disconnect()" << std::endl;
        server->cl.erase(this);
    },
    [this, &ctx] {
        std::cerr << "on_read()" << std::endl;
        char buff[1024] = {0};
        int r = sock.recv(buff, 1024);
        if (r < 0) {
            if (errno == EINTR)
                return;
            IPV4_EXC(std::to_string(errno));
        }

        int st = 0;
        for (int i = 0; i < r - 1; ++i) {
            if (buff[i] == '\r' && buff[i + 1] == '\n') {
                std::string host(buff + st, buff + i);
                std::cerr << "adding task: '" << host << "'" << std::endl;
                w.add_task(std::string(buff + st, buff + i));
                st = i + 2;
            }
        }
        timer.reset(ctx.get_timer(), timer::clock_t::now() + std::chrono::seconds(10));
    }, {}))
    , w(this)
    , timer(&ctx.get_timer(), timer::clock_t::now() + std::chrono::seconds(10), [this, server]{
        std::cerr << "timer called()" << std::endl;
        server->cl.erase(this);
    })
{}

getaddrinfo_server::getaddrinfo_server(io_api::io_context &ctx, const ipv4::endpoint &ep)
    : ssock(ctx, ep
            , [this, &ctx] {
                std::cerr << "on_connect()" << std::endl;
                auto cc = new client_connection_(ctx, this);
                cl.emplace(cc, std::unique_ptr<client_connection_>(cc));
            })
{}
}
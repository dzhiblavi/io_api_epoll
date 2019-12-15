#include "getaddrinfo_server.h"

namespace {
std::mutex error_log_mutex;

#ifdef DEBUG
void errlog(std::string const& what) {
    std::unique_lock<std::mutex> lg(error_log_mutex);
    std::cerr << what << std::endl;
}
#else
#define errlog
#endif

std::string fail_message(std::string const& hostname, std::string const& why) {
    std::stringstream resstr;
//    resstr << "[failed to resolve : "
//           << why << "]: '" << hostname << "'";
    resstr << "[failed to resolve '" << hostname << "']";
    return resstr.str();
}

std::string form_response(std::string const& host) {
    auto hs = ipv4::address::getaddrinfo(host);

//    std::vector<std::string> vec;
//    for (auto const& ad : hs)
//        vec.push_back(ad.to_string());
//    sort(vec.begin(), vec.end());
//
//    std::stringstream resstr;
//    resstr << host << "::{";
//    for (auto it = vec.begin(); it != vec.end(); ++it) {
//        resstr << *it;
//        if (std::next(it) != vec.end())
//            resstr << ", ";
//        else
//            resstr << "}";
//    }

    std::stringstream resstr;
    resstr << host << "::{";
    for (auto it = hs.begin(); it != hs.end(); ++it) {
        resstr << it->to_string();
        if (std::next(it) != hs.end())
            resstr << ", ";
        else
            resstr << "}";
    }
    return resstr.str();
}
}

namespace ipv4 {
getaddrinfo_server::client_connection_::worker_thread_::worker_thread_(client_connection_* conn)
        : conn(conn)
        , is_working(false)
        , quit(false)
        , failbit(false)
        , th(
        [this] {
            for (;;) {
                is_working = false;
                std::unique_lock<std::mutex> lg(tm);
                cv.wait(lg, [this] {
                    return quit || !tasks.empty();
                });
                is_working = true;
                if (quit)
                    break;

                auto hostname = std::move(tasks.front());
                tasks.pop();
                lg.unlock();

                std::string res;
                try {
                    res = form_response(hostname);
                } catch (ipv4::exception const &e) {
                    res = fail_message(hostname, e.what());
                } catch (...) {
                    res = fail_message(hostname, "unknown reason");
                }

                if (quit)
                    break;

                try {
                    std::unique_lock<std::mutex> lg_res(rm);
                    results += res + "\r\n";

                    if (!this->conn->sock.has_on_write()) {
                        this->conn->sock.set_on_write([this] {
                            this->conn->process_write();
                        });
                    }
                } catch (...) {
                    // doing nothing about this; let client repeat his request
                    errlog("ERROR");
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


void getaddrinfo_server::client_connection_::process_read(timer& tm) {
//    errlog("on_read()");
    int r = sock.recv(buff + offset, GETADDRINFO_BUFSIZE - offset);
    if (r < 0) {
        if (errno == EINTR)
            return;
        IPV4_EXC(std::to_string(errno));
    }

    int st = 0;
    for (int i = 0; i < offset + r - 1; ++i) {
        if (buff[i] == '\r' && buff[i + 1] == '\n') {
            std::string host(buff + st, buff + i);
//            errlog("adding task: '" + host + "'");
            w.add_task(host);
            st = i + 2;
        }
    }
    if (st != offset + r) {
        errlog("\033[41mNOT FULL RECEIVE\033[0m:\t" + std::string(buff + st, buff + offset + r));
        std::memmove(buff, buff + st, offset + r - st);
        offset = offset + r - st;
    } else {
        offset = 0;
    }
    timr.reset(tm, timer::clock_t::now() + std::chrono::seconds(GETADDRINFO_TIMEOUT));
}

void getaddrinfo_server::client_connection_::process_write() {
    std::unique_lock<std::mutex> lg(w.rm);

//    errlog("\033[31mon_write():\033[0m" + std::to_string(w.results.size()));
    if (w.results.empty()) {
        sock.set_on_write({});
        return;
    }

    int r = sock.send(w.results.c_str(), w.results.size());
    if (r == (int)w.results.size()) {
        w.results.clear();
        sock.set_on_write({});
    } else if ((r >= 0 && r < (int)w.results.size()) || (r < 0 && errno == EINTR)) {
        r = std::max(r, 0);
        w.results = w.results.substr(r);
    } else {
        IPV4_EXC(std::to_string(errno));
    }
}

getaddrinfo_server::client_connection_::client_connection_(io_api::io_context& ctx, ipv4::getaddrinfo_server *server)
        : offset(0)
        , sock(server->ssock.accept(
        [this, server] {
//            errlog("on_disconnect()");
            server->cl.erase(this);
        },
        [this, &ctx] {
            process_read(ctx.get_timer());
        }, {}))
        , w(this)
        , timr(&ctx.get_timer(), timer::clock_t::now()
            + std::chrono::seconds(GETADDRINFO_TIMEOUT),
        [this, server] {
            errlog("\033[41mtimer_callback()\033[0m");
            if (is_idle())
                server->cl.erase(this);
        })
{}

bool getaddrinfo_server::client_connection_::client_connection_::is_idle() {
    return !w.is_working && !sock.has_on_write() && offset == 0;
}

getaddrinfo_server::getaddrinfo_server(io_api::io_context &ctx, const ipv4::endpoint &ep)
        : ssock(ctx, ep
        , [this, &ctx] {
//            errlog("on_connect()");
            auto cc = new client_connection_(ctx, this);
            cl.emplace(cc, std::unique_ptr<client_connection_>(cc));
        })
{}
}
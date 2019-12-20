#include "getaddrinfo_server.h"

namespace {
std::mutex cerr_m;

#if GACHI_LOGLEVEL > 0
void errlog_impl_() {
    std::cerr << std::endl;
}

template <typename T, typename... Args>
void errlog_impl_(T&& t, Args&&... args) {
    std::cerr << t << " ";
    errlog_impl_(std::forward<Args>(args)...);
}

template <typename... Args>
void errlog(Args&&...args) {
    std::unique_lock<std::mutex> lg(cerr_m);
    errlog_impl_(std::forward<Args>(args)...);
}
#else
#define errlog(...)
#endif

std::string fail_message(std::string const& hostname, std::string const& why) {
    std::stringstream resstr;
    resstr << "[failed to resolve '" << hostname << "']";
    return resstr.str();
}

std::string form_response(std::string const& host) {
    auto hs = ipv4::address::getaddrinfo(host);

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

#ifdef GACHI_USE_DTHREAD
template <typename F, typename... Args>
dthread make_thread(size_t stack_size_pages, void** stack_addr, F&& f, Args&&... args) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int ps = getpagesize();
    posix_memalign(stack_addr, ps, ps * stack_size_pages);

    if (pthread_attr_setstack(&attr, &stack_addr, ps * 10))
        throw std::runtime_error("failed to change stack_size");

    auto ret = dthread(&attr, std::forward<F>(f), std::forward<Args>(args)...);
    pthread_attr_destroy(&attr);

    return ret;
}
#endif
}

namespace ipv4 {
getaddrinfo_server::client_connection_::worker_thread_::worker_thread_(client_connection_* conn)
        : conn(conn)
        , is_working(false)
        , quit(false)
        , failbit(false)
        , th(
#ifdef GACHI_USE_DTHREAD
        make_thread(GACHI_CONNECTION_THREAD_STACK_SIZE, &stack,
#endif
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
                    try {
                        res = form_response(hostname);
                    } catch (ipv4::exception const &e) {
                        res = fail_message(hostname, e.what());
                    } catch (...) {
                        res = fail_message(hostname, "unknown reason");
                    }
                } catch (...) {
    #if GACHI_LOGLEVEL & 1
                    errlog("ERROR");
    #endif
                    failbit = true;
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
    #if GACHI_LOGLEVEL & 1
                    errlog("ERROR");
    #endif
                    failbit = true;
                }
            }
        })
#ifdef GACHI_USE_DTHREAD
    )
#endif
{}

getaddrinfo_server::client_connection_::worker_thread_::~worker_thread_() {
    {
        std::unique_lock<std::mutex> lg(tm);
        quit = true;
        kill(th.native_handle(), SIGINT);
    }
    cv.notify_one();
    th.join();
#ifdef GACHI_USE_DTHREAD
    free(stack);
#endif
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
#if GACHI_LOGLEVEL & 4
    errlog("on_read()");
#endif
    int r = sock.recv(buff + offset, GACHI_BUFFSIZE - offset);
    if (r < 0) {
        if (errno == EINTR)
            return;
        IPV4_EXC(std::to_string(errno));
    }

    int st = 0;
    for (int i = 0; i < offset + r - 1; ++i) {
        if (buff[i] == '\r' && buff[i + 1] == '\n') {
            std::string host(buff + st, buff + i);
#if GACHI_LOGLEVEL & 8
            errlog("adding task: '" + host + "'");
#endif
            w.add_task(host);
            st = i + 2;
        }
    }
    if (st != offset + r) {
#if GACHI_LOGLEVEL & 4
        errlog("\033[41mnot full receive\033[0m:\t", std::string(buff + st, buff + offset + r));
#endif
        std::memmove(buff, buff + st, offset + r - st);
        offset = offset + r - st;
    } else {
        offset = 0;
    }
    timr.reset(tm, timer::clock_t::now() + std::chrono::seconds(GACHI_TIMEOUT));
}

void getaddrinfo_server::client_connection_::process_write() {
    std::unique_lock<std::mutex> lg(w.rm);

#if GACHI_LOGLEVEL & 4
    errlog("\033[31mon_write():\033[0m", w.results.size());
#endif
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
#if GACHI_LOGLEVEL & 2
                    errlog("on_disconnect()");
#endif
                    server->cl.erase(this);
                },
                [this, &ctx] {
                    process_read(ctx.get_timer());
                }, {}))
        , w(this)
        , timr(&ctx.get_timer(), timer::clock_t::now()
                                 + std::chrono::seconds(GACHI_TIMEOUT),
               [this, server] {
#if GACHI_LOGLEVEL & 2
                   errlog("\033[41mtimer_callback()\033[0m");
#endif
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
#if GACHI_LOGLEVEL & 2
            errlog("on_connect()");
#endif
            auto cc = new client_connection_(ctx, this);
            cl.emplace(cc, std::unique_ptr<client_connection_>(cc));
        })
{}
}
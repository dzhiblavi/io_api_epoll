//
// dzhiblavi
//

#include "echo_server.h"

namespace ipv4 {
echo_server::echo_server(io_api::io_context& ctx, const ipv4::endpoint& ep)
    : ssock_(ctx, ep, [this] {
        auto conn = new client_conn_(this);
        con_.insert({conn, std::unique_ptr<client_conn_>(conn)});
    })
{}

echo_server::client_conn_::client_conn_(echo_server* es)
    : csock_(es->ssock_.accept(
            [es, this] {
                std::cerr << "on_disconnect()" << std::endl;
                es->con_.erase(this);
            }
            , [this] {
                std::cerr << "on_read()" << std::endl;
                size_ = 0;
                for (;;) {
                    std::cerr << "A" << std::endl;
                    int r = csock_.recv(buff + size_, 1024 - size_);
                    std::cerr << "B" << std::endl;

                    std::cerr << r << std::endl;
                    if (r == 0 || (r < 0 && errno == EWOULDBLOCK)) {
                        if (r < 0)
                            std::cerr << "on_read() EWOULDBLOCK" << std::endl;
                        sent_ = 0;
                        csock_.set_on_write([this] {
                            std::cerr << "on_write()" << std::endl;
                            for (;;) {
                                int rr = csock_.send(buff + sent_, 1024 - sent_);

                                if (rr == 0 || (rr < 0 && errno == EWOULDBLOCK)) {
                                    if (rr < 0)
                                        std::cerr << "on_write() EWOULDBLOCK" << std::endl;
                                    csock_.set_on_write(std::function<void()>());
                                    return;
                                } else if (rr < 0) {
                                    IPV4_EXC_DEB(std::to_string(errno));
                                }
                                sent_ += rr;
                            }
                        });
                        return;
                    } else if (r < 0) {
                        IPV4_EXC_DEB(std::to_string(errno));
                    }
                    size_ += r;
                }
            }
            , std::function<void()>()))
{}
}
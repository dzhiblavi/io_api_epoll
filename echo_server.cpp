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
                size_ = csock_.recv(buff, 1024);
                csock_.set_on_write([this] {
                    std::cerr << "on_write()" << std::endl;
                    csock_.send(buff, size_);
                    size_ = 0;
                    csock_.set_on_write(std::function<void()>());
                });
            }
            , std::function<void()>()))
{}
}
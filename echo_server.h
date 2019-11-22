//
// dzhiblavi
//

#ifndef WEB_CRACKER_ECHO_SERVER_H
#define WEB_CRACKER_ECHO_SERVER_H

#include <map>
#include <vector>
#include <memory>

#include "basic_socket.h"

namespace ipv4 {
class echo_server {
    struct client_conn_;
    friend struct client_conn_;
    std::map<client_conn_*, std::unique_ptr<client_conn_>> con_;

private:
    basic_server_socket ssock_;

public:
    echo_server(io_api::io_context&, endpoint const&);
};

struct echo_server::client_conn_ {
private:
    char buff[1024] = {0};
    size_t size_ = 0;
    basic_socket csock_;

public:
    explicit client_conn_(echo_server*);
};
} // namespace ipv4

#endif //WEB_CRACKER_ECHO_SERVER_H

//
// dzhiblavi
//

#ifndef WEB_CRACKER_HTTP_REQUEST_H
#define WEB_CRACKER_HTTP_REQUEST_H

#include <string>
#include <map>
#include <sstream>

#include "socket.h"
#include "io_api.h"

class http_request {
    std::string type_;
    std::vector<std::pair<std::string, std::string>> parms_;
    ipv4::basic_socket sock_;
    int sent_ = 0;

private:
    std::string form_request_();

public:
    explicit http_request(std::string const& url);
    void set_type(std::string const& type);

    void set_param(std::string const& name, std::string const& value);

    std::string request();
};

#endif //WEB_CRACKER_HTTP_REQUEST_H

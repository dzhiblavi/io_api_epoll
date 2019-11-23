//
// dzhiblavi
//

#include "http_request.h"

http_request::http_request(std::string const& url)
    : sock_(ipv4::basic_socket(ipv4::endpoint(ipv4::address::resolve(url), 80)))
{}

void http_request::set_type(std::string const& type) {
    type_ = type;
}

void http_request::set_param(std::string const& name, std::string const& value) {
    parms_.emplace_back(name, value);
}

std::string http_request::form_request_() {
    std::stringstream ss;
    ss << type_ << " HTTP/1.1\r\n";
    for (auto const& p : parms_)
        ss << p.first << ": " << p.second << "\r\n";
    ss << "\r\n";
    return ss.str();
}

std::string http_request::request() {
    sent_ = 0;
    std::string req = form_request_();
    std::cerr << req << std::endl;
    std::string resp;
    while (sent_ < req.size())
        sent_ += sock_.send(req.data() + sent_, req.size() - sent_);

    char buff[1024];
    for (;;) {
        int r = sock_.recv(buff, 1024);
        if (r == 0)
            break;
        resp += std::string(buff, buff + r);
    }
    return resp;
}


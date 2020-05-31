#ifndef SERVER_HPP
#define SERVER_HPP

#include "client.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class HTTPServer {
public:
    HTTPServer(std::string address, std::string port):
    _address(std::move(address)),
    _port(std::move(port))
    {}

    void start_server();

private:
    std::string _address;
    std::string _port;

    void connection_loop(tcp::acceptor& acceptor, tcp::socket& socket);
};

#endif
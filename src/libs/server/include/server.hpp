#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include "../../client/include/client.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class HTTPServer {
public:
    HTTPServer(std::string address, std::string port): _address(std::move(address)), _port(std::move(port)) {}
    void start_server();

private:
    std::string _address;
    std::string _port;

    void ConnectionLoop(tcp::acceptor& acceptor, tcp::socket& socket);
};


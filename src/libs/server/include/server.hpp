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
    static HTTPServer& Instance();
    void start_server(const std::string _address, const std::string _port);

private:
    HTTPServer();
    void ConnectionLoop(tcp::acceptor& acceptor, tcp::socket& socket);
};


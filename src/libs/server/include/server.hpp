#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <regex>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include "index_controller.hpp"
#include "unit_of_work.hpp"
#include "../../controllers/include/get_profile_controller.hpp"
#include "../../serialize/include/serialize.hpp"
#include "../../models/include/profile.hpp"
#include "client.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class HTTPServer {
public:
    HTTPServer(std::string address, std::string port): _address(std::move(address)), _port(std::move(port)) {}

    void start_server() {
        try {
            auto const address = net::ip::make_address(_address);
            auto const port = static_cast<unsigned short>(std::stoi(_port));

            net::io_context io_context{1};

            tcp::acceptor acceptor{io_context, {address, port}};
            tcp::socket socket{io_context};

            connection_loop(acceptor, socket);

            io_context.run();

        } catch (std::exception const &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

private:
    std::string _address;
    std::string _port;

    void connection_loop(tcp::acceptor& acceptor, tcp::socket& socket) {
        acceptor.async_accept(socket,
                              [&](beast::error_code ec) {
                                  if(!ec)
                                      std::make_shared<HTTPClient>(std::move(socket))->start();
                                  connection_loop(acceptor, socket);
                              });
    }
};

#endif
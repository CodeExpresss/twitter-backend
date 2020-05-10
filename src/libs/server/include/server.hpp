#ifndef SERVER_HPP
#define SERVER_HPP

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
#include "index_controller.hpp"
#include "unit_of_work.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class HTTPClient : public std::enable_shared_from_this<HTTPClient> {
public:
    HTTPClient(tcp::socket socket) : socket(std::move(socket)) {}

    void start();

    static std::shared_ptr<UnitOfWork> worker;

private:
    tcp::socket socket; //сокет для подключения конкретного клиента
    beast::flat_buffer buffer{8192}; //буфер для чтения данных

    http::request<http::dynamic_body> request; //объект запроса
    http::response<http::dynamic_body> response; //объект ответа

    //таймер для "протухания" соеденений
    net::steady_timer deadline_{
            socket.get_executor(), std::chrono::seconds(60)};

    HTTPClient(const HTTPClient&) = delete;
    HTTPClient(const HTTPClient&&) = delete;
    HTTPClient&operator= (const HTTPClient&) = delete;
    HTTPClient&operator= (HTTPClient&&) = delete;

    void read_request();

    // Метод для обработки запроса
    void process_request();

    // Создание ответа, здесь должен быть реализован роутинг
    void routing();

    // записать ответ в сокет
    void write_response();

    // Проверить время подключения
    void check_deadline();
};

std::shared_ptr<UnitOfWork> HTTPClient::worker = make_shared<UnitOfWork>();

void HTTPClient::start() {
    read_request();
    check_deadline();
}

void HTTPClient::read_request() {
    auto self = shared_from_this();

    http::async_read(
            socket,
            buffer,
            request,
            [self](beast::error_code ec,
                   std::size_t bytes_transferred) {
                boost::ignore_unused(bytes_transferred);
                if(!ec)
                    self->process_request();
            });
}

void HTTPClient::process_request() {
    response.version(request.version());
    response.keep_alive(false);

    switch (request.method()) {
        case http::verb::get:
            response.result(http::status::ok);
            routing();
            break;
        case http::verb::post:
            break;
        default:
            // неопределённый метод запроса
            response.result(http::status::bad_request);
            response.set(http::field::content_type, "text/plain");
            beast::ostream(response.body())
                    << "Invalid request-method '"
                    << std::string(request.method_string())
                    << "'";
            break;
    }
    write_response();
}

void HTTPClient::routing() {
    if (request.target() == "/echo") {
        response.set(http::field::content_type, "text/html");
        beast::ostream(response.body())
                << request.method() << "\n"
                << request.target() << "\n";
    } else if (request.target() == "/api/user/register/") {
        return;

    } else if (request.target() == "/api/user/login/") {
        return;

    } else if (request.target() == "/api/user/current/") {
        return;

    } else if (request.target() == "/api/user/update/") {
        return;

    } else if (request.target() == "/api/profile/current/") {
        std::shared_ptr<ProfileController> p_cont = make_shared<ProfileController>(worker);
        p_cont->get_queryset();
        return;

    } else if (request.target() == "/api/profile/update/") {
        return;

    } else if (request.target() == "/api/tweet/index/") {

        return;

    } else if (request.target() == "/api/tweet/create/") {
        return;

    } else if (request.target() == "/api/tweet/vote/") {
        return;

    } else {
        response.result(http::status::not_found);
        response.set(http::field::content_type, "text/plain");
        beast::ostream(response.body()) << "File not found\r\n";
    }
}

void HTTPClient::write_response() {
    auto self = shared_from_this();

    response.set(http::field::content_length, response.body().size());

    http::async_write(
            socket,
            response,
            [self](beast::error_code ec, std::size_t) {
                self->socket.shutdown(tcp::socket::shutdown_send, ec);
                self->deadline_.cancel();
            });
}

void HTTPClient::check_deadline() {
    auto self = shared_from_this();

    deadline_.async_wait(
            [self](beast::error_code ec) {
                if(!ec) {
                    self->socket.close(ec);
                }
            });
}

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

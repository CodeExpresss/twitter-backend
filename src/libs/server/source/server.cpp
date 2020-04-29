#include "server.hpp"

void HTTPServer::connection_loop(tcp::acceptor& acceptor, tcp::socket& socket) {
    acceptor.async_accept(socket,
                          [&](beast::error_code ec) {
                              if(!ec)
                                  std::make_shared<HTTPClient>(std::move(socket))->start();
                              connection_loop(acceptor, socket);
                          });
}

void HTTPServer::start_server() {
    try {
        auto const address = net::ip::make_address(_address);
        auto const port = static_cast<unsigned short>(std::stoi(_port));

        net::io_context io_context{1};

        tcp::acceptor acceptor{io_context, {address, port}};
        tcp::socket socket{io_context};

        connection_loop(acceptor, socket);

        io_context.run();

    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

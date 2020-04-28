#include <gtest/gtest.h>
#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

#include "../../libs/client/include/client.hpp"
#include "../../libs/server/include/server.hpp"

class MockServer : public HTTPServer<HTTPClient> {
public:
    MockServer(std::string& address, std::string& port) : HTTPServer<HTTPClient>(address, port) {}
    MOCK_METHOD2(connection_loop, void(tcp::acceptor&, tcp::socket&));
};

class MockClient : public HTTPClient {
public:
    MockClient(tcp::socket socket) : HTTPClient(std::move(socket)) {}
    MOCK_METHOD0(start, void());
};

class TestUnitOfWork {};

class MockIndexController : public IndexController<TestUnitOfWork> {
public:
    MockIndexController(std::shared_ptr<TestUnitOfWork> _worker) : IndexController<TestUnitOfWork>(_worker) {}
    MOCK_METHOD0(get_queryset, boost::property_tree::ptree());
};

TEST(ClientStartTest, client_start) {

    net::io_context io_context{1};
    tcp::socket socket{io_context};

    std::string _address = "0.0.0.0";
    std::string _port = "80";
    HTTPServer<MockClient> server_test(_address, _port);

    MockClient client_test(std::move(socket));

    EXPECT_CALL(client_test, start()).Times(AtLeast(1));
    server_test.test_start_server(io_context, socket);
}

TEST(ControllerCallTest, index_call) {
    std::shared_ptr<TestUnitOfWork> _worker;
    MockIndexController test_cont(_worker);

    net::io_context io_context{1};
    tcp::socket socket{io_context};

    HTTPClient client_test(std::move(socket));

    EXPECT_CALL(test_cont, get_queryset()).Times(AtLeast(1));

    client_test.start();
}

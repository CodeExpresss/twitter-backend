#include <gtest/gtest.h>
#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

#include "../../libs/client/include/client.hpp"

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

class MockLoginController : public LoginController<TestUnitOfWork> {
public:
    MockLoginController(std::shared_ptr<TestUnitOfWork> _worker) : LoginController<TestUnitOfWork>(_worker) {}
    MOCK_METHOD0(get_queryset, boost::property_tree::ptree());
};

class MockLogoutController : public LogoutController<TestUnitOfWork> {
public:
    MockLogoutController(std::shared_ptr<TestUnitOfWork> _worker) : LogoutController<TestUnitOfWork>(_worker) {}
    MOCK_METHOD0(get_queryset, boost::property_tree::ptree());
};

class MockSignUpController : public SignUpController<TestUnitOfWork> {
public:
    MockSignUpController(std::shared_ptr<TestUnitOfWork> _worker) : SignUpController<TestUnitOfWork>(_worker) {}
    MOCK_METHOD0(get_queryset, boost::property_tree::ptree());
};

class MockUserController : public UserController<TestUnitOfWork> {
public:
    MockUserController(std::shared_ptr<TestUnitOfWork> _worker) : UserController<TestUnitOfWork>(_worker) {}
    MOCK_METHOD0(get_queryset, boost::property_tree::ptree());
};

TEST(ControllerCallTest, login_call) {
    std::shared_ptr<TestUnitOfWork> _worker;
    MockLoginController test_cont(_worker);

    net::io_context io_context{1};
    tcp::socket socket{io_context};

    HTTPClient client_test(std::move(socket));

    EXPECT_CALL(test_cont, get_queryset()).Times(AtLeast(1));

    client_test.start();
}

TEST(ControllerCallTest, logout_call) {
    std::shared_ptr<TestUnitOfWork> _worker;
    MockLogoutController test_cont(_worker);

    net::io_context io_context{1};
    tcp::socket socket{io_context};

    HTTPClient client_test(std::move(socket));

    EXPECT_CALL(test_cont, get_queryset()).Times(AtLeast(1));

    client_test.start();
}

TEST(ControllerCallTest, signup_call) {
    std::shared_ptr<TestUnitOfWork> _worker;
    MockSignUpController test_cont(_worker);

    net::io_context io_context{1};
    tcp::socket socket{io_context};

    HTTPClient client_test(std::move(socket));

    EXPECT_CALL(test_cont, get_queryset()).Times(AtLeast(1));

    client_test.start();
}

TEST(ControllerCallTest, user_call) {
    std::shared_ptr<TestUnitOfWork> _worker;
    MockUserController test_cont(_worker);

    net::io_context io_context{1};
    tcp::socket socket{io_context};

    HTTPClient client_test(std::move(socket));

    EXPECT_CALL(test_cont, get_queryset()).Times(AtLeast(1));

    client_test.start();
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

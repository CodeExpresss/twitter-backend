#include <gtest/gtest.h>
#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

#include "../../libs/client/include/client.hpp"
#include "controller_header.hpp"
#include "unit_of_work.hpp"

class MockClient : public HTTPClient {
public:
    MockClient(tcp::socket socket) : HTTPClient(std::move(socket)) {}
    MOCK_METHOD0(start, void());
};


class MockIndexController : public IndexController<UnitOfWork> {
public:
    MockIndexController(std::shared_ptr<UnitOfWork> _worker) : IndexController<UnitOfWork>(_worker) {}
    MOCK_METHOD0(get_queryset, boost::property_tree::ptree());
};

class MockLoginController : public LoginController<UnitOfWork> {
public:
    MockLoginController(std::shared_ptr<UnitOfWork> _worker) : LoginController<UnitOfWork>(_worker) {}
    MOCK_METHOD0(get_queryset, boost::property_tree::ptree());
};

class MockLogoutController : public LogoutController<UnitOfWork> {
public:
    MockLogoutController(std::shared_ptr<UnitOfWork> _worker) : LogoutController<UnitOfWork>(_worker) {}
    MOCK_METHOD0(get_queryset, boost::property_tree::ptree());
};

class MockSignUpController : public SignUpController<UnitOfWork> {
public:
    MockSignUpController(std::shared_ptr<UnitOfWork> _worker) : SignUpController<UnitOfWork>(_worker) {}
    MOCK_METHOD0(get_queryset, boost::property_tree::ptree());
};

class MockUserController : public UserController<UnitOfWork> {
public:
    MockUserController(std::shared_ptr<UnitOfWork> _worker) : UserController<UnitOfWork>(_worker) {}
    MOCK_METHOD0(get_queryset, boost::property_tree::ptree());
};

TEST(ControllerCallTest, login_call) {
    std::shared_ptr<UnitOfWork> _worker;
    MockLoginController test_cont(_worker);

    net::io_context io_context{1};
    tcp::socket socket{io_context};

    HTTPClient client_test(std::move(socket));

    EXPECT_CALL(test_cont, get_queryset()).Times(AtLeast(1));

    client_test.start();
}

TEST(ControllerCallTest, logout_call) {
    std::shared_ptr<UnitOfWork> _worker;
    MockLogoutController test_cont(_worker);

    net::io_context io_context{1};
    tcp::socket socket{io_context};

    HTTPClient client_test(std::move(socket));

    EXPECT_CALL(test_cont, get_queryset()).Times(AtLeast(1));

    client_test.start();
}

TEST(ControllerCallTest, signup_call) {
    std::shared_ptr<UnitOfWork> _worker;
    MockSignUpController test_cont(_worker);

    net::io_context io_context{1};
    tcp::socket socket{io_context};

    HTTPClient client_test(std::move(socket));

    EXPECT_CALL(test_cont, get_queryset()).Times(AtLeast(1));

    client_test.start();
}

TEST(ControllerCallTest, user_call) {
    std::shared_ptr<UnitOfWork> _worker;
    MockUserController test_cont(_worker);

    net::io_context io_context{1};
    tcp::socket socket{io_context};

    HTTPClient client_test(std::move(socket));

    EXPECT_CALL(test_cont, get_queryset()).Times(AtLeast(1));

    client_test.start();
}


TEST(ControllerCallTest, index_call) {
    std::shared_ptr<UnitOfWork> _worker;
    MockIndexController test_cont(_worker);

    net::io_context io_context{1};
    tcp::socket socket{io_context};

    HTTPClient client_test(std::move(socket));

    EXPECT_CALL(test_cont, get_queryset()).Times(AtLeast(1));

    client_test.start();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

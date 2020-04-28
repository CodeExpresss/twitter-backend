#include <iostream>
#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "index_controller.hpp"
#include "login_controller.hpp"
#include "logout_controller.hpp"
#include "user_controller.hpp"
#include "signup_controller.hpp"

using ::testing::AtLeast;

class MockUnitOfWork {
public:
    MOCK_METHOD0(get_index_tweet, boost::property_tree::ptree());
    MOCK_METHOD0(login, boost::property_tree::ptree());
    MOCK_METHOD0(logout, boost::property_tree::ptree());
    MOCK_METHOD0(authenticate, boost::property_tree::ptree());
    MOCK_METHOD0(get_user, boost::property_tree::ptree());
    MOCK_METHOD0(sign_up, boost::property_tree::ptree());
};

TEST(unit_of_work_mock, tweet_index) {
    MockUnitOfWork mock;
    EXPECT_CALL(mock, get_index_tweet()).Times(AtLeast(1));
    IndexController<MockUnitOfWork> obj(static_cast<std::shared_ptr<MockUnitOfWork>>(&mock));
    obj.get_queryset();
}

TEST(unit_of_work_mock, login) {
    MockUnitOfWork mock;
    EXPECT_CALL(mock, authenticate()).Times(AtLeast(1));
    EXPECT_CALL(mock, login()).Times(AtLeast(1));
    LoginController<MockUnitOfWork> obj(static_cast<std::shared_ptr<MockUnitOfWork>>(&mock));
    obj.get_queryset();
}

TEST(unit_of_work_mock, logout) {
    MockUnitOfWork mock;
    EXPECT_CALL(mock, logout()).Times(AtLeast(1));
    LogoutController<MockUnitOfWork> obj(static_cast<std::shared_ptr<MockUnitOfWork>>(&mock));
    obj.get_queryset();
}

TEST(unit_of_work_mock, get_user) {
    MockUnitOfWork mock;
    EXPECT_CALL(mock, get_user()).Times(AtLeast(1));
    UserController<MockUnitOfWork> obj(static_cast<std::shared_ptr<MockUnitOfWork>>(&mock));
    obj.get_queryset();
}

TEST(unit_of_work_mock, sign_up) {
    MockUnitOfWork mock;
    EXPECT_CALL(mock, sign_up()).Times(AtLeast(1));
    SignUpController<MockUnitOfWork> obj(static_cast<std::shared_ptr<MockUnitOfWork>>(&mock));
    obj.get_queryset();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

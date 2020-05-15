#include <gtest/gtest.h>
#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

#include "controller_header.hpp"
#include "unit_of_work.hpp"
#include "server.hpp"

TEST(Server_Working, Server_Tests) {
    std::string address = "0.0.0.0";
    std::string port = "8888";
    HTTPServer server(std::move(address), std::move(port));
    server.start_server();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
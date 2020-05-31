#include <gtest/gtest.h>
#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

#include "DBConnection.hpp"
#include "DBController.hpp"

#include "news_feed_repository.hpp"
#include "unit_of_work.hpp"
#include "server.hpp"

TEST(server_working, server_receiving_requests) {
    HTTPServer server {"127.0.0.1", "8000"};
    server.start_server();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
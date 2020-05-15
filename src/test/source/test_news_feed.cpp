#include <gtest/gtest.h>
#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

#include "DBConnection.hpp"
#include "DBController.hpp"

#include "news_feed_repository.hpp"

TEST(NewsFeedTests, NewsFeedReturnValue) {
    std::weak_ptr<DBController<DBConnection>> controller = make_shared<DBController<DBConnection>>(1);
    NewsFeedRepository NFrep(controller);
    err_code ec;
    NFrep.get_by_id(1, ec);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
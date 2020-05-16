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

TEST(NewsFeedTests, NewsFeedReturnValue) {
    std::shared_ptr<DBController<DBConnection>> controller =
            make_shared<DBController<DBConnection>>(3);
    NewsFeedRepository NFrep(controller);
    err_code ec;
    auto res = NFrep.get_by_id(1, ec);
    EXPECT_EQ(res[0].second.get_username(), "user1");
    EXPECT_EQ(res[0].second.get_user_id(), 3);
    EXPECT_EQ(res[0].first.get_text(), "tweet");
    EXPECT_EQ(res[0].first.get_tweet_id(), 2);
}

TEST(NewsFeedTests, NewsFeedUpdating) {
    UnitOfWork worker;
    std::vector<Tag> tags;
    std::string text{"some_text u dont know"};
    std::string date{"2020-05-06 00:01"};
    std::string image{"image"};
    Tweet tweet{1, 1, tags, text, date, image};
    err_code rc;
    worker.create_tweet(tweet);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
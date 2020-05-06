#include <iostream>
#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "profile_repository.hpp"
#include "tweet_repository.hpp"
#include "subscription_repository.hpp"
#include "user_repository.hpp"
#include "vote_repository.hpp"
#include "tag_repository.hpp"

#include "unit_of_work.hpp"

using ::testing::AtLeast;

class ProfileRepositoryMock : ProfileRepository {
public:
    MOCK_METHOD0(get_where, std::vector<Profile>());
    MOCK_METHOD0(get_by_id, Profile());
    MOCK_METHOD0(update, void());
    MOCK_METHOD0(create, void());
};

class UserRepositoryMock : UserRepository {
public:
    MOCK_METHOD0(get_by_id, User());
    MOCK_METHOD0(update, void());
    MOCK_METHOD0(create, void());
};

class TweetRepositoryMock : TweetRepository {
public:
    MOCK_METHOD0(get_where, std::vector<Tweet>());
    MOCK_METHOD0(get_by_id, Tweet());
    MOCK_METHOD0(create, void());
    MOCK_METHOD0(erase, void());
};

class TagRepositoryMock : TagRepository {
public:
    MOCK_METHOD0(get_where, std::vector<Tag>());
    MOCK_METHOD0(get_by_id, Tag());
    MOCK_METHOD0(create, void());
    MOCK_METHOD0(erase, void());
};

class VoteRepositoryMock : VoteRepository {
public:
    MOCK_METHOD0(get_where, std::vector<Vote>());
    MOCK_METHOD0(get_by_id, Vote());
    MOCK_METHOD0(create, void());
    MOCK_METHOD0(erase, void());
};

class SubscriptionRepositoryMock : SubscriptionRepository {
public:
    MOCK_METHOD0(get_where, std::vector<Subscription>());
    MOCK_METHOD0(get_by_id, Subscription());
    MOCK_METHOD0(create, void());
};

TEST(unit_of_work, login_test) {
    ProfileRepositoryMock mock_profile_rep;;
    UserRepositoryMock mock_user_rep;
    UnitOfWork unit_of_work;

    EXPECT_CALL(mock_profile_rep, create()).Times(AtLeast(1));
    EXPECT_CALL(mock_user_rep, create()).Times(AtLeast(1));

    unit_of_work.sing_up();
}

TEST(unit_of_work, update_profile_test) {
    ProfileRepositoryMock mock_profile_rep;;
    UserRepositoryMock mock_user_rep;
    UnitOfWork unit_of_work;

    EXPECT_CALL(mock_profile_rep, create()).Times(AtLeast(1));

    EXPECT_CALL(mock_profile_rep, update()).Times(AtLeast(1));

    unit_of_work.profile_update();
}

TEST(unit_of_work, update_user_test) {
    UserRepositoryMock mock_user_rep;
    UnitOfWork unit_of_work;

    EXPECT_CALL(mock_user_rep, update()).Times(AtLeast(1));

    unit_of_work.user_update();
}

TEST(unit_of_work, logout_test) {
    UserRepositoryMock mock_user_rep;
    UnitOfWork unit_of_work;

    EXPECT_CALL(mock_user_rep, update()).Times(AtLeast(1));

    unit_of_work.logout();
}

TEST(unit_of_work, get_index_tweet_test) {
    ProfileRepositoryMock mock_profile_rep;;
    TweetRepositoryMock mock_tweet_rep;
    TagRepositoryMock mock_tag_rep;
    SubscriptionRepositoryMock mock_subs_rep;
    VoteRepositoryMock mock_vote_rep;
    UnitOfWork unit_of_work;

    EXPECT_CALL(mock_subs_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_profile_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tweet_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_vote_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tag_rep, get_where()).Times(AtLeast(1));

    unit_of_work.get_index_tweet();
}

TEST(unit_of_work, create_tweet_test) {
    ProfileRepositoryMock mock_profile_rep;;
    UserRepositoryMock mock_user_rep;
    TweetRepositoryMock mock_tweet_rep;
    TagRepositoryMock mock_tag_rep;
    SubscriptionRepositoryMock mock_subs_rep;
    VoteRepositoryMock mock_vote_rep;
    UnitOfWork unit_of_work;

    EXPECT_CALL(mock_tag_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tweet_rep, create()).Times(AtLeast(1));

    unit_of_work.create_tweet();
}

TEST(unit_of_work, create_tweet_tag_test) {
    TweetRepositoryMock mock_tweet_rep;
    TagRepositoryMock mock_tag_rep;
    UnitOfWork unit_of_work;

    EXPECT_CALL(mock_tag_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tag_rep, create()).Times(AtLeast(1));
    EXPECT_CALL(mock_tweet_rep, create()).Times(AtLeast(1));

    unit_of_work.create_tweet();
}

TEST(unit_of_work, delete_tweet_test) {
    ProfileRepositoryMock mock_profile_rep;;
    UserRepositoryMock mock_user_rep;
    TweetRepositoryMock mock_tweet_rep;
    TagRepositoryMock mock_tag_rep;
    SubscriptionRepositoryMock mock_subs_rep;
    VoteRepositoryMock mock_vote_rep;
    UnitOfWork unit_of_work;

    EXPECT_CALL(mock_tag_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_vote_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tweet_rep, erase()).Times(AtLeast(1));

    unit_of_work.delete_tweet();
}
TEST(unit_of_work, delete_tweet_tag_test) {
    ProfileRepositoryMock mock_profile_rep;;
    UserRepositoryMock mock_user_rep;
    TweetRepositoryMock mock_tweet_rep;
    TagRepositoryMock mock_tag_rep;
    SubscriptionRepositoryMock mock_subs_rep;
    VoteRepositoryMock mock_vote_rep;
    UnitOfWork unit_of_work;

    EXPECT_CALL(mock_tag_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tag_rep, erase()).Times(AtLeast(1));
    EXPECT_CALL(mock_vote_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tweet_rep, erase()).Times(AtLeast(1));

    unit_of_work.delete_tweet();
}

TEST(unit_of_work, delete_tweet_vote_test) {
    ProfileRepositoryMock mock_profile_rep;;
    UserRepositoryMock mock_user_rep;
    TweetRepositoryMock mock_tweet_rep;
    TagRepositoryMock mock_tag_rep;
    SubscriptionRepositoryMock mock_subs_rep;
    VoteRepositoryMock mock_vote_rep;
    UnitOfWork unit_of_work;

    EXPECT_CALL(mock_tag_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_vote_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_vote_rep, erase()).Times(AtLeast(1));
    EXPECT_CALL(mock_tweet_rep, erase()).Times(AtLeast(1));

    unit_of_work.delete_tweet();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


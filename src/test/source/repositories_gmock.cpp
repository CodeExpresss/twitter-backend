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

class ProfileRepositoryMock : public ProfileRepository {
public:
    ProfileRepositoryMock(std::weak_ptr<DBController<DBConnection>> controller) : ProfileRepository(controller) {};
    MOCK_METHOD0(get_where, std::vector<Profile>());
    MOCK_METHOD0(get_by_id, Profile());
    MOCK_METHOD0(update, void());
    MOCK_METHOD0(create, void());
};

class UserRepositoryMock : public UserRepository {
public:
    UserRepositoryMock(std::weak_ptr<DBController<DBConnection>> controller) : UserRepository(controller) {};
    MOCK_METHOD0(get_by_id, User());
    MOCK_METHOD0(update, void());
    MOCK_METHOD0(create, void());
};

class TweetRepositoryMock : public TweetRepository {
public:
    TweetRepositoryMock(std::weak_ptr<DBController<DBConnection>> controller) : TweetRepository(controller) {};
    MOCK_METHOD0(get_where, std::vector<Tweet>());
    MOCK_METHOD0(get_by_id, Tweet());
    MOCK_METHOD0(create, void());
    MOCK_METHOD0(erase, void());
};

class TagRepositoryMock : public TagRepository {
public:
    TagRepositoryMock(std::weak_ptr<DBController<DBConnection>> controller) : TagRepository(controller) {};
    MOCK_METHOD0(get_where, std::vector<Tag>());
    MOCK_METHOD0(get_by_id, Tag());
    MOCK_METHOD0(create, void());
    MOCK_METHOD0(erase, void());
};

class VoteRepositoryMock : public VoteRepository {
public:
    VoteRepositoryMock(std::weak_ptr<DBController<DBConnection>> controller) : VoteRepository(controller) {};
    MOCK_METHOD0(get_where, std::vector<Vote>());
    MOCK_METHOD0(get_by_id, Vote());
    MOCK_METHOD0(create, void());
    MOCK_METHOD0(erase, void());
};

class SubscriptionRepositoryMock : public SubscriptionRepository {
public:
    SubscriptionRepositoryMock(std::weak_ptr<DBController<DBConnection>> controller) : SubscriptionRepository(controller) {};
    MOCK_METHOD0(get_where, std::vector<Subscription>());
    MOCK_METHOD0(get_by_id, Subscription());
    MOCK_METHOD0(create, void());
};

TEST(unit_of_work, login_test) {
    weak_ptr<DBController<DBConnection>> ptr_ctrl = make_shared<DBController<DBConnection>>(1);

    ProfileRepositoryMock mock_profile_rep(ptr_ctrl);
    UserRepositoryMock mock_user_rep(ptr_ctrl);
    TweetRepositoryMock mock_tweet_rep(ptr_ctrl);
    TagRepositoryMock mock_tag_rep(ptr_ctrl);
    VoteRepositoryMock mock_vote_rep(ptr_ctrl);
    SubscriptionRepositoryMock mock_subs_rep(ptr_ctrl);

    UnitOfWork unit_of_work(std::move(mock_profile_rep),
            std::move(mock_tweet_rep),
            std::move(mock_tag_rep),
            std::move(mock_user_rep),
            std::move(mock_vote_rep),
            std::move(mock_subs_rep));

    EXPECT_CALL(mock_profile_rep, create()).Times(AtLeast(1));
    EXPECT_CALL(mock_user_rep, create()).Times(AtLeast(1));

    unit_of_work.sing_up();
}

TEST(unit_of_work, update_profile_test) {
    weak_ptr<DBController<DBConnection>> ptr_ctrl = make_shared<DBController<DBConnection>>(1);

    ProfileRepositoryMock mock_profile_rep(ptr_ctrl);
    UserRepositoryMock mock_user_rep(ptr_ctrl);
    TweetRepositoryMock mock_tweet_rep(ptr_ctrl);
    TagRepositoryMock mock_tag_rep(ptr_ctrl);
    VoteRepositoryMock mock_vote_rep(ptr_ctrl);
    SubscriptionRepositoryMock mock_subs_rep(ptr_ctrl);

    UnitOfWork unit_of_work(std::move(mock_profile_rep),
            std::move(mock_tweet_rep),
            std::move(mock_tag_rep),
            std::move(mock_user_rep),
            std::move(mock_vote_rep),
            std::move(mock_subs_rep));

    EXPECT_CALL(mock_profile_rep, create()).Times(AtLeast(1));

    EXPECT_CALL(mock_profile_rep, update()).Times(AtLeast(1));

    unit_of_work.profile_update();
}

TEST(unit_of_work, update_user_test) {
    weak_ptr<DBController<DBConnection>> ptr_ctrl = make_shared<DBController<DBConnection>>(1);

    ProfileRepositoryMock mock_profile_rep(ptr_ctrl);
    UserRepositoryMock mock_user_rep(ptr_ctrl);
    TweetRepositoryMock mock_tweet_rep(ptr_ctrl);
    TagRepositoryMock mock_tag_rep(ptr_ctrl);
    VoteRepositoryMock mock_vote_rep(ptr_ctrl);
    SubscriptionRepositoryMock mock_subs_rep(ptr_ctrl);

    UnitOfWork unit_of_work(std::move(mock_profile_rep),
            std::move(mock_tweet_rep),
            std::move(mock_tag_rep),
            std::move(mock_user_rep),
            std::move(mock_vote_rep),
            std::move(mock_subs_rep));

    EXPECT_CALL(mock_user_rep, update()).Times(AtLeast(1));

    unit_of_work.user_update();
}

TEST(unit_of_work, logout_test) {
    weak_ptr<DBController<DBConnection>> ptr_ctrl = make_shared<DBController<DBConnection>>(1);

    ProfileRepositoryMock mock_profile_rep(ptr_ctrl);
    UserRepositoryMock mock_user_rep(ptr_ctrl);
    TweetRepositoryMock mock_tweet_rep(ptr_ctrl);
    TagRepositoryMock mock_tag_rep(ptr_ctrl);
    VoteRepositoryMock mock_vote_rep(ptr_ctrl);
    SubscriptionRepositoryMock mock_subs_rep(ptr_ctrl);

    UnitOfWork unit_of_work(std::move(mock_profile_rep),
            std::move(mock_tweet_rep),
            std::move(mock_tag_rep),
            std::move(mock_user_rep),
            std::move(mock_vote_rep),
            std::move(mock_subs_rep));

    EXPECT_CALL(mock_user_rep, update()).Times(AtLeast(1));

    unit_of_work.logout();
}

TEST(unit_of_work, get_index_tweet_test) {
    weak_ptr<DBController<DBConnection>> ptr_ctrl = make_shared<DBController<DBConnection>>(1);

    ProfileRepositoryMock mock_profile_rep(ptr_ctrl);
    UserRepositoryMock mock_user_rep(ptr_ctrl);
    TweetRepositoryMock mock_tweet_rep(ptr_ctrl);
    TagRepositoryMock mock_tag_rep(ptr_ctrl);
    VoteRepositoryMock mock_vote_rep(ptr_ctrl);
    SubscriptionRepositoryMock mock_subs_rep(ptr_ctrl);

    UnitOfWork unit_of_work(std::move(mock_profile_rep),
            std::move(mock_tweet_rep),
            std::move(mock_tag_rep),
            std::move(mock_user_rep),
            std::move(mock_vote_rep),
            std::move(mock_subs_rep));

    EXPECT_CALL(mock_subs_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_profile_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tweet_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_vote_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tag_rep, get_where()).Times(AtLeast(1));

    unit_of_work.get_index_tweet();
}

TEST(unit_of_work, create_tweet_test) {
    weak_ptr<DBController<DBConnection>> ptr_ctrl = make_shared<DBController<DBConnection>>(1);

    ProfileRepositoryMock mock_profile_rep(ptr_ctrl);
    UserRepositoryMock mock_user_rep(ptr_ctrl);
    TweetRepositoryMock mock_tweet_rep(ptr_ctrl);
    TagRepositoryMock mock_tag_rep(ptr_ctrl);
    VoteRepositoryMock mock_vote_rep(ptr_ctrl);
    SubscriptionRepositoryMock mock_subs_rep(ptr_ctrl);

    UnitOfWork unit_of_work(std::move(mock_profile_rep),
            std::move(mock_tweet_rep),
            std::move(mock_tag_rep),
            std::move(mock_user_rep),
            std::move(mock_vote_rep),
            std::move(mock_subs_rep));

    EXPECT_CALL(mock_tag_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tweet_rep, create()).Times(AtLeast(1));

    unit_of_work.create_tweet();
}

TEST(unit_of_work, create_tweet_tag_test) {
    weak_ptr<DBController<DBConnection>> ptr_ctrl = make_shared<DBController<DBConnection>>(1);

    ProfileRepositoryMock mock_profile_rep(ptr_ctrl);
    UserRepositoryMock mock_user_rep(ptr_ctrl);
    TweetRepositoryMock mock_tweet_rep(ptr_ctrl);
    TagRepositoryMock mock_tag_rep(ptr_ctrl);
    VoteRepositoryMock mock_vote_rep(ptr_ctrl);
    SubscriptionRepositoryMock mock_subs_rep(ptr_ctrl);

    UnitOfWork unit_of_work(std::move(mock_profile_rep),
            std::move(mock_tweet_rep),
            std::move(mock_tag_rep),
            std::move(mock_user_rep),
            std::move(mock_vote_rep),
            std::move(mock_subs_rep));

    EXPECT_CALL(mock_tag_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tag_rep, create()).Times(AtLeast(1));
    EXPECT_CALL(mock_tweet_rep, create()).Times(AtLeast(1));

    unit_of_work.create_tweet();
}

TEST(unit_of_work, delete_tweet_test) {
    weak_ptr<DBController<DBConnection>> ptr_ctrl = make_shared<DBController<DBConnection>>(1);

    ProfileRepositoryMock mock_profile_rep(ptr_ctrl);
    UserRepositoryMock mock_user_rep(ptr_ctrl);
    TweetRepositoryMock mock_tweet_rep(ptr_ctrl);
    TagRepositoryMock mock_tag_rep(ptr_ctrl);
    VoteRepositoryMock mock_vote_rep(ptr_ctrl);
    SubscriptionRepositoryMock mock_subs_rep(ptr_ctrl);

    UnitOfWork unit_of_work(std::move(mock_profile_rep),
            std::move(mock_tweet_rep),
            std::move(mock_tag_rep),
            std::move(mock_user_rep),
            std::move(mock_vote_rep),
            std::move(mock_subs_rep));

    EXPECT_CALL(mock_tag_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_vote_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tweet_rep, erase()).Times(AtLeast(1));

    unit_of_work.delete_tweet();
}
TEST(unit_of_work, delete_tweet_tag_test) {
    weak_ptr<DBController<DBConnection>> ptr_ctrl = make_shared<DBController<DBConnection>>(1);

    ProfileRepositoryMock mock_profile_rep(ptr_ctrl);
    UserRepositoryMock mock_user_rep(ptr_ctrl);
    TweetRepositoryMock mock_tweet_rep(ptr_ctrl);
    TagRepositoryMock mock_tag_rep(ptr_ctrl);
    VoteRepositoryMock mock_vote_rep(ptr_ctrl);
    SubscriptionRepositoryMock mock_subs_rep(ptr_ctrl);

    UnitOfWork unit_of_work(std::move(mock_profile_rep),
            std::move(mock_tweet_rep),
            std::move(mock_tag_rep),
            std::move(mock_user_rep),
            std::move(mock_vote_rep),
            std::move(mock_subs_rep));

    EXPECT_CALL(mock_tag_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tag_rep, erase()).Times(AtLeast(1));
    EXPECT_CALL(mock_vote_rep, get_where()).Times(AtLeast(1));
    EXPECT_CALL(mock_tweet_rep, erase()).Times(AtLeast(1));

    unit_of_work.delete_tweet();
}

TEST(unit_of_work, delete_tweet_vote_test) {
    weak_ptr<DBController<DBConnection>> ptr_ctrl = make_shared<DBController<DBConnection>>(1);

    ProfileRepositoryMock mock_profile_rep(ptr_ctrl);
    UserRepositoryMock mock_user_rep(ptr_ctrl);
    TweetRepositoryMock mock_tweet_rep(ptr_ctrl);
    TagRepositoryMock mock_tag_rep(ptr_ctrl);
    VoteRepositoryMock mock_vote_rep(ptr_ctrl);
    SubscriptionRepositoryMock mock_subs_rep(ptr_ctrl);

    UnitOfWork unit_of_work(std::move(mock_profile_rep),
            std::move(mock_tweet_rep),
            std::move(mock_tag_rep),
            std::move(mock_user_rep),
            std::move(mock_vote_rep),
            std::move(mock_subs_rep));

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


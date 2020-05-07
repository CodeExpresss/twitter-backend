#include <iostream>
#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "controller_header.hpp"

/*#include "index_controller.hpp"*/
//#include "login_controller.hpp"
//#include "logout_controller.hpp"
//#include "user_controller.hpp"
/*#include "signup_controller.hpp"*/

using ::testing::AtLeast;



class MockUnitOfWork : public UnitOfWork {
public:
    MockUnitOfWork(ProfileRepository profile_repository,
        TweetRepository  tweet_repository,
        TagRepository tag_repository,
        UserRepository user_repository,
        VoteRepository vote_repository,
        SubscriptionRepository subscription_repository)
        : UnitOfWork(profile_repository,
                tweet_repository,
                tag_repository,
                user_repository,
                vote_repository,
                subscription_repository) {}
    MOCK_METHOD0(get_index_tweet, std::tuple<Tweet, Profile>());
    MOCK_METHOD0(login, unsigned short int());
    MOCK_METHOD0(logout, unsigned short int());
    MOCK_METHOD0(authenticate, unsigned short int());
    MOCK_METHOD0(get_user, User());
    MOCK_METHOD0(sign_up, std::pair<unsigned short int, std::string>());
};

class TestUnitOfWork : public ::testing::Test
{
protected:
    void SetUp()
    {
        db_conn = make_shared<DBController<DBConnection>>(1);
        ProfileRepository profile_rep(db_conn);
        TweetRepository  tweet_rep(db_conn);
        TagRepository tag_rep(db_conn);
        UserRepository user_rep(db_conn);
        VoteRepository vote_rep(db_conn);
        SubscriptionRepository subscription_rep(db_conn);

        mock_work = new MockUnitOfWork(profile_rep, tweet_rep, tag_rep, user_rep, vote_rep, subscription_rep);
    }
    void TearDown() {}
    shared_ptr<DBController<DBConnection>> db_conn;
    MockUnitOfWork* mock_work;
};

TEST_F(TestUnitOfWork, tweet_index) {
    EXPECT_CALL(*mock_work, get_index_tweet()).Times(AtLeast(1));
    IndexController<MockUnitOfWork> obj(static_cast<std::shared_ptr<MockUnitOfWork>>(mock_work));
    obj.get_queryset();
}

TEST_F(TestUnitOfWork, login) {
    EXPECT_CALL(*mock_work, authenticate()).Times(AtLeast(1));
    EXPECT_CALL(*mock_work, login()).Times(AtLeast(1));
    LoginController<MockUnitOfWork> obj(static_cast<std::shared_ptr<MockUnitOfWork>>(mock_work));
    obj.get_queryset();
}

TEST_F(TestUnitOfWork, logout) {
    EXPECT_CALL(*mock_work, logout()).Times(AtLeast(1));
    LogoutController<MockUnitOfWork> obj(static_cast<std::shared_ptr<MockUnitOfWork>>(mock_work));
    obj.get_queryset();
}

TEST_F(TestUnitOfWork, get_user) {
    EXPECT_CALL(*mock_work, get_user()).Times(AtLeast(1));
    UserController<MockUnitOfWork> obj(static_cast<std::shared_ptr<MockUnitOfWork>>(mock_work));
    obj.get_queryset();
}

TEST_F(TestUnitOfWork, sign_up) {
    EXPECT_CALL(*mock_work, sign_up()).Times(AtLeast(1));
    SignUpController<MockUnitOfWork> obj(static_cast<std::shared_ptr<MockUnitOfWork>>(mock_work));
    obj.get_queryset();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <gtest/gtest.h>
#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

#include "../../libs/data_base/include/DBConnection.hpp"
#include "../../libs/data_base/include/DBController.hpp"

#include "../../libs/repositories/include/profile_repository.hpp"
#include "../../libs/repositories/include/subscription_repository.hpp"
#include "../../libs/repositories/include/tag_repository.hpp"
#include "../../libs/repositories/include/tweet_repository.hpp"
#include "../../libs/repositories/include/user_repository.hpp"
#include "../../libs/repositories/include/vote_repository.hpp"

class MockDBConnection : public DBConnection {
public:
    MOCK_CONST_METHOD0(get_connection, shared_ptr<PGconn>&());
};

class MockDBController : public DBController<DBConnection> {
public:
    MockDBController(int c) : DBController<DBConnection>(c) {}
    MOCK_METHOD0(get_free_connection, shared_ptr<DBConnection>());
    MOCK_METHOD1(reset_connection, void(shared_ptr<DBConnection>));
    MOCK_METHOD2(run_query, bool(string, vector<string>&));
};

class TestDBController : public ::testing::Test
{
protected:
    void SetUp()
    {
        mock_obj = make_shared<MockDBController>(1);
    }
    void TearDown() {}
    shared_ptr<MockDBController> mock_obj;
    vector<string> result;
};

TEST(DBConnectionTest, get_connection_call) {
    DBController<MockDBConnection> ctrl(1);
    shared_ptr<MockDBConnection> conn = ctrl.get_free_connection();
    ctrl.reset_connection(conn);
    EXPECT_CALL(*conn, get_connection()).Times(AtLeast(1));
    vector<string> result;
    ctrl.run_query("select 1;", result);
}

TEST_F(TestDBController, can_get_free_and_reset_connection) {
    shared_ptr<DBConnection> conn = mock_obj->get_free_connection();
    mock_obj->reset_connection(conn);
    EXPECT_CALL(*mock_obj, get_free_connection()).Times(AtLeast(1));
    EXPECT_CALL(*mock_obj, reset_connection(conn)).Times(AtLeast(1));
    mock_obj->run_query("select 1;", result);
}

TEST_F(TestDBController, profile_repository_run_query) {
    EXPECT_CALL(*mock_obj, run_query("select 1;", result)).Times(AtLeast(5));
    ProfileRepository p_rep(mock_obj);
    Profile p;
    p_rep.create(p);
    p_rep.get_where();
    p_rep.get_by_id(1);
    p_rep.update(p);
    p_rep.erase(1);
}

TEST_F(TestDBController, subscription_repository_run_query) {
    EXPECT_CALL(*mock_obj, run_query("select 1;", result)).Times(AtLeast(5));
    SubscriptionRepository sub_rep(mock_obj);
    Subscription sub;
    sub_rep.create(sub);
    sub_rep.get_where();
    sub_rep.get_by_id(1);
    sub_rep.update(sub);
    sub_rep.erase(1);
}

TEST_F(TestDBController, tag_repository_run_query) {
    EXPECT_CALL(*mock_obj, run_query("select 1;", result)).Times(AtLeast(5));
    TagRepository t_rep(mock_obj);
    Tag t;
    t_rep.create(t);
    t_rep.get_where();
    t_rep.get_by_id(1);
    t_rep.update(t);
    t_rep.erase(1);
}

TEST_F(TestDBController, tweet_repository_run_query) {
    EXPECT_CALL(*mock_obj, run_query("select 1;", result)).Times(AtLeast(5));
    TweetRepository tw_rep(mock_obj);
    Tweet tw;
    tw_rep.create(tw);
    tw_rep.get_where();
    tw_rep.get_by_id(1);
    tw_rep.update(tw);
    tw_rep.erase(1);
}

TEST_F(TestDBController, user_repository_run_query) {
    EXPECT_CALL(*mock_obj, run_query("select 1;", result)).Times(AtLeast(5));
    UserRepository u_rep(mock_obj);
    User u;
    u_rep.create(u);
    u_rep.get_where();
    u_rep.get_by_id(1);
    u_rep.update(u);
    u_rep.erase(1);
}

TEST_F(TestDBController, vote_repository_run_query) {
    EXPECT_CALL(*mock_obj, run_query("select 1;", result)).Times(AtLeast(5));
    VoteRepository v_rep(mock_obj);
    Vote v;
    v_rep.create(v);
    v_rep.get_where();
    v_rep.get_by_id(1);
    v_rep.update(v);
    v_rep.erase(1);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
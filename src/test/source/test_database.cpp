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

class MockDBController {
public:
    MOCK_METHOD0(get_free_connection, shared_ptr<MockDBConnection>());
    MOCK_METHOD1(reset_connection, void(shared_ptr<MockDBConnection>));
    MOCK_METHOD2(run_query, bool(string, vector<string>&));
};

class DBControllerLayer {
public:
    DBControllerLayer() { ctrl = &(DBController<MockDBConnection>::instance()); }
    shared_ptr<MockDBConnection> get_free_connection() { return ctrl->get_free_connection(); }
    void reset_connection(shared_ptr<MockDBConnection> c) { ctrl->reset_connection(c); }
    bool run_query(string str, vector<string>& ss) { return ctrl->run_query(str, ss); }
    
private:
    DBController<MockDBConnection> *ctrl;
};

class MockDBControl : public DBControllerLayer {
public:
    MOCK_METHOD0(get_free_connection, shared_ptr<MockDBConnection>());
    MOCK_METHOD1(reset_connection, void(shared_ptr<MockDBConnection>));
    MOCK_METHOD2(run_query, bool(string, vector<string>&));
};

/*TEST(DBConnectionTest, get_connection_call) {
    MockDBController controller;
    shared_ptr<MockDBConnection> conn = controller.connection;
    EXPECT_CALL(*conn, get_connection()).Times(AtLeast(1));
    vector<string> result;
    controller.run_query("select 1;", result);
}*/

TEST(DBControllerTest, can_get_free_and_reset_connection) {
    MockDBControl controller;
    EXPECT_CALL(controller, get_free_connection()).Times(AtLeast(1));
    shared_ptr<MockDBConnection> c = controller.get_free_connection();
    EXPECT_CALL(controller, reset_connection(c)).Times(AtLeast(1));
    vector<string> result;
    controller.run_query("select 1;", result);
}

TEST(DBControllerTest, profile_repository_run_query) {
    MockDBController controller;
    vector<string> result;
    EXPECT_CALL(controller, run_query("select 1;", result)).Times(AtLeast(5));
    ProfileRepository<MockDBController> p_rep;
    Profile p;
    p_rep.create(p);
    p_rep.get_all();
    p_rep.get_by_id(1);
    p_rep.update(p);
    p_rep.erase(1);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
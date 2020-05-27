#include <gtest/gtest.h>
#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

#include "../../libs/repositories/include/session_repository.hpp"
#include "../../libs/unit_of_work//include/unit_of_work.hpp"


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(session_tests, sessions_working) {
    std::shared_ptr<DBController<DBConnection>> controller =
            make_shared<DBController<DBConnection>>(3);
    SessionRepository repository(controller);
    err_code ec;
    std::string s_id = repository.create(1, ec);
    EXPECT_EQ(repository.check_session(s_id, ec), true);
    EXPECT_EQ(repository.get_profile_id(s_id, ec), 1);
    repository.erase(s_id, ec);
    EXPECT_EQ(repository.check_session(s_id, ec), false);
}

TEST(session_tests, unit_of_work_tests) {
    UnitOfWork worker;
    std::pair<int, std::string> id_s_id = worker.create_session(1);
    EXPECT_EQ(worker.check_session(id_s_id.second), true);
    EXPECT_EQ(worker.get_user_id_session(id_s_id.second).first, id_s_id.first);
    worker.delete_session(id_s_id.second);
    EXPECT_EQ(worker.check_session(id_s_id.second), false);
}
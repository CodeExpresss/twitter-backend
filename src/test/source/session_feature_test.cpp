#include <gtest/gtest.h>
#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

#include "../../libs/repositories//include/session_repository.hpp"

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

#include "gmock/gmock.h"

#include <gtest/gtest.h>
#include "container_tweet.hpp"
#include "container_tag.hpp"
#include "types.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

//class MockUser : public User {
    //MOCK_METHOD0(login, bool());
//};

class MockTag : public Tag {
};

TEST(TestUserAll, test_1) {
    //User<MockUserContainer> A;
    //A.Objects.all();
    //EXPECT_CALL(MockUserContainer, check_user()).Times(1);
    //User<MockUserContainer>::objects.check_user();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

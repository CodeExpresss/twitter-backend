#include "gmock/gmock.h"

#include <gtest/gtest.h>
//#include "container_user.hpp"
#include "types.h"
#include "user.hpp"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

//class MockUser : public User {
    //MOCK_METHOD0(login, bool());
//};


class MockUserContainer : public ContainerUser {
public:
    MOCK_METHOD0(check_user, bool());
};

//class MockUser : public User {
//};

TEST(TestUserAll, test_1) {
    //User<MockUserContainer> A;
    //A.Objects.all();
    EXPECT_CALL(MockUserContainer, check_user()).Times(1);
    User<MockUserContainer>::objects.check_user();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

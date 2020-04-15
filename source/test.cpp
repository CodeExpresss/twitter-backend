#include "gmock/gmock.h"

#include <gtest/gtest.h>
#include "container_user.hpp"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

//class MockUser : public User {
    //MOCK_METHOD0(login, bool());
//};

class MockUserContainer : public ContainerUser {
public:
    MOCK_METHOD0(all, void());
};



int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

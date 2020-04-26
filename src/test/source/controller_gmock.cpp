#include <iostream>
#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "../../libs/controllers/include/index_controller.hpp"

using ::testing::AtLeast;


// TODO class MockController : public UnitOfWork
class MockUnitOfWork {
public:
    MOCK_METHOD0(get_index_tweet, boost::property_tree::ptree());
};


TEST(controller_mock, controller_unit_of_work) {
    MockUnitOfWork mock;
    EXPECT_CALL(mock, get_index_tweet()).Times(AtLeast(1));
    IndexController index;
    EXPECT_TRUE(index.get_queryset());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

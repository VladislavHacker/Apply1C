#include <iostream>
#include <gtest/gtest.h>
#include "trytest.h"

TEST(Group1, Test1) {
    ASSERT_EQ(foo(), 1);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

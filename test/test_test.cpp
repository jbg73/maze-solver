#include <gtest/gtest.h>

TEST(TestingTestSuite, MyFirstTest){
    EXPECT_NE("Hello", "world");
    EXPECT_EQ(5,5);
}
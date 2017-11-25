#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(yes, test1)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

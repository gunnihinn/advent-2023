#include <gtest/gtest.h>

TEST(HelloTest, Basic)
{
	EXPECT_STRNE("A", "B");
	EXPECT_EQ(7 * 6, 42);
}

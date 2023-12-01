#include <fuzztest/fuzztest.h>
#include <gtest/gtest.h>

#include "advent.h"

TEST(HelloTest, Basic)
{
	EXPECT_STRNE("A", "B");
	EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest, Advent)
{
	EXPECT_NO_THROW(advent::hello());
}

void AdditionCommutes(int a, int b)
{
	EXPECT_EQ(a + b, b + a);
}
FUZZ_TEST(HelloTest, AdditionCommutes);

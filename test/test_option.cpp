#include <errno.h>

#include <gtest/gtest.h>
#include <crust/std/Option.h>

TEST(OptionTest, OptionSome)
{
	Option_t option;
	int data = 42;

	EXPECT_EQ(Option_some(nullptr, &data), -EINVAL);
	EXPECT_EQ(Option_some(&option, &data), 0);
	EXPECT_FALSE(Option_is_some(nullptr));
	EXPECT_TRUE(Option_is_some(&option));
	EXPECT_FALSE(Option_is_none(&option));
	EXPECT_EQ(*(int *)Option_unwrap(&option), 42);
}

TEST(OptionTest, OptionNone)
{
	Option_t option;

	EXPECT_EQ(Option_none(nullptr), -EINVAL);
	EXPECT_EQ(Option_none(&option), 0);
	EXPECT_FALSE(Option_is_some(&option));
	EXPECT_TRUE(Option_is_none(nullptr));
	EXPECT_TRUE(Option_is_none(&option));
	EXPECT_EQ(Option_unwrap(&option), nullptr);
}

TEST(OptionTest, OptionUnwrapNone)
{
	Option_t option;

	Option_none(&option);
	EXPECT_EQ(Option_unwrap(&option), nullptr);
}

TEST(OptionTest, OptionUnwrapSome)
{
	Option_t option;
	int data = 42;

	Option_some(&option, &data);
	EXPECT_EQ(*(int *)Option_unwrap(&option), 42);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

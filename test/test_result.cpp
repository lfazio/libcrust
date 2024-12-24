#include <errno.h>

#include <gtest/gtest.h>
#include <crust/std/Result.h>

TEST(ResultTest, ResultOk)
{
	Result_t result;
	int data = 42;

	EXPECT_EQ(Result_ok(nullptr, &data), -EINVAL);
	EXPECT_EQ(Result_ok(&result, &data), 0);
	EXPECT_TRUE(Result_is_ok(&result));
	EXPECT_FALSE(Result_is_err(&result));
	EXPECT_EQ(*(int *)Result_unwrap(&result), 42);
}

TEST(ResultTest, ResultErr)
{
	Result_t result;
	int error_code = -1;

	EXPECT_EQ(Result_err(nullptr, 0), -EINVAL);
	EXPECT_EQ(Result_err(&result, error_code), 0);
	EXPECT_FALSE(Result_is_ok(&result));
	EXPECT_TRUE(Result_is_err(&result));
	EXPECT_EQ(Result_unwrap_err(&result), error_code);
}

TEST(ResultTest, UnwrapOk)
{
	Result_t result;
	int data = 42;

	Result_ok(&result, &data);
	EXPECT_EQ(*(int *)Result_unwrap(&result), 42);
	EXPECT_EQ(Result_unwrap(nullptr), nullptr);
}

TEST(ResultTest, UnwrapErr)
{
	Result_t result;
	Result_t ok;
	int error_code = -1;

	Result_err(&result, error_code);
	EXPECT_EQ(Result_unwrap(&result), nullptr);
	Result_ok(&ok, nullptr);
	EXPECT_EQ(Result_unwrap_err(nullptr), -EINVAL);
	EXPECT_EQ(Result_unwrap_err(&ok), 0);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

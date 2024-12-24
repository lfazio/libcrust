#include <gtest/gtest.h>
#include <crust/std/Box.h>

TEST(BoxTest, CreateAndRef)
{
	int data = 42;

	Box_t box = Box_new(&data, sizeof(data));
	ASSERT_NE(box, nullptr);
	EXPECT_EQ(*Box_downcast(box, int), 42);
	ASSERT_EQ(Box_new(&data, 0), nullptr);

	Box_drop(box);
	Box_drop(nullptr);

	box = Box_new(nullptr, sizeof(data));
	ASSERT_NE(box, nullptr);
	EXPECT_EQ(*Box_downcast(box, int), 0);
	*Box_downcast(box, int) = 42;
	EXPECT_EQ(*Box_downcast(box, int), 42);

	Box_drop(box);
}

TEST(BoxTest, CreateWithNullRef)
{
	Box_t box = Box_new(nullptr, sizeof(int));
	ASSERT_NE(box, nullptr);
	EXPECT_NE(Box_ref(box), nullptr);
	EXPECT_EQ(Box_ref(nullptr), nullptr);

	Box_drop(box);
}

TEST(BoxTest, SizeOf)
{
	int data = 42;

	Box_t box = Box_new(&data, sizeof(data));
	ASSERT_NE(box, nullptr);
	EXPECT_EQ(Box_sizeof(box), sizeof(data));

	Box_drop(box);

	EXPECT_EQ(Box_sizeof(nullptr), -EINVAL);
}

TEST(BoxTest, Display)
{
	int data = 42;

	Box_t box = Box_new(&data, sizeof(data));
	ASSERT_NE(box, nullptr);

	testing::internal::CaptureStdout();
	Box_display(box);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Box<"), std::string::npos);

	Box_drop(box);
}

TEST(BoxTest, DisplayAllocated)
{
	Box_t box = Box_new(nullptr, sizeof(int));
	ASSERT_NE(box, nullptr);

	EXPECT_EQ(*Box_downcast(box, int), 0);
	*Box_downcast(box, int) = 42;
	EXPECT_EQ(*Box_downcast(box, int), 42);

	testing::internal::CaptureStdout();
	Box_display(box);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Box<"), std::string::npos);

	Box_drop(box);
}

TEST(BoxTest, DisplayNullPtr)
{
	testing::internal::CaptureStdout();
	Box_display(nullptr);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Box<invalid>"), std::string::npos);
}


int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
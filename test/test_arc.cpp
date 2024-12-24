#include <gtest/gtest.h>
#include <crust/std/Arc.h>

void free_func(void *ref)
{
	free(ref);
}

TEST(ArcTest, CreateAndRef)
{
	int data = 42;

	Arc_t arc = Arc_create(&data, nullptr);
	ASSERT_NE(arc, nullptr);
	EXPECT_EQ(*Arc_downcast(arc, int), 42);
	EXPECT_EQ(Arc_downcast(nullptr, void *), nullptr);

	Arc_drop(arc);
	Arc_drop(nullptr);
}

TEST(ArcTest, Clone)
{
	int data = 42;

	ASSERT_EQ(Arc_clone(nullptr), nullptr);

	Arc_t arc = Arc_create(&data, nullptr);
	ASSERT_NE(arc, nullptr);

	Arc_t arc_clone = (Arc_t)Arc_clone(arc);
	ASSERT_NE(arc_clone, nullptr);
	EXPECT_EQ(*Arc_downcast(arc_clone, int), 42);

	Arc_drop(arc);
	Arc_drop(arc_clone);
}

TEST(ArcTest, LockUnlock)
{
	int data = 42;

	Arc_t arc = Arc_create(&data, nullptr);
	ASSERT_NE(arc, nullptr);

	EXPECT_EQ(Arc_lock(nullptr), -EINVAL);
	EXPECT_EQ(Arc_lock(arc), 0);
	EXPECT_EQ(Arc_unlock(nullptr), -EINVAL);
	EXPECT_EQ(Arc_unlock(arc), 0);

	Arc_drop(arc);
}

TEST(ArcTest, StrongCount)
{
	int data = 42;

	Arc_t arc = Arc_create(&data, nullptr);
	ASSERT_NE(arc, nullptr);

	EXPECT_EQ(Arc_strong_count(nullptr), -EINVAL);
	EXPECT_EQ(Arc_strong_count(arc), 1);

	Arc_t arc_clone = (Arc_t)Arc_clone(arc);
	EXPECT_EQ(Arc_strong_count(arc), 2);

	Arc_drop(arc);
	Arc_drop(arc_clone);
}

TEST(ArcTest, CreateAndRefAlloc)
{
	int *data = (int *)malloc(sizeof(int));
	*data = 42;

	Arc_t arc = Arc_create(data, free_func);
	ASSERT_NE(arc, nullptr);
	EXPECT_EQ(*Arc_downcast(arc, int), 42);

	Arc_drop(arc);
}

TEST(ArcTest, CloneAlloc)
{
	int *data = (int *)malloc(sizeof(int));
	*data = 42;

	Arc_t arc = Arc_create(data, free_func);
	ASSERT_NE(arc, nullptr);

	Arc_t arc_clone = (Arc_t)Arc_clone(arc);
	ASSERT_NE(arc_clone, nullptr);
	EXPECT_EQ(*Arc_downcast(arc_clone, int), 42);

	Arc_drop(arc);
	Arc_drop(arc_clone);
}

TEST(ArcTest, LockUnlockAlloc)
{
	int *data = (int *)malloc(sizeof(int));
	*data = 42;

	Arc_t arc = Arc_create(data, free_func);
	ASSERT_NE(arc, nullptr);

	EXPECT_EQ(Arc_lock(arc), 0);
	EXPECT_EQ(Arc_unlock(arc), 0);

	Arc_drop(arc);
}

TEST(ArcTest, StrongCountAlloc)
{
	int *data = (int *)malloc(sizeof(int));
	*data = 42;

	Arc_t arc = Arc_create(data, free_func);
	ASSERT_NE(arc, nullptr);

	EXPECT_EQ(Arc_strong_count(arc), 1);

	Arc_t arc_clone = (Arc_t)Arc_clone(arc);
	EXPECT_EQ(Arc_strong_count(arc), 2);

	Arc_drop(arc);
	Arc_drop(arc_clone);
}

TEST(ArcTest, Display)
{
	int data = 42;

	Arc_t rc = Arc_create(&data, nullptr);
	ASSERT_NE(rc, nullptr);

	testing::internal::CaptureStdout();
	Arc_display(rc);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Arc<"), std::string::npos);

	Arc_drop(rc);
}

TEST(ArcTest, DisplayLocked)
{
	int data = 42;

	Arc_t rc = Arc_create(&data, nullptr);
	ASSERT_NE(rc, nullptr);

	testing::internal::CaptureStdout();
	EXPECT_EQ(Arc_lock(rc), 0);
	Arc_display(rc);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Arc<"), std::string::npos);

	EXPECT_EQ(Arc_unlock(rc), 0);
	Arc_drop(rc);
}

TEST(ArcTest, DisplayNullPtr)
{
	testing::internal::CaptureStdout();
	Arc_display(nullptr);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Arc<"), std::string::npos);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#include <errno.h>
#include <gtest/gtest.h>
#include <crust/std/Rc.h>

void free_func(void *ref)
{
	free(ref);
}

TEST(RcTest, CreateAndRef)
{
	int *data = (int *)malloc(sizeof(int));
	*data = 42;

	Rc_t rc = Rc_create(data, free_func);
	ASSERT_NE(rc, nullptr);
	EXPECT_EQ(*(int *)Rc_ref(rc), 42);
	EXPECT_EQ(Rc_ref(nullptr), nullptr);

	Rc_drop(rc);
	Rc_drop(nullptr);
}

TEST(RcTest, Clone)
{
	int *data = (int *)malloc(sizeof(int));
	*data = 42;

	Rc_t rc = Rc_create(data, free_func);
	ASSERT_NE(rc, nullptr);

	ASSERT_EQ(Rc_clone(nullptr), nullptr);

	Rc_t rc_clone = (Rc_t)Rc_clone(rc);
	ASSERT_NE(rc_clone, nullptr);
	EXPECT_EQ(*Rc_downcast(rc_clone, int), 42);

	Rc_drop(rc);
	Rc_drop(rc_clone);
}

TEST(RcTest, LockUnlock)
{
	int *data = (int *)malloc(sizeof(int));
	*data = 42;

	Rc_t rc = Rc_create(data, free_func);
	ASSERT_NE(rc, nullptr);

	ASSERT_EQ(Rc_lock(nullptr), -EINVAL);
	EXPECT_EQ(Rc_lock(rc), 0);
	ASSERT_EQ(Rc_unlock(nullptr), -EINVAL);
	EXPECT_EQ(Rc_unlock(rc), 0);

	Rc_drop(rc);
}

TEST(RcTest, StrongCount)
{
	int *data = (int *)malloc(sizeof(int));
	*data = 42;

	Rc_t rc = Rc_create(data, free_func);
	ASSERT_NE(rc, nullptr);

	EXPECT_EQ(Rc_strong_count(rc), 1);

	Rc_t rc_clone = (Rc_t)Rc_clone(rc);
	EXPECT_EQ(Rc_strong_count(nullptr), -EINVAL);
	EXPECT_EQ(Rc_strong_count(rc), 2);

	Rc_drop(rc);
	Rc_drop(rc_clone);
}

TEST(RcTest, Display)
{
	int data = 42;

	Rc_t rc = Rc_create(&data, nullptr);
	ASSERT_NE(rc, nullptr);

	testing::internal::CaptureStdout();
	Rc_display(rc);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Rc<"), std::string::npos);

	Rc_drop(rc);
}

TEST(RcTest, DisplayLocked)
{
	int data = 42;

	Rc_t rc = Rc_create(&data, nullptr);
	ASSERT_NE(rc, nullptr);

	testing::internal::CaptureStdout();
	EXPECT_EQ(Rc_lock(rc), 0);
	Rc_display(rc);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Rc<"), std::string::npos);

	EXPECT_EQ(Rc_unlock(rc), 0);
	Rc_drop(rc);
}

TEST(RcTest, DisplayNullPtr)
{
	testing::internal::CaptureStdout();
	Rc_display(nullptr);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Rc<"), std::string::npos);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

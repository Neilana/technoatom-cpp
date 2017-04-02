#include "gtest/gtest.h"
#include <iostream>

#include "shared_ptr.h"

using std::size_t;

using IlluminatiConfirmed::shared_ptr;

TEST(SharedPtrTest, CheckConstructor)
{
    // test 1 - empty constructor
    // given
    shared_ptr<int> sp1;
    size_t expectedCount = 0;

    // when
    size_t actualCount = sp1.use_count();

    // then
    ASSERT_EQ(actualCount, expectedCount);

    // test 2 - not empty
    // given
    shared_ptr<int> sp2(new int(2));
    expectedCount = 1;

    // when
    actualCount = sp2.use_count();

    // then
    ASSERT_EQ(actualCount, expectedCount);
}

TEST(SharedPtrTest, CheckCopyConstructor)
{
    // given
    shared_ptr<int> sp1(new int(2));

    // when
    shared_ptr<int> sp2(sp1);
    size_t expectedCount = 2;
    size_t actualCount1 = sp1.use_count();
    size_t actualCount2 = sp2.use_count();

    // then
    ASSERT_EQ(actualCount1, expectedCount);
    ASSERT_EQ(actualCount2, expectedCount);
}

TEST(SharedPtrTest, CheckOperatorAssignment)
{
    // given
    shared_ptr<int> sp1(new int(2));

    // when
    shared_ptr<int> sp2;
    sp2 = sp1;
    size_t expectedCount = 2;
    size_t actualCount1 = sp1.use_count();
    size_t actualCount2 = sp2.use_count();

    // then
    ASSERT_EQ(actualCount1, expectedCount);
    ASSERT_EQ(actualCount2, expectedCount);
}

TEST(SharedPtrTest, CheckEmptyReset)
{
    // given
    shared_ptr<int> sp1(new int(2));
    shared_ptr<int> sp2(sp1);
    shared_ptr<int> sp3(sp2);

    // when
    sp2.reset();

    size_t expectedCountSp1 = 2;
    size_t expectedCountSp2 = 0;

    size_t actualCountSp1 = sp1.use_count();
    size_t actualCountSp2 = sp2.use_count();

    // then
    ASSERT_EQ(actualCountSp1, expectedCountSp1);
    ASSERT_EQ(actualCountSp2, expectedCountSp2);
}

TEST(SharedPtrTest, CheckNotEmptyReset)
{
    // given
    shared_ptr<int> sp1;

    // when
    sp1.reset(new int(1));
    size_t expectedCount = 1;
    size_t actualCount = sp1.use_count();

    // then
    ASSERT_EQ(actualCount, expectedCount);
}

TEST(SharedPtrTest, CheckOperatorStar)
{
    // given
    shared_ptr<int> sp1(new int(123));

    // when
    int expectedValue = 123;
    int actualValue = *sp1;

    // then
    ASSERT_EQ(actualValue, expectedValue);
}

TEST(SharedPtrTest, CheckOperatorArrow)
{
    struct TestStruct
    {
        int x;
        int y;
    };

    // given
    shared_ptr<TestStruct> sp1(new TestStruct {10, 20});

    // when
    int expectedX = 10;
    int actualX = sp1->x;

    int expectedY = 20;
    int actualY = sp1->y;

    // then
    ASSERT_EQ(actualX, expectedX);
    ASSERT_EQ(actualY, expectedY);
}

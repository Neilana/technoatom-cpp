#include "gtest/gtest.h"
//#include <bitset>

#include "ContainerInterface.h"
#include "Array.h"
#include "Vector.h"

using IlluminatiConfirmed::Array;
using IlluminatiConfirmed::Vector;
using IlluminatiConfirmed::Iterator;

// BitPointer
TEST(BoolTestBitPointer, CheckGetSet)
{
    // test 1
    // given
    Array <bool, 10> a1;
    bool expectedValue = true;

    // when
    a1[2].setValue(true);
    bool actualValue = a1[2].getValue();

    // then
    ASSERT_EQ(actualValue, expectedValue);

    // test 2
    //given a1
    expectedValue = false;

    // when
    a1[2].setValue(false);
    actualValue = a1[2].getValue();

    // then
    ASSERT_EQ(actualValue, expectedValue);
}

// iterators
TEST(BoolTestIterator, CheckBegin)
{
    // test 1: begin
    // given
    Array <bool, 5> a1;
    a1[0] = true;
    bool expectedValue = true;

    // when
    Array <bool, 5>::iterator it1 = a1.begin();
    bool actualValue = *it1;

    //then
    ASSERT_EQ(actualValue, expectedValue);

    // test 2: begin
    // given
    expectedValue = false;
    a1[0] = false;

    // when
    actualValue = *it1;

    // then
    ASSERT_EQ(actualValue, expectedValue);
}

TEST(BoolTestIterator, CheckPrefixPlus)
{
    // given
    Array <bool, 5> a1;
    a1[0] = true;
    a1[1] = false;
    a1[2] = true;
    a1[3] = false;
    a1[4] = true;

    Array <bool, 5>::iterator it1 = a1.begin();

    // when/then
    ASSERT_EQ(*it1, true);          // a[0]

    ASSERT_EQ(*(++it1), false);     // a[1]

    ASSERT_EQ(*(++it1), true);      // a[2]

    ASSERT_EQ(*(++it1), false);     // a[3]

    ASSERT_EQ(*(++it1), true);      // a[4]
}

TEST(BoolTestIterator, CheckPostfixPlus)
{
    // given
    Array <bool, 5> a1;
    a1[0] = true;
    a1[1] = false;
    a1[2] = true;
    a1[3] = false;
    a1[4] = true;

    Array <bool, 5>::iterator it1 = a1.begin();

    // when/then
    ASSERT_EQ(*it1++, true);      // a[0]

    ASSERT_EQ(*it1++, false);     // a[1]

    ASSERT_EQ(*it1++, true);      // a[2]

    ASSERT_EQ(*it1++, false);     // a[3]

    ASSERT_EQ(*it1++, true);      // a[4]
}

TEST(BoolTestIterator, CheckPlus)
{
    // given
    Array <bool, 5> a1;
    a1[0] = true;
    a1[1] = false;
    a1[2] = true;
    a1[3] = false;
    a1[4] = false;

    Array <bool, 5>::iterator it1 = a1.begin();

    // when/then
    ASSERT_EQ(*it1, true);
    ASSERT_EQ(*(it1+1), false);
    ASSERT_EQ(*(it1+2), true);
    ASSERT_EQ(*(it1+3), false);
    ASSERT_EQ(*(it1+4), false);
}

TEST(BoolTestIterator, CheckMinus)
{
    // given
    Array <bool, 5> a1;
    a1[0] = true;
    a1[1] = false;
    a1[2] = true;
    a1[3] = false;
    a1[4] = false;

    Array <bool, 5>::iterator it1 = a1.end();

    // when/then
    ASSERT_EQ(*(it1-1), false);
    ASSERT_EQ(*(it1-2), false);
    ASSERT_EQ(*(it1-3), true);
    ASSERT_EQ(*(it1-4), false);
    ASSERT_EQ(*(it1-5), true);
}

TEST(BoolTestIterator, CheckCompareOps)
{
    // test 1
    // given
    Array <bool, 5> a;
    a[0] = true;
    a[1] = false;
    a[2] = true;
    a[3] = false;
    a[4] = false;

    Array <bool, 5>::iterator ita1 = a.begin();
    Array <bool, 5>::iterator ita2 = a.begin();

    // when/then
    ASSERT_TRUE (ita1 == ita2);

//    ita2 = a.begin() + 3;
//    ASSERT_TRUE (ita1 < ita2);

    // test 2
    // given
    Array <bool, 5> b;
    b[0] = true;
    b[1] = false;
    b[2] = true;
    b[3] = false;
    b[4] = false;

    Array <bool, 5>::iterator itb = b.begin();

    // when/then
    ASSERT_TRUE (ita1 != itb);
}

// array
TEST(BoolTestArray, CheckConstructorWithDefaultValue)
{
    // test 1: defualt 1
    // given
    Array <bool, 5> a1(1);

    // when
    bool expectedValue = true;

    // then
    for (size_t i = 0; i < 5; i++)
    {
        bool actualValue = a1[i];
        ASSERT_EQ(actualValue, expectedValue);
    }

    // test 2: defualt 0
    // given
    Array <bool, 10> a2(0);

    // when
    expectedValue = false;

    // then
    for (size_t i = 0; i < 10; i++)
    {
        bool actualValue = a2[i];
        ASSERT_EQ(actualValue, expectedValue);
    }
}

TEST(BoolTestArray, CheckCopyConstructor)
{
    // given
    Array <bool, 5> a1;
    a1[0] = true;
    a1[1] = false;
    a1[2] = true;
    a1[3] = false;
    a1[4] = false;
    size_t expectedSize = 5;

    // when
    Array <bool, 5> a2(a1);
    size_t actualSize = a2.size();

    // then
    ASSERT_EQ(actualSize, expectedSize);

    // and
    Array <bool, 5>::iterator it1 = a2.end();

    // when/then
    ASSERT_EQ(*(it1-1), false);
    ASSERT_EQ(*(it1-2), false);
    ASSERT_EQ(*(it1-3), true);
    ASSERT_EQ(*(it1-4), false);
    ASSERT_EQ(*(it1-5), true);
}

TEST(BoolTestArray, CheckAggregateInitialization)
{
    Array <bool, 5> a1 = {1, 1, 0, 0, 1};
    // and
    Array <bool, 5>::iterator it1 = a1.begin();

    // when/then
    ASSERT_EQ(*(it1), 1);
    ASSERT_EQ(*(it1+1), 1);
    ASSERT_EQ(*(it1+2), 0);
    ASSERT_EQ(*(it1+3), 0);
    ASSERT_EQ(*(it1+4), 1);
}

TEST(BoolTestArray, CheckAssigment)
{
    // given
    Array <bool, 5> a1 = {1, 1, 0, 0, 1};
    Array <bool, 5> a2 = {0, 0, 1, 0, 1};
    Array <bool, 5>::iterator it1 = a2.begin();

    // when
    a2 = a1;

    // then
    ASSERT_EQ(*(it1), 1);
    ASSERT_EQ(*(it1+1), 1);
    ASSERT_EQ(*(it1+2), 0);
    ASSERT_EQ(*(it1+3), 0);
    ASSERT_EQ(*(it1+4), 1);
}

TEST(BoolTestArray, CheckSize)
{
   // given
   Array <bool, 10> a1;
   size_t expectedSize = 10;

   // when
   size_t actualSize = a1.size();

   // then
   ASSERT_EQ(actualSize, expectedSize);
}

TEST(BoolTestArray, CheckBracketsLValue)
{
   // given
   Array <bool, 10> a1;
   bool expectedValue = true;

   // when
   a1[3] = true;                        //l-value
   bool actualValue = a1[3].getValue();

   // then
   ASSERT_EQ(actualValue, expectedValue);
}

TEST(BoolTestArray, CheckBracketsRValue)
{
    // test 1
    // given
    Array <bool, 10> a1;
    bool expectedValue = true;

    // when
    a1[3] = true;                // l-value
    bool actualValue = a1[3];    // r-value

    // then
    ASSERT_EQ(actualValue, expectedValue);

    // test 2
    // given
    a1[0] = true;
    a1[1] = false;
    expectedValue = true;

    // when
    a1[1] = a1[0];                 // both: l and r-value
    actualValue = a1[1];

    // then
    ASSERT_EQ(actualValue, expectedValue);
}

// vector
TEST(BoolTestVector, CheckConstructorWithDefaultValue)
{
    // test 1: defualt 1
    // given
    Vector <bool> v1(5, true);

    // when
    bool expectedValue = true;

    // then
    for (size_t i = 0; i < 5; i++)
    {
        bool actualValue = v1[i];
        ASSERT_EQ(actualValue, expectedValue);
    }

    // test 2: defualt false
    // given
    Vector <bool> v2(10, false);

    // when
    expectedValue = false;

    // then
    for (size_t i = 0; i < 10; i++)
    {
        bool actualValue = v2[i];
        ASSERT_EQ(actualValue, expectedValue);
    }
}

TEST(BoolTestVector, CheckCopyConstructor)
{
    // given
    Vector <bool> v1(5);
    v1[0] = true;
    v1[1] = false;
    v1[2] = true;
    v1[3] = false;
    v1[4] = false;
    size_t expectedSize = 5;

    // when
    Vector <bool> v2(v1);
    size_t actualSize = v2.size();

    // then
    ASSERT_EQ(actualSize, expectedSize);

    // and
    Vector <bool>::iterator it1 = v2.end();

    // when/then
    ASSERT_EQ(*(it1-1), false);
    ASSERT_EQ(*(it1-2), false);
    ASSERT_EQ(*(it1-3), true);
    ASSERT_EQ(*(it1-4), false);
    ASSERT_EQ(*(it1-5), true);
}

TEST(BoolTestVector, CheckAggregateInitialization)
{
    Vector <bool> v1 = {1, 1, 0, 0, 1};
    // and
    Vector <bool>::iterator it1 = v1.begin();

    // when/then
    ASSERT_EQ(*(it1), 1);
    ASSERT_EQ(*(it1+1), 1);
    ASSERT_EQ(*(it1+2), 0);
    ASSERT_EQ(*(it1+3), 0);
    ASSERT_EQ(*(it1+4), 1);
}

TEST(BoolTestVector, CheckAssigment)
{
    // given
    Vector <bool> v1 = {1, 1, 0, 0, 1};
    Vector <bool> v2 = {0, 0, 1, 0, 1};
    Vector <bool>::iterator it1 = v2.begin();

    // when
    v2 = v1;

    // then
    ASSERT_EQ(*(it1), 1);
    ASSERT_EQ(*(it1+1), 1);
    ASSERT_EQ(*(it1+2), 0);
    ASSERT_EQ(*(it1+3), 0);
    ASSERT_EQ(*(it1+4), 1);
}

TEST(BoolTestVector, CheckSize)
{
   // given
   Vector <bool> v1(10);
   size_t expectedSize = 10;

   // when
   size_t actualSize = v1.size();

   // then
   ASSERT_EQ(actualSize, expectedSize);
}

TEST(BoolTestVector, CheckBracketsLValue)
{
   // given
   Vector <bool> v1(10);
   bool expectedValue = true;

   // when
   v1[3] = true;                        //l-value
   bool actualValue = v1[3].getValue();

   // then
   ASSERT_EQ(actualValue, expectedValue);
}

TEST(BoolTestVector, CheckBracketsRValue)
{
    // test 1
    // given
    Vector <bool> v1(10);
    bool expectedValue = true;

    // when
    v1[3] = true;                // l-value
    bool actualValue = v1[3];    // r-value

    // then
    ASSERT_EQ(actualValue, expectedValue);

    // test 2
    // given
    v1[0] = true;
    v1[1] = false;
    expectedValue = true;

    // when
    v1[1] = v1[0];                 // both: l and r-value
    actualValue = v1[1];

    // then
    ASSERT_EQ(actualValue, expectedValue);
}

TEST(BoolTestVector, CheckReserve)
{
    Vector<bool> v1(2);
    size_t expectedCapacity = 8;
    size_t actualCapacity = v1.capacity();
    ASSERT_EQ(actualCapacity, expectedCapacity);

    v1.reserve(4);
    expectedCapacity = 8;
    actualCapacity = v1.capacity();
    ASSERT_EQ(actualCapacity, expectedCapacity);

    v1.reserve(10);
    expectedCapacity = 16;
    actualCapacity = v1.capacity();
    ASSERT_EQ(actualCapacity, expectedCapacity);
}

TEST (BoolTestVector, CheckResize)
{
    // given
    Vector <bool> v1 = {1, 1, 0, 0, 1};
    Vector <bool>::iterator it1 = v1.begin();

    // when
    v1.resize(10, true);
    size_t expectedSize = 10;
    size_t expectedCapacity = 16;

    // then
    size_t actualSize = v1.size();
    ASSERT_EQ(actualSize, expectedSize);

    size_t actualCapacity = v1.capacity();
    ASSERT_EQ(actualCapacity, expectedCapacity);

    // and
    ASSERT_EQ(*(it1+5), 1);
    ASSERT_EQ(*(it1+6), 1);
    ASSERT_EQ(*(it1+7), 1);
    ASSERT_EQ(*(it1+8), 1);
    ASSERT_EQ(*(it1+9), 1);
}

TEST (BoolTestVector, CheckPushBack)
{
    // given
    Vector <bool> v1(0);

    // when
    v1.push_back(1);
    v1.push_back(0);
    v1.push_back(0);
    v1.push_back(1);

    size_t expectedSize = 4;
    size_t expectedCapacity = 8;

    Vector <bool>::iterator it1 = v1.begin();

    // then
    size_t actualSize = v1.size();
    ASSERT_EQ(actualSize, expectedSize);

    size_t actualCapacity = v1.capacity();
    ASSERT_EQ(actualCapacity, expectedCapacity);

    // and
    ASSERT_EQ(*(it1), 1);
    ASSERT_EQ(*(it1+1), 0);
    ASSERT_EQ(*(it1+2), 0);
    ASSERT_EQ(*(it1+3), 1);
}

// useful headers
#include "gtest/gtest.h"
#include <string>
#include <vector>

// custom headers
#include "Array.h"

using IlluminatiConfirmed::Array;

TEST(ArrayTest, CheckDefaultConstructorReturnsCorrectSize)
{
    // GIVEN
    Array <int, 10> array1;
    size_t expectedSize = 10;

    // WHEN
    size_t actualSize = array1.size();

    // THEN
    ASSERT_EQ(actualSize, expectedSize);

}

TEST(ArrayTest, CheckAccessWithBrackets)
{
    /* FEATURE #1. CHECK OPERATOR [] WITH NOT EMPTY ARRAY (LOW BOUNDARY). */
    // GIVEN
    Array <int, 6> a1 = {1,2,3,4,5,6};
    int expectedValue = 10;

    // WHEN
    a1[0] = 10;
    int actualValue = a1[0];

    // THEN
    ASSERT_EQ(actualValue, expectedValue);


    /* FEATURE #2. CHECK OPERATOR [] WITH NOT EMPTY ARRAY (HIGH BOUNDARY). */
    // GIVEN
    expectedValue = 5;

    // WHEN
    actualValue = a1[4];

    // THEN
    ASSERT_EQ(actualValue, expectedValue);

    // GIVEN
    expectedValue = 50;

    // WHEN
    a1[4] = 50;
    actualValue = a1[4];

    // THEN
    ASSERT_EQ(actualValue, expectedValue);


    /* FEATURE #3. CHECK OPERATOR [] WITH NOT EMPTY ARRAY (INDEX OUT OF RANGE). */
    // GIVEN the same full array
    // WHEN trying to get value of non-existing 10th element
    // THEN we have an exception
    ASSERT_ANY_THROW(a1[10]);

    // GIVEN the same full array
    // WHEN trying to get value of -10 element (just for fun)
    // THEN we have an exception
    ASSERT_ANY_THROW(a1[-10]);

    // GIVEN the same full array
    // WHEN trying to get value of non-existing element with TOOOOOO BIIIIIIIG INDEX
    // THEN we have an exception
    ASSERT_ANY_THROW(a1[10000000000000]);
}

TEST(ArrayTest, CheckAccess_At)
{
    /* 1. Check not empty array. */
    Array <int, 6> a1 = {1,2,3,4,5,6};

    // low threshold
    ASSERT_EQ(a1.at(0), 1);    // check read

    a1[0] = 10;
    ASSERT_EQ(a1.at(0), 10);   // check write

    // high thersshold
    ASSERT_EQ(a1.at(4), 5);    // read

    a1[4] = 50;
    ASSERT_EQ(a1.at(4), 50);   // write

    // out of range: too high
    ASSERT_ANY_THROW(a1.at(10));

    // out of range: too low
    ASSERT_ANY_THROW(a1.at(-10));

    // out of range: wrong high number
    ASSERT_ANY_THROW(a1.at(100000000000000));

}

TEST(ArrayTest, CheckMaxSize)
{
    // test 1
    std::vector <std::string> v1(5);
    size_t expectedSize = v1.max_size();

    Array <std::string, 5> a1;
    size_t actualSize =  a1.max_size();

    ASSERT_EQ(expectedSize, actualSize);

    // test 2
    std::vector <std::string> v2(10);
    expectedSize = v2.max_size();

    Array <std::string, 10> a2;
    actualSize =  a2.max_size();

    ASSERT_EQ(expectedSize, actualSize);
}

TEST(ArrayTest, CheckOperatorAssignment)
{
    Array<double, 10> a1;
    for (size_t i = 0; i<10; i++)
    {

        a1[i] = i*10;
    }
    Array<double, 10> a2(10);
    for (size_t i = 0; i<10; i++)
    {

        a2[i] = i*1000;
    }

    a2 = a1;

    for (size_t i = 0; i<10; i++)
    {
        ASSERT_EQ(a1.at(i), i*10);
        ASSERT_EQ(a2.at(i), i*10);
    }
}

TEST(ArrayTest, CheckEqualOperator)
{
    Array<double, 6> a1 = {10,20,30,40,50,60};
    Array<double, 6> a2 = {10,20,30,40,50,60};

    ASSERT_TRUE(a1 == a2);

    Array<double, 6> a3 = {10,20,30,40,50,60};

    a3[2] = 0;

    ASSERT_FALSE(a3 == a1);
}

TEST (ArrayTest, CheckSwap)
{
    Array <double, 5> a1;
    for (size_t i = 0; i<5; i++)
        a1[i] = i*10;

    Array <double, 5> a2;
    for (size_t i = 0; i<5; i++)
        a2[i] = i*1000;

    a1.swap(a2);
    // ыыыы, смотрим дампы, там всё океюшки. но надо будет переделать по-православному
}

TEST (ArrayTest2, CheckAggregateInitialization)
{
    Array<double, 6> a1 = {10,20,30,40,50,60};

    for (size_t i = 0; i < a1.size(); i++)
    {
        ASSERT_EQ(a1.at(i), (i+1)*10);
    }

    Array<double, 6> a2 {10,20,30,40,50,60};

    for (size_t i = 0; i < a2.size(); i++)
    {
        ASSERT_EQ(a2.at(i), (i+1)*10);
    }

    Array<double, 6> a3 ({10,20,30,40,50,60});

    for (size_t i = 0; i < a3.size(); i++)
    {
        ASSERT_EQ(a3.at(i), (i+1)*10);
    }
}

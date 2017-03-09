#include "gtest/gtest.h"
#include <string>
#include <vector>
#include "Array.h"

using IlluminatiConfirmed::Array;

TEST(ArrayTest, CheckDefaultConstructorReturnsCorrectCapacity)
{
    // GIVEN
    Array <int> array1;
    size_t expectedCapacity = 0;

    // WHEN
    size_t capacity = array1.capacity();

    // THEN
    ASSERT_EQ(capacity, expectedCapacity);


    /* FEATURE #2. CHECK CONSTRUCTOR WITH 1 ARGUMENT (ZERO SIZED ARRAY). */
    // GIVEN
    Array <int> array2(0);
    expectedCapacity = 0;

    // WHEN
    capacity = array2.capacity();

    // THEN
    ASSERT_EQ(capacity, expectedCapacity);


    /* FEATURE #3. CHECK CONSTRUCTOR WITH 1 ARGUMENT (NORMAL SIZED ARRAY). */
    // GIVEN
    Array <int> array3(10);
    expectedCapacity = 10;

    // WHEN
    capacity = array3.capacity();

    // THEN
    ASSERT_EQ(capacity, expectedCapacity);


    /* FEATURE #4. CHECK CONSTRUCTOR WITH 1 ARGUMENT (NEGATIVE AMOUNT OF ELEMENTS). */
    // GIVEN
    Array <int> array4(-10);
    expectedCapacity = 0;

    // WHEN
    capacity = array4.capacity();

    // THEN
    ASSERT_EQ(capacity, expectedCapacity);


    /* FEATURE #5. CHECK CONSTRUCTOR WITH 1 ARGUMENT (TOO BIG NUMBER OF ELEMENTS). */
    // GIVEN
    Array <int> array5(1000000000000000);
    expectedCapacity = 0;

    // WHEN
    capacity = array5.capacity();

    // THEN
    ASSERT_EQ(capacity, expectedCapacity);


    /* FEATURE #6. CHECK CONSTRUCTOR WITH 1 ARGUMENT (WRONG ARGUMENT TYPE). */
    // GIVEN
    Array <int> array6(5.5);
    expectedCapacity = 5;

    // WHEN
    capacity = array6.capacity();

    // THEN
    ASSERT_EQ(capacity, expectedCapacity);
}

TEST(ArrayTest, CheckAccessWithBrackets)
{
    /* FEATURE #1. CHECK OPERATOR [] WITH NOT EMPTY ARRAY (LOW BOUNDARY). */
    // GIVEN
    Array <int> a1;
    a1.push_back(1);
    a1.push_back(2);
    a1.push_back(3);
    a1.push_back(4);
    a1.push_back(5);

    int expectedValue = 1;

    // WHEN
    int actualValue = a1[0];

    // THEN
    ASSERT_EQ(actualValue, expectedValue);


    // GIVEN
    expectedValue = 10;

    // WHEN
    a1[0] = 10;
    actualValue = a1[0];

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


    /* FEATURE #4. CHECK OPERATOR [] WITH EMPTY ARRAY. */
    // GIVEN an empty array with no elements
    Array <int> a2;

    // WHEN trying to get value of non-existing 2nd element
    // THEN we have an exception
    ASSERT_ANY_THROW(a2[2]);

    /* FEATURE #5. CHECK OPERATOR [] WITH EMPTY ARRAY (WITHOUT push_back(). */
    Array <int> a3(5);
    a3[0] = 100;
    ASSERT_EQ(a3[0], 100);
}

TEST(ArrayTest, CheckAccess_At)
{
    /* 1. Check not empty array. */
    Array <int> a1;
    a1.push_back(1);
    a1.push_back(2);
    a1.push_back(3);
    a1.push_back(4);
    a1.push_back(5);

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

    // wrong range type
//    ASSERT_ANY_THROW(a1.at(3.4));

    /* 2. Check empty array. */
    Array <int> a2;
    ASSERT_ANY_THROW(a2.at(2));
}

TEST(ArrayTest, CheckSize)
{
    Array <int> a1;

    a1.push_back(1);
    ASSERT_EQ(a1.size(), 1);
}

TEST(ArrayTest, CheckMaxSize)
{
    // test 1
    std::vector <std::string> v1(5);
    size_t expectedSize = v1.max_size();

    Array <std::string> a1(5);
    size_t actualSize =  a1.max_size();

    ASSERT_EQ(expectedSize, actualSize);

    // test 2
    std::vector <std::string> v2(10);
    expectedSize = v2.max_size();

    Array <std::string> a2(10);
    actualSize =  a2.max_size();

    ASSERT_EQ(expectedSize, actualSize);
}

TEST(ArrayTest, CheckOperatorAssignment)
{
    Array<double> a1(10);
    for (size_t i = 0; i<10; i++)
    {

        a1[i] = i*10;
    }
    Array<double> a2(10);
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

TEST(ArrayTest, CheckConstructorDefaultValue)
{
    Array<double> a1(10,10.1);
    for (size_t i = 0; i < 10; i++)
    {
        ASSERT_EQ(a1.at(i), 10.1);
    }

    Array <int> a2(10);
    for (size_t i = 0; i < 10; i++)
    {
        ASSERT_EQ(a2.at(i), 0);
    }

    Array <std::string> a3(10);
    for (size_t i = 0; i < 10; i++)
    {
        ASSERT_EQ(a3.at(i), "");
    }
}

TEST(ArrayTest, CheckAccessAssignmentOpConst)
{
    const Array<double> a1(10);
    //a1[1] = 0; //It does not compile if all is ok
}

TEST(ArrayTest, CheckEqualOperator)
{
    const Array<double> a1(10, 10.2);
    const Array<double> a2(10, 10.2);

    ASSERT_TRUE(a1 == a2);

    Array<double> a3(10, 10.2);

    a3[9] = 0;

    ASSERT_FALSE(a3 == a1);
}

TEST(ArrayTest, CheckReserve)
{
    Array<double> a1(2);
    size_t expectedCapacity = 2;
    size_t actualCapacity = a1.capacity();
    ASSERT_EQ(actualCapacity, expectedCapacity);

    a1.reserve(5);
    expectedCapacity = 5;
    actualCapacity = a1.capacity();
    ASSERT_EQ(actualCapacity, expectedCapacity);
}

TEST(ArrayTest, CheckPushFront)
{
    Array<double> a1(10, 10.3);

    a1.push_front(10000);

    ASSERT_EQ(a1.capacity(), 11);
    ASSERT_EQ(a1.at(0), 10000);

    a1.push_front(20000);

    ASSERT_EQ(a1.capacity(), 12);
    ASSERT_EQ(a1.at(0), 20000);
    ASSERT_EQ(a1.at(1), 10000);

    for (size_t i = 2; i < a1.capacity(); i++)
        ASSERT_EQ(a1.at(i), 10.3);
}

//TEST(ArrayTest, CheckAccess_FrontBack)
//{
//    Array <float> a1;
//    a1.push_back(1.21);
//    a1.push_back(2.34);
//    a1.push_back(3.56);
//    a1.push_back(4.78);
//    a1.push_back(5.91);
//    ASSERT_EQ(a1.front(), 1.21);
//    ASSERT_EQ(a1.back(), 5.91);

//    Array <float> a2;
//    ASSERT_ANY_THROW(a2.front());
//    ASSERT_ANY_THROW(a2.back());

//    Array <float> a3(5);
//    ASSERT_ANY_THROW(a3.front());
//    ASSERT_ANY_THROW(a3.back());
//}

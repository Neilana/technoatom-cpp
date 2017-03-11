#include "gtest/gtest.h"
#include <string>
#include <vector>

#include "Vector.h"

using IlluminatiConfirmed::Vector;

TEST(VectorTest, CheckDefaultConstructorReturnsCorrectCapacity)
{
    // GIVEN
    Vector <int> vector1;
    size_t expectedCapacity = 0;

    // WHEN
    size_t capacity = vector1.capacity();

    // THEN
    ASSERT_EQ(capacity, expectedCapacity);


    /* FEATURE #2. CHECK CONSTRUCTOR WITH 1 ARGUMENT (ZERO SIZED ARRAY). */
    // GIVEN
    Vector <int> vector2(0);
    expectedCapacity = 0;

    // WHEN
    capacity = vector2.capacity();

    // THEN
    ASSERT_EQ(capacity, expectedCapacity);


    /* FEATURE #3. CHECK CONSTRUCTOR WITH 1 ARGUMENT (NORMAL SIZED ARRAY). */
    // GIVEN
    Vector <int> vector3(10);
    expectedCapacity = 10;

    // WHEN
    capacity = vector3.capacity();

    // THEN
    ASSERT_EQ(capacity, expectedCapacity);


    /* FEATURE #4. CHECK CONSTRUCTOR WITH 1 ARGUMENT (NEGATIVE AMOUNT OF ELEMENTS). */
    // GIVEN
    Vector <int> vector4(-10);
    expectedCapacity = 0;

    // WHEN
    capacity = vector4.capacity();

    // THEN
    ASSERT_EQ(capacity, expectedCapacity);


    /* FEATURE #5. CHECK CONSTRUCTOR WITH 1 ARGUMENT (TOO BIG NUMBER OF ELEMENTS). */
    // GIVEN
    Vector <int> vector5(1000000000000000);
    expectedCapacity = 0;

    // WHEN
    capacity = vector5.capacity();

    // THEN
    ASSERT_EQ(capacity, expectedCapacity);


    /* FEATURE #6. CHECK CONSTRUCTOR WITH 1 ARGUMENT (WRONG ARGUMENT TYPE). */
    // GIVEN
    Vector <int> vector6(5.5);
    expectedCapacity = 5;

    // WHEN
    capacity = vector6.capacity();

    // THEN
    ASSERT_EQ(capacity, expectedCapacity);
}

TEST(VectorTest, CheckAccessWithBrackets)
{
    /* FEATURE #1. CHECK OPERATOR [] WITH NOT EMPTY ARRAY (LOW BOUNDARY). */
    // GIVEN
    Vector <int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);

    int expectedValue = 1;

    // WHEN
    int actualValue = v1[0];

    // THEN
    ASSERT_EQ(actualValue, expectedValue);


    // GIVEN
    expectedValue = 10;

    // WHEN
    v1[0] = 10;
    actualValue = v1[0];

    // THEN
    ASSERT_EQ(actualValue, expectedValue);


    /* FEATURE #2. CHECK OPERATOR [] WITH NOT EMPTY ARRAY (HIGH BOUNDARY). */
    // GIVEN
    expectedValue = 5;

    // WHEN
    actualValue = v1[4];

    // THEN
    ASSERT_EQ(actualValue, expectedValue);


    // GIVEN
    expectedValue = 50;

    // WHEN
    v1[4] = 50;
    actualValue = v1[4];

    // THEN
    ASSERT_EQ(actualValue, expectedValue);


    /* FEATURE #3. CHECK OPERATOR [] WITH NOT EMPTY ARRAY (INDEX OUT OF RANGE). */
    // GIVEN the same full vector
    // WHEN trying to get value of non-existing 10th element
    // THEN we have an exception
    ASSERT_ANY_THROW(v1[10]);

    // GIVEN the same full vector
    // WHEN trying to get value of -10 element (just for fun)
    // THEN we have an exception
    ASSERT_ANY_THROW(v1[-10]);

    // GIVEN the same full vector
    // WHEN trying to get value of non-existing element with TOOOOOO BIIIIIIIG INDEX
    // THEN we have an exception
    ASSERT_ANY_THROW(v1[10000000000000]);


    /* FEATURE #4. CHECK OPERATOR [] WITH EMPTY ARRAY. */
    // GIVEN an empty vector with no elements
    Vector <int> v2;

    // WHEN trying to get value of non-existing 2nd element
    // THEN we have an exception
    ASSERT_ANY_THROW(v2[2]);

    /* FEATURE #5. CHECK OPERATOR [] WITH EMPTY ARRAY (WITHOUT push_back(). */
    Vector <int> v3(5);
    v3[0] = 100;
    ASSERT_EQ(v3[0], 100);
}

TEST(VectorTest, CheckAccess_At)
{
    /* 1. Check not empty vector. */
    Vector <int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);

    // low threshold
    ASSERT_EQ(v1.at(0), 1);    // check read

    v1[0] = 10;
    ASSERT_EQ(v1.at(0), 10);   // check write

    // high thersshold
    ASSERT_EQ(v1.at(4), 5);    // read

    v1[4] = 50;
    ASSERT_EQ(v1.at(4), 50);   // write

    // out of range: too high
    ASSERT_ANY_THROW(v1.at(10));

    // out of range: too low
    ASSERT_ANY_THROW(v1.at(-10));

    // out of range: wrong high number
    ASSERT_ANY_THROW(v1.at(100000000000000));

    // wrong range type
//    ASSERT_ANY_THROW(v1.at(3.4));

    /* 2. Check empty vector. */
    Vector <int> v2;
    ASSERT_ANY_THROW(v2.at(2));
}

TEST(VectorTest, CheckSize)
{
    Vector <int> v1;

    v1.push_back(1);
    ASSERT_EQ(v1.size(), 1);

    v1.push_back(10);
    ASSERT_EQ(v1.size(), 2);
    ASSERT_EQ(v1.capacity(), 5);
    v1.push_back(10);
    v1.push_back(10);
    v1.push_back(10);
    ASSERT_EQ(v1.capacity(), 5);
    v1.push_back(10);
    ASSERT_EQ(v1.capacity(), 10);
    ASSERT_EQ(v1.size(), 6);
    v1.reserve(20);
    ASSERT_EQ(v1.size(), 6);
    ASSERT_EQ(v1.capacity(), 20);
    v1.clear();
    ASSERT_EQ(v1.capacity(), 20);
    ASSERT_EQ(v1.size(), 0);
}

TEST(VectorTest, CheckMaxSize)
{
    // test 1
    std::vector <std::string> v1(5);
    size_t expectedSize = v1.max_size();

    Vector <std::string> vStd1(5); //FIXME: wtf??
    size_t actualSize =  v1.max_size();

    ASSERT_EQ(expectedSize, actualSize);

    // test 2
    std::vector <std::string> vStd2(10);
    expectedSize = vStd2.max_size();

    Vector <std::string> v2(10);
    actualSize =  v2.max_size();

    ASSERT_EQ(expectedSize, actualSize);
}

TEST(VectorTest, CheckOperatorAssignment)
{
    Vector<double> v1(10);
    for (size_t i = 0; i<10; i++)
    {

        v1[i] = i*10;
    }
    Vector<double> v2(10);
    for (size_t i = 0; i<10; i++)
    {

        v2[i] = i*1000;
    }

    v2 = v1;

    for (size_t i = 0; i<10; i++)
    {
        ASSERT_EQ(v1.at(i), i*10);
        ASSERT_EQ(v2.at(i), i*10);
    }
}

TEST(VectorTest, CheckConstructorDefaultValue)
{
    Vector<double> v1(10,10.1);
    for (size_t i = 0; i < 10; i++)
    {
        ASSERT_EQ(v1.at(i), 10.1);
    }

    Vector <int> v2(10);
    for (size_t i = 0; i < 10; i++)
    {
        ASSERT_EQ(v2.at(i), 0);
    }

    Vector <std::string> v3(10);
    for (size_t i = 0; i < 10; i++)
    {
        ASSERT_EQ(v3.at(i), "");
    }
}

TEST(VectorTest, CheckAccessAssignmentOpConst)
{
    const Vector<double> v1(10);
    //v1[1] = 0; //It does not compile if all is ok
}

TEST(VectorTest, CheckEqualOperator)
{
    const Vector<double> v1(10, 10.2);
    const Vector<double> v2(10, 10.2);

    ASSERT_TRUE(v1 == v2);

    Vector<double> v3(10, 10.2);

    v3[9] = 0;

    ASSERT_FALSE(v3 == v1);
}

TEST(VectorTest, CheckReserve)
{
    Vector<double> v1(2);
    size_t expectedCapacity = 2;
    size_t actualCapacity = v1.capacity();
    ASSERT_EQ(actualCapacity, expectedCapacity);

    v1.reserve(5);
    expectedCapacity = 5;
    actualCapacity = v1.capacity();
    ASSERT_EQ(actualCapacity, expectedCapacity);
}

TEST (VectorTest, CheckSwap)
{
    Vector <double> v1(10);
    for (size_t i = 0; i<10; i++)
        v1[i] = i*10;

    Vector <double> v2(5);
    for (size_t i = 0; i<5; i++)
        v2[i] = i*1000;

    v1.swap(v2);
    // ыыыы, смотрим дампы, там всё океюшки. но надо будет переделать по-православному
}

TEST (VectorTest, CheckResize)
{
    Vector <double> v1(10);
    for (size_t i = 0; i<10; i++)
        v1[i] = i*10;
    v1.resize(5);
    // ыыы, снова смотрим дампы :D

    Vector <double> v2(5);
    for (size_t i = 0; i<5; i++)
        v2[i] = i*1000;

    v2.resize(10);
    // ...и снова!
}

TEST (VectorTest, CheckAggregateInitialization)
{
    Vector<double> v1 = {10,20,30,40,50,60};

    for (size_t i = 0; i < v1.capacity(); i++)
    {
        ASSERT_EQ(v1.at(i), (i+1)*10);
    }

    Vector<double> v2 {10,20,30,40,50,60};

    for (size_t i = 0; i < v2.capacity(); i++)
    {
        ASSERT_EQ(v2.at(i), (i+1)*10);
    }

    Vector<double> v3 ({10,20,30,40,50,60});

    for (size_t i = 0; i < v3.capacity(); i++)
    {
        ASSERT_EQ(v3.at(i), (i+1)*10);
    }
}

TEST (VectorTest, CheckIterators) //эммм..))
{
    Vector<double> v1 = {10,20,30,40,50,60};
    size_t i = 0;
    ASSERT_EQ(6,v1.size());
    for (IlluminatiConfirmed::Vector<double>::iterator it = v1.begin(); it != v1.end(); it++)
    {
        ASSERT_EQ((*it), ((i++)+1)*10);
    }
    i = 6;
    for (IlluminatiConfirmed::Vector<double>::iterator it = v1.end(); it != v1.begin(); --it)
    {
        ASSERT_EQ((*it), ((i--))*10);
    }
}


#include "gtest/gtest.h"
#include "Array.h"

using IlluminatiConfirmed::Array;

TEST(ArrayTest, CheckConstructors)
{
    /* FEATURE #1: CHECK CONSTRUCTOR WITHOUT ARGUMENTS (ZERO SIZED ARRAY). */
    // GIVEN an empty just constructed array with default constructor
    Array <int> a1;

    // WHEN we check for its capacity
    size_t capacity = a1.capacity();

    // THEN it tells us it's empty
    ASSERT_EQ(capacity, 0);


    /* FEATURE #2. CHECK CONSTRUCTOR WITH 1 ARGUMENT (ZERO SIZED ARRAY). */
    // GIVEN an empty just constructed arrray with arguments
    Array <int> a2(0);

    // WHEN we check for its capacity
    capacity = a2.capacity();

    // THEN it tells us it's empty
    ASSERT_EQ(capacity, 0);


    /* FEATURE #3. CHECK CONSTRUCTOR WITH 1 ARGUMENT (NORMAL SIZED ARRAY). */
    // GIVEN an empty array with 10 elements
    Array <int> a3(10);

    // WHEN we check for its capacity
    capacity = a3.capacity();

    // THEN it tells us it's in fact 10 elements
    ASSERT_EQ(capacity, 10);


    /* FEATURE #4. CHECK CONSTRUCTOR WITH 1 ARGUMENT (NEGATIVE AMOUNT OF ELEMENTS). */
    // GIVEN an attempt to create an array with -10 elements (just for fun)
    Array <int> a4(-10);

    // WHEN we're trying to do sth with this array (to get its capacity)
    capacity = a4.capacity();

    // THEN it tells us it's ok but has zero capacity
    ASSERT_EQ(capacity, 0);


    /* FEATURE #5. CHECK CONSTRUCTOR WITH 1 ARGUMENT (TOO BIG NUMBER OF ELEMENTS). */
    // GIVEN an attempt to create an array with toooooooo maaaaaaaanyyyyyyyyyyyyy elements
    Array <int> a5(1000000000000000);

    // WHEN we're trying to do sth with this array (to get its capacity)
    capacity = a5.capacity();

    // THEN it tells us it's ok but has zero capacity
    ASSERT_EQ(capacity, 0);


    /* FEATURE #6. CHECK CONSTRUCTOR WITH 1 ARGUMENT (WRONG ARGUMENT TYPE). */
    // GIVEN an attempt to create an array with wrong argument type
    Array <int> a6(5.5);

    // WHEN we're trying to do sth with this array (to get its capacity)
    capacity = a6.capacity();

    // THEN it tells us it's ok but has zero capacity
    ASSERT_EQ(capacity, 5);
}

TEST(ArrayTest, CheckAccess_Brackets)
{
    /* FEATURE #1. CHECK OPERATOR [] WITH NOT EMPTY ARRAY (LOW BOUNDARY). */
    // GIVEN not empty array with 5 eleemnts
    Array <int> a1;
    a1.push_back(1);
    a1.push_back(2);
    a1.push_back(3);
    a1.push_back(4);
    a1.push_back(5);

    // WHEN trying to accesS 0th element (check low boundary)
    // THEN it equals the first value we put into the array (1)
    ASSERT_EQ(a1[0], 1);

    // GIVEN the same array
    // WHEN trying to change value of the 0th element to be equal 10
    a1[0] = 10;

    // THEN it really changes to 10
    ASSERT_EQ(a1[0], 10);


    /* FEATURE #2. CHECK OPERATOR [] WITH NOT EMPTY ARRAY (HIGH BOUNDARY). */
    // GIVEN the same full array
    // WHEN trying to get value of the last (4th) element
    // THEN it equals the last value we put into the array (5)
    ASSERT_EQ(a1[4], 5);

    // GIVEN the same array
    // WHEN trying to change value of the last element to 50
    a1[4] = 50;

    // THEN it equals 50
    ASSERT_EQ(a1[4], 50);


    /* FEATURE #3. CHECK OPERATOR [] WITH NOT EMPTY ARRAY (INDEX OUT OF RANGE). */
    // GIVEN the same full array
    // WHEN trying to get value of non-existing 10th element
    // THEN we have an exception
    ASSERT_ANY_THROW(a1[10]);
    //try { ASSERT_ANY_THROW(a1[10]);} catch (exception &e) { std::cout << e.what();};
  //  try { a1[10];} catch (exception &e) { std::cout << e.what();};

    // GIVEN the same full array
    // WHEN trying to get value of -10 element (just for fun)
    // THEN we have an exception
    ASSERT_ANY_THROW(a1[-10]);

    // GIVEN the same full array
    // WHEN trying to get value of non-existing element with TOOOOOO BIIIIIIIG INDEX
    // THEN we have an exception
    ASSERT_ANY_THROW(a1[10000000000000]);

    // wrong range type
    // GIVEN the same full array
    // WHEN typing some wrong index
    // THEN we have an exception
//    ASSERT_ANY_THROW(a1[3.4]);


    /* FEATURE #4. CHECK OPERATOR [] WITH EMPTY ARRAY. */
    // GIVEN an empty array with no elements
    Array <int> a2;

    // WHEN trying to get value of non-existing 2nd element
    // THEN we have an exception
    ASSERT_ANY_THROW(a2[2]);
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
    ASSERT_EQ(a1.capacity(), size_t(1));
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
    for (size_t i = 0; i<10; i++)
    {
        ASSERT_EQ(a1.at(i) , 10.1);
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

//DISABLED_TEST(ArrayTest, CheckAccess_FrontBack)
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

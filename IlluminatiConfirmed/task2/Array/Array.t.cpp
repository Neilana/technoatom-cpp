// useful headers
#include "gtest/gtest.h"
#include <string>
#include <vector>

// custom headers
#include "Array.h"

using IlluminatiConfirmed::Array;

TEST(ArrayTest, CheckDefaultConstructor)
{
    //test 1
    // given
    Array <int, 10> a1;                 // correct number of elements
    size_t expectedSize = 10;

    //when
    size_t actualSize = a1.size();

    // then
    ASSERT_EQ(actualSize, expectedSize);

    // test 2
    //given
    Array <int, 0> a2;                  // number of elements = 0. Because...why not?
    expectedSize = 0;

    //when
    actualSize = a2.size();

    //then
    ASSERT_EQ(actualSize, expectedSize);
}

TEST(ArrayTest, CheckCopyConstructor)
{
    // given
    Array <int, 6> a1 = {10, 20, 30, 40, 50, 60};
    size_t expectedSize = 6;

    // when
    Array <int, 6> a2(a1);
    size_t actualSize = a2.size();

    // then
    ASSERT_EQ(actualSize, expectedSize);

    // and
    int j = 1;
    for (auto &it : a2)
        ASSERT_EQ(it, j++ * 10);
}

TEST(ArrayTest, CheckAccessWithBrackets)
{
    // given
    Array <int, 6> a1 = {1, 2, 3, 4, 5, 6};

    // when
    size_t correctIndex = 0;
    int expectedValue = 1;

    // then
    ASSERT_EQ(a1[correctIndex], expectedValue);

    // given
    // a1

    // when
    size_t wrongIndexes[3];
    wrongIndexes[0] = 10;
    wrongIndexes[1] = -10;
    wrongIndexes[2] = 10000000000000;

    // then
    for (size_t i = 0; i < 3; i++)
    {
        size_t index = wrongIndexes[i];
        ASSERT_ANY_THROW(a1[index]);
    }
}

TEST(ArrayTest, CheckAccessAt)
{
    Array <int, 6> a1 = {1,2,3,4,5,6};

    // low threshold
    ASSERT_EQ(a1.at(0), 1);    // check read

    a1[0] = 10;
    ASSERT_EQ(a1.at(0), 10);   // check write

    // high threshold
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
    for (size_t i = 0; i < 5; i++)
        a1[i] = i+10;

    Array <double, 5> a2;
    for (size_t i = 0; i < 5; i++)
        a2[i] = i+1000;

    a1.swap(a2);

    for (size_t i = 0; i < 5; i++)
    {
        ASSERT_EQ(a1[i], i+1000);
        ASSERT_EQ(a2[i], i+10);
    }
}

TEST (ArrayTest, CheckAggregateInitialization)
{
    // test 1
    Array<double, 6> a1 = {10,20,30,40,50,60};

    for (size_t i = 0; i < a1.size(); i++)
        ASSERT_EQ(a1.at(i), (i+1)*10);

    // test 2
    Array<double, 6> a2 {10,20,30,40,50,60};

    for (size_t i = 0; i < a2.size(); i++)
        ASSERT_EQ(a2.at(i), (i+1)*10);

    // test 3
    Array<double, 6> a3 ({10,20,30,40,50,60});

    for (size_t i = 0; i < a3.size(); i++)
        ASSERT_EQ(a3.at(i), (i+1)*10);

    Array<double,4> a5 = {10,10.1,10.2,10.3};

    ASSERT_EQ(a5.size(), 4);
    double i = 0;
    for(auto &it : a5)
        ASSERT_EQ(it, 10.0 + i++*0.1);

    Array<double> a6 = {999};

    ASSERT_EQ(a6.size(), 1);
    ASSERT_EQ(a6.at(0), 999);

    Array<int> a7 = 999;

    ASSERT_EQ(a7.size(), 1);
    ASSERT_EQ(a7.at(0), 999);
}


TEST (ArrayIteratorTest, Constractor)
{
    Array<int,7> s1 = {10,20,60,70,80,90,100};
    auto it = s1.begin();

    ASSERT_EQ(*(it), 10);

    const Array<int,7> s2 = {10,20,60,70,80,90,100};
    auto const_it = s2.begin();

    ASSERT_EQ(*(const_it), 10);
}

TEST (ArrayIteratorTest, Increment)
{
    Array<int,7> s1 = {10,20,60,70,80,90,100};
    auto it = s1.begin();

    ASSERT_EQ(*it++, 10);
    ASSERT_EQ(*it,   20);
    ASSERT_EQ(*++it, 60);


    const Array<int,7> const_s1 = {10,20,60,70,80,90,100};
    auto const_it = const_s1.begin();

    ASSERT_EQ(*const_it++, 10);
    ASSERT_EQ(*const_it,   20);
    ASSERT_EQ(*++const_it, 60);
}

TEST (ArrayIteratorTest, OpSum)
{
    Array<int,7> s1 = {10,20,60,70,80,90,100};
    auto it = s1.begin();

    ASSERT_EQ(*(it + 3), 70);


    const Array<int,7> const_s1 = {10,20,60,70,80,90,100};
    auto const_it = const_s1.begin();

    ASSERT_EQ(*(const_it + 3), 70);
}

TEST (ArrayIteratorTest, OpSub)
{
    Array<int,7> s1 = {10,20,60,70,80,90,100};
    auto it = s1.begin();
    ++it; ++it;

    ASSERT_EQ(*(it - 2), 10);


    const Array<int,7> const_s1 = {10,20,60,70,80,90,100};
    auto const_it = const_s1.begin();
    ++const_it; ++const_it;

    ASSERT_EQ(*(const_it - 2), 10);
}

TEST (ArrayIteratorTest, FriendFuncSub)
{
    Array<int,7> s1 = {10,20,60,70,80,90,100};
    auto it1 = s1.begin();
    auto it2 = s1.end();

    ASSERT_EQ(it2 - it1, 7);


    const Array<int,7> const_s1 = {10,20,60,70,80,90,100};
    auto const_it1 = const_s1.begin();
    auto const_it2 = const_s1.end();

    ASSERT_EQ(const_it2 - const_it1, 7);
}

TEST (ArrayIteratorTest, Equal)
{
    Array<int,7> s1 = {10,20,60,70,80,90,100};
    auto it1 = s1.begin();
    auto it2 = s1.begin();

    ASSERT_TRUE(it2 == it1);


    const Array<int,7> const_s1 = {10,20,60,70,80,90,100};
    auto const_it1 = const_s1.begin();
    auto const_it2 = const_s1.begin();

    ASSERT_TRUE(const_it2 == const_it1);
}

TEST (ArrayIteratorTest, NotEqual)
{
    Array<int,7> s1 = {10,20,60,70,80,90,100};
    auto it1 = s1.begin();
    auto it2 = s1.end();

    ASSERT_TRUE(it2 != it1);


    const Array<int,7> const_s1 = {10,20,60,70,80,90,100};
    auto const_it1 = const_s1.begin();
    auto const_it2 = const_s1.end();

    ASSERT_TRUE(const_it2 != const_it1);
}

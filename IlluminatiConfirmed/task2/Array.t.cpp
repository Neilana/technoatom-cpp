// useful headers
#include "gtest/gtest.h"
#include <string>
#include <vector>

// custom headers
#include "Array.h"

using IlluminatiConfirmed::Array;

TEST(ArrayTest, CheckDefaultConstructor)
{
    Array <int, 10> a1;                 // correct number of elements
    ASSERT_EQ(a1.size(), 10);

    Array <int, 0> a2;                  // number of elements = 0. Because...why not?
    ASSERT_EQ(a2.size(), 0);


}

TEST(ArrayTest, CheckCopyConstruct)
{
    Array <int,6> a1 = {10,20,30,40,50,60};
    Array <int,6> a2(a1);
    ASSERT_EQ(a2.size(), 6);
    int j = 1;
    for (auto &it : a2)
        ASSERT_EQ(it, j++*10);
}

TEST(ArrayTest, CheckAccessWithBrackets)
{
    Array <int, 6> a1 = {1,2,3,4,5,6};

    ASSERT_EQ(a1[0], 1);                   // correct range

    ASSERT_ANY_THROW(a1[10]);               // out of range

    ASSERT_ANY_THROW(a1[-10]);              // wrong range type

    ASSERT_ANY_THROW(a1[10000000000000]);   // really wrong range
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

    // test 4
    Array<double, 6> a4 ({10,20});

    ASSERT_EQ(a4.at(0), 10);
    ASSERT_EQ(a4.at(1), 20);
    for (size_t i = 2; i < a3.size(); i++)
        ASSERT_EQ(a4.at(i), 0);

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

TEST (ArrayIteratorsTest, CheckIterators) //эммм..))
{
    //--, ++, +, -
    const Array<double, 6> v0 = {10,20,30,40,50,60};

    IlluminatiConfirmed::Array<double, 6>::const_iterator it0 = v0.begin();

    ASSERT_EQ(v0.at(3) , (*(it0+3)));
    ASSERT_EQ(v0.at(0),(*(it0++)));
    ASSERT_EQ(v0.at(1), (*(it0++)));
    ASSERT_EQ(v0.at(1), (*(it0-1)));
    ASSERT_EQ(v0.at(1), (*(--it0)));
    ASSERT_EQ(v0.at(1), (*(it0--)));

    //begin, end
    Array<double, 6> v1 = {10,20,30,40,50,60};
    size_t i = 0;
    ASSERT_EQ(6,v1.size());
    for (IlluminatiConfirmed::Array<double, 6>::iterator it = v1.begin(); it != v1.end(); it++)
        ASSERT_EQ((*it), ((i++)+1)*10);

    const Array<double, 6> v2 = {10,20,30,40,50,60};

    ASSERT_EQ(6,v2.size());

    //begin, end, ++: check const
    i = 0;
    for (IlluminatiConfirmed::Array<double, 6>::const_iterator it = v2.begin(); it != v2.end(); it++)
    {
        //*it = 10; //It does not compile if all is ok
        ASSERT_EQ((*it), ((i++)+1)*10);
    }

    //[]
    const Array<double, 6> v3 = {10,20,30,40,50,60};

    IlluminatiConfirmed::Array<double, 6>::const_iterator it3 = v3.begin();

    ASSERT_EQ(it3[5], 60);

    //==, !=
    Array<double, 6> v4 = {10,20,30,40,50,60};
    Array<double, 6> v5 = {10,20,30,40,50,60};
    IlluminatiConfirmed::Array<double, 6>::iterator it4 = v4.begin();
    IlluminatiConfirmed::Array<double, 6>::iterator it5 = v5.begin();
    ASSERT_TRUE(it4 != it5);

    ASSERT_FALSE(it4 == it5);

    //>
    Array<double, 6> v6 = {10,20,30,40,50,60};
    IlluminatiConfirmed::Array<double, 6>::iterator it6 = v6.begin();
    IlluminatiConfirmed::Array<double, 6>::iterator it7 = v6.begin();
    it7++;
    ASSERT_TRUE(it6 < it7);

    ASSERT_TRUE(it7 > it6); // And so on .. this is utopia

}

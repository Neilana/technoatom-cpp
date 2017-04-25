#include "gtest/gtest.h"
#include "unique_ptr.h"

using IlluminatiConfirmed::unique_ptr;

TEST(unique_ptrTest, ToperatorPtr)
{
    //given
    unique_ptr<int> p1 ( new int[3] {10, 20, 30} );

    //when
    int expectedValue = 10;
    int actualValue = *p1;

    //then
    ASSERT_EQ(actualValue, expectedValue);
}

TEST(unique_ptrTest, Constructors)
{
    //given
    unique_ptr<int> p1 (new int(123));

    //when
    int expectedValue1 = 123;
    int actualValue1 = *p1;

    //then
    ASSERT_EQ(expectedValue1,actualValue1);

    //given
    unique_ptr<int> p2 (unique_ptr<int>(new int(111)));

    //when
    int expectedValue2 = 111;
    int actualValue2 = *p2;

    //then
    ASSERT_EQ(expectedValue2, actualValue2);

    //given
    unique_ptr<int> p3 = unique_ptr<int>(new int(4321));

    //when
    int expectedValue3 = 4321;
    int actualValue3 = *p3;

    //then
    ASSERT_EQ(expectedValue3, actualValue3);

    //given
    int b1 = 1;
    unique_ptr<int> p4(b1);

    //when
    int expectedValue4 = b1;
    int actualValue4 = *p4;

    //then
    ASSERT_EQ(expectedValue4, actualValue4);

    //given
    int b2 = 3;
    unique_ptr<int> p5 = b2;

    //when
    int expectedValue5 = b2;
    int actualValue5 = *p5;

    //then
    ASSERT_EQ(expectedValue5, actualValue5);
}



TEST(unique_ptrTest, operatorEqual)
{
    //given
    unique_ptr<std::string> p1 (new std::string("Azzazazaz"));
    unique_ptr<std::string> p2;
    //p2 = p1;

    //when doesn't compile

    //then it's ok
}

TEST(unique_ptrTest, operatorThis)
{
    //given
    unique_ptr<std::string> p1 (new std::string("Azzazazaz"));

    //when
    int expectedSize = 9;
    int actualSize = p1->size();

    //then
    ASSERT_EQ(expectedSize, actualSize);
}

TEST(unique_ptrTest, CheckReset)
{
    // given
    unique_ptr<int> p1(new int(2));

    // when
    p1.reset(new int (10));

    std::size_t expectedValue = 10;
    std::size_t actualValue = *p1;

    // then
    ASSERT_EQ(expectedValue, actualValue);
}

TEST(unique_ptrTest, CheckRelease)
{
    // given
    unique_ptr<int> p1(new int(2));

    // when
    int * release = p1.release();

    std::size_t expectedValue = 2;
    std::size_t actualValue = *release;

    // then
    ASSERT_EQ(expectedValue, actualValue);
    delete release;
}

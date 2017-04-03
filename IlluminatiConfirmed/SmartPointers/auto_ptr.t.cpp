#include "gtest/gtest.h"
#include "auto_ptr.h"

using IlluminatiConfirmed::auto_ptr;

TEST(auto_ptrTest, ToperatorPtr)
{
    //given
    auto_ptr<int> p1 ( new int[3] {10, 20, 30} );

    //when
    int expectedValue = 10;
    int actualValue = *p1;

    //then
    ASSERT_EQ(actualValue, expectedValue);
}

TEST(auto_ptrTest, Constructors)
{
    //given
    auto_ptr<int> p1 (new int(123));

    //when
    int expectedValue1 = 123;
    int actualValue1 = *p1;
    
    //then
    ASSERT_EQ(expectedValue1,actualValue1);

    //given
    auto_ptr<int> p2 (auto_ptr<int>(new int(111)));

    //when
    int expectedValue2 = 111;
    int actualValue2 = *p2;

    //then
    ASSERT_EQ(expectedValue2, actualValue2);

    //given
    auto_ptr<int> p3 = auto_ptr<int>(new int(4321));

    //when
    int expectedValue3 = 4321;
    int actualValue3 = *p3;

    //then
    ASSERT_EQ(expectedValue3, actualValue3);

    //given
    int b1 = 1;
    auto_ptr<int> p4(b1);

    //when
    int expectedValue4 = b1;
    int actualValue4 = *p4;

    //then
    ASSERT_EQ(expectedValue4, actualValue4);

    //given
    int b2 = 3;
    auto_ptr<int> p5 = b2;

    //when
    int expectedValue5 = b2;
    int actualValue5 = *p5;

    //then
    ASSERT_EQ(expectedValue5, actualValue5);
}



TEST(auto_ptrTest, operatorEqual)
{
    //given
    auto_ptr<std::string> p1 (new std::string("Azzazazaz"));
    auto_ptr<std::string> p2;
    p2 = p1;

    //when
    std::string expectedValue1 = "Azzazazaz";
    std::string actualValue1 = *p2;

    //then
    ASSERT_EQ(expectedValue1, actualValue1);
    //ASSERT_ANY_THROW(p1->size()); Crash -> it's ok
}

TEST(auto_ptrTest, operatorThis)
{
    //given
    auto_ptr<std::string> p1 (new std::string("Azzazazaz"));

    //when
    int expectedSize = 9;
    int actualSize = p1->size();

    //then
    ASSERT_EQ(expectedSize, actualSize);
}

TEST(auto_ptrTest, CheckReset)
{
    // given
    auto_ptr<int> p1(new int(2));

    // when
    p1.reset(new int (10));

    std::size_t expectedValue = 10;
    std::size_t actualValue = *p1;

    // then
    ASSERT_EQ(expectedValue, actualValue);
}

TEST(auto_ptrTest, CheckRelease)
{
    // given
    auto_ptr<int> p1(new int(2));

    // when
    int * release = p1.release();

    std::size_t expectedValue = 2;
    std::size_t actualValue = *release;

    // then
    ASSERT_EQ(expectedValue, actualValue);
    delete release;
}

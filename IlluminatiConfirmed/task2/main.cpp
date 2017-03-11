#include <iostream>
#include "gtest/gtest.h"
#include "Array.h"
#include "bugnumbers.h"
using IlluminatiConfirmed::Array;
using IlluminatiConfirmed::BugNumbers;

int main(int argc, char *argv[])
{
    //::testing::InitGoogleTest(&argc, argv);
    // запускаем только определённый тест (чтобы проще смотреть дампы)
    //::testing::GTEST_FLAG(filter) = "ArrayTest2*";
    //return RUN_ALL_TESTS();

    typedef BugNumbers<int,0> Int;

    Int num1 = {1};
    Int num2 = {2};
    Int num3 = {1};
    num3 = num1*num2;
    num3 = num1*num2;
    num3 = num1*num2;
    num3 = num1*num2;
    num3 = num1*num2;
    num3 = num1/num2;
    num3 = num1/num2;
    num3 = num1/num2;
    num3 = num1/num2;

}

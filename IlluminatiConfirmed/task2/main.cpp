// usefull headers and usings
#include <iostream>
#include "gtest/gtest.h"

// custom headers and usings
#include "Vector.h"
#include "Array.h"
//#include "BugNumbers.h"

using IlluminatiConfirmed::Array;
//using IlluminatiConfirmed::BugNumbers;
using IlluminatiConfirmed::Vector;

int main(int argc, char *argv[])
{
 /*   typedef BugNumbers<int,0> Int;

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
  */
    ::testing::InitGoogleTest(&argc, argv);
    // запускаем только определённый тест (чтобы проще смотреть дампы)
    //::testing::GTEST_FLAG(filter) = "VectorTest3*";
    return RUN_ALL_TESTS();
}

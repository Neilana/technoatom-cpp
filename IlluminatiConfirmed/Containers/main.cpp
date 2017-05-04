// usefull headers and usings
#include <iostream>
#include "gtest/gtest.h"

// custom headers and usings
#include "Vector.h"
#include "Array.h"

using IlluminatiConfirmed::Array;
using IlluminatiConfirmed::Vector;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    // запускаем только определённый тест (чтобы проще смотреть дампы)
    //::testing::GTEST_FLAG(filter) = "VectorTest3*";


    return RUN_ALL_TESTS();
}

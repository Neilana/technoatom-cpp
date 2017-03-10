#include <iostream>
#include "gtest/gtest.h"
#include "Array.h"

using IlluminatiConfirmed::Array;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    // запускаем только определённый тест (чтобы проще смотреть дампы)
    //::testing::GTEST_FLAG(filter) = "ArrayTest2*";
    return RUN_ALL_TESTS();
}

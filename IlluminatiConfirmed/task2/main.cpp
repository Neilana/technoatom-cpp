#include <iostream>
#include "gtest/gtest.h"
#include "Vector.h"

using IlluminatiConfirmed::Vector;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    // запускаем только определённый тест (чтобы проще смотреть дампы)
   // ::testing::GTEST_FLAG(filter) = "VectorTest3*";
    return RUN_ALL_TESTS();
}

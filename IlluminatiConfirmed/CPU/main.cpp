#include <iostream>
#include "gtest/gtest.h"

#include "assembler.h"
#include "../Exceptions/Exception.h"


using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;

    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

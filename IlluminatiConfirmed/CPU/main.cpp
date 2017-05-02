#include <iostream>
#include "gtest/gtest.h"

#include "assembler.h"
#include "../Exceptions/Exception.h"


using namespace std;

int main(int argc, char *argv[])
{
//    IlluminatiConfirmed::Assembler as;
//    try
//    {


//        as.runAssemblerForFile("../cpu_ver3000/savings/test.code");
//        as.saveMemoryToTextFile("../cpu_ver3000/savings/resultVer3000.txt");
//    }
//    catch(IlluminatiConfirmed::Exception &e)
//    {
//        cout <<e.what() << endl;
//    }

//    for (auto &&it : as.getMemory())

//    std:: cout << it << " ";

    cout << "Hello World!" << endl;

    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

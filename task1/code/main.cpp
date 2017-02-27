/**
*   @file       main.cpp
*   @briefi     Task #1: Stack 
*   @details    Implements stack structure. 
*   @author     Alina Voropaeva
*   @date       2017
*/  

// headers
#include <iostream>
#include "gtest/gtest.h"

// my headers
#include "Stack.h"

// simple unit-test
#define MY_TEST( condition )  \
    if ( ! (condition) )    \
    cout << "Test failed: " << #condition << endl;  

using MyNamespace::Stack;
using namespace std;

int main(int argc, char** argv)
{

    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    
    return 0;
}

/**
*   @file       main.cpp
*   @briefi     Task #1: Stack 
*   @details    Implements stack structure. 
*   @author     Alina Voropaeva
*   @date       2017
*/  

// headers
#include <iostream>
#include "/usr/include/gtest/gtest.h"

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

    Stack <int> stack1;
    stack1.push(1); 
    stack1.push(2); 
    stack1.push(3); 
    stack1.push(4); 
    stack1.push(5); 
    stack1.push(6); 
    stack1.push(7); 
    stack1.push(8); 
    stack1.push(9); 
    stack1.push(1); 
    Stack <int> stack2(stack1);
     //   stack2.pop();
    
//  cout << stack1.top()++;
//  MY_TEST(stack1.top() == 4); 

//    ::testing::InitGoogleTest(&argc, argv);
 //   RUN_ALL_TESTS();
    
    return 0;
}

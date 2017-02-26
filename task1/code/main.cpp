/**
*   @file       main.cpp
*   @brief      Task #1: Stack 
*   @details    Implements stack structure. 
*   @author     Alina Voropaeva
*   @date       2017
*/  

// headers
#include<iostream>

// my headers
#include "MyStack.h"

// simple unit-test
#define MY_TEST( condition )  \
    if ( ! (condition) )    \
    cout << "Test failed: " << #condition << endl;   

using namespace std;

int main()
{
	MyStack stack1(6);
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    stack1.push(4);
    stack1.top()++;
//    cout << stack1.top()++;
    MY_TEST(stack1.top() == 4); 
	return 0;

}
	

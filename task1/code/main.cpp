/**
*   @file       main.cpp
*   @brief      Task #1: Stack Implementation
*   @details    Implement stack structure. Test with unit-tests.
*   @author     Alina Voropaeva
*/  
#include<iostream>

#include "MyStack.h"

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
	return 0;

}
	

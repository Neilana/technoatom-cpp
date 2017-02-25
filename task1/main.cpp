#include<iostream>

#include "MyStack.h"

using namespace std;

int main()
{
	MyStack stack1(6);
	MyStack stack2;
	MyStack stack3(1000000000000000);
	stack3.pop();
	stack3.push(60);
	stack3.top();
stack2.top();
	return 0;
}
	

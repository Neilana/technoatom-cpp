#include<iostream>

#include "MyStack.h"

using namespace std;

int main()
{
	MyStack stack1(6);
	MyStack stack3(100000000000000000);
	stack3.push(10);
	stack3.push(11);
	stack3.push(111);
//	stack1.dump("Save st1...\n");
//	stack3.dump("Save st2...\n");
	stack1 = stack3;
//	stack1.dump("Check st1...\n");
//	stack3.dump("Check st2...\n");
	stack1.push(1999);
	return 0;

}
	

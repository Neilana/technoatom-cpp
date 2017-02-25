#include<iostream>

#include "MyStack.h"

using namespace std;

int main()
{
	MyStack stack1(6);
	//cout << stack1.capacity();
	
	int  n;
	cin >> n;
	MyStack stack2(n);
	cout << "Stack 2: "<<	stack2.getCapacity();	

	return 0;
}
	

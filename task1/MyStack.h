#pragma once

#include <iostream>

#include "MyStack.h"

class MyStack
{
public:
	typedef float value_type;
	
	MyStack(int capacity = DEFAULT_CAPACITY);
	~MyStack();

	bool push (value_type value);
	value_type pop();

	int getCapacity() const;

private:
	static const int DEFAULT_CAPACITY = 6;	
	static int stacksCount;

	int m_capacity;
	int m_id;
	
	//zvalue_type m_data[m_capacity];
	value_type *m_data;
	int m_size;
	
	bool isOk() const;
	void dump(const std::string &message = "", bool wantElements = true) const;

};

inline int MyStack::getCapacity() const { return m_capacity; } 

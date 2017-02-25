#include <iostream>
#include <fstream>
#include <limits>
#include <exception>    // std::exception
#include <new>  
#include "MyStack.h"

using namespace std;

// initialize non-const static members
int MyStack::stacksCount = 0;

MyStack::MyStack(int capacity) : m_size(0), m_capacity(0), m_id(stacksCount)
{

	cout << capacity << " " << m_capacity << endl;
	
	cout << std::numeric_limits<int>::max()  << endl;
	int maxCapacity = std::numeric_limits<int>::max();
	
	if (capacity > 0 && capacity < maxCapacity) 
		m_capacity = capacity;
	else 
		m_capacity = DEFAULT_CAPACITY; 
	try 
	{
		m_data = new value_type[m_capacity];
	} catch (std::bad_alloc& e)
	{					 
    		cout << "Hey, sth is wrong! Excpetion caught: " << e.what() << '\n';
	}
	cout << "Stack created! Capacity: " << capacity << " "<<  m_capacity << endl;
	stacksCount++;
}

MyStack::~MyStack()
{
	cout << "Free memory (elements: " << m_size << ", capacity: " << m_capacity << ")\n";
	delete [] m_data;
}


bool MyStack::push(value_type value)
{
	if (m_size >= m_capacity)
		return false;
	// add value
	m_data[m_size++] = value;

	return true;
}

bool MyStack::isOk() const
{
	return (m_size <= m_capacity);
}

void MyStack::dump(const string &message, bool wantElements) const
{
	string fileName = "dumpFile";
	fileName += m_id + ".txt";

	ofstream dumpFile(fileName, std::ios_base::app);
	dumpFile << "Stack #" << m_id << endl;
	if (wantElements)
	{
		if (m_size == 0) 
			dumpFile << "No elements\n";
		//write stack els
	}
//	else
	{
		// just write message + size, capacity
		dumpFile << message << "(Size: " << m_size << ", capacity: " << m_capacity << ")\n\n";
	}
	dumpFile.close();
}

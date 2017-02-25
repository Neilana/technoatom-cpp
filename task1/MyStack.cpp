#include <iostream>
#include <fstream>
#include <limits>
#include <exception>    // std::exception
#include <new>  
#include "MyStack.h"

using namespace std;

// initialize static members
//const int DEFAULT_CAPACITY = 6;
const string MyStack::DUMP_FILE_NAME = "dumpFile.txt";

int MyStack::stacksCount = 0;

MyStack::MyStack(size_t capacity) : m_size(0), m_capacity(0), m_id(stacksCount), m_data(NULL)
{
	cout << capacity << endl;if (stacksCount == 0)
		remove("dumpFile.txt");
	string message = "Creating stack...";	
	try 
	{
		m_data = new value_type[capacity];
		m_capacity = capacity;
		stacksCount++;

		message += " Stack created!\n";	
	} catch (exception& e)
	{					 
		string error = e.what();
    		message += " Hey, sth is wrong! Exception caught: " + error + ". (Input capacity:  " + to_string(capacity) + ")\n";
	}
	dump(message, false);
}

MyStack::~MyStack()
{
	string message = "Freeing memory... ";
	if (m_data != NULL)	
	{
		message += "Success!\n";
		dump(message, true);
		delete [] m_data;
	}
	else
	{
		message += "Nothing to free - memory wasn't allocated.\n";
		dump(message, true);
	}
}


bool MyStack::push(value_type value)
{
	bool ok = false;
	if (m_capacity == 0)
	{
		dump("Trying to push. Hmmmm... Something wrong with this stack! Capacity is 0 :(\n", true);
	}
	else	
	if (m_size >= m_capacity)
	{	
		string message = "Trying to push to full stack (value: " + to_string(value) + ").\n";	
		dump(message, true);
	}
	else
		m_data[m_size++] = value, ok = true;

	return ok;

}

MyStack::value_type MyStack::pop()
{
	value_type result = 0;	
	if (m_capacity == 0)
		dump("Trying to pop. Hmmmm... Something wrong with this stack! Capacity is 0 :(\n", true);
else	
	if (m_size > 0)
		result = m_data[--m_size];	
	else
		dump("Trying to pop from empty stack!\n", true);

	return result;
}

bool MyStack::isOk() const
{
	return (m_size <= m_capacity);
}

void MyStack::dump(const string &message, bool wantElements) const
{
	ofstream dumpFile(DUMP_FILE_NAME, std::ios_base::app);
	dumpFile << "Stack #" << m_id << endl;
	dumpFile << "(Size: " << m_size << ", capacity: " << m_capacity << ")\n";
	if (wantElements)
	{
		string elements = "";
		if (m_size == 0) 
			elements = "No elements.\n";
		else
			for (int i = 0; i < m_size; i++)
				elements += "[" +to_string(i) + "] = " + to_string(m_data[i]) + "\n";
		dumpFile << elements;
	}
	// write message + size, capacity
	dumpFile << message << endl;
	dumpFile.close();
}

bool MyStack::empty() const
{
	if (m_size == 0)
		return true;
	else 
		return false;
}

MyStack::value_type MyStack::top() const
{
	value_type result = 0;
	if (m_size > 0 && m_capacity > 0)
		result = m_data[m_size]; 
	else
		dump("Trying to top() for empty stack.\n", true);
	return result; 
}

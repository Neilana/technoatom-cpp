/// @file MyStack.cpp

// headers
#include <iostream>
#include <fstream>
#include <limits>
#include <exception>    // std::exception
#include <new>  

// my headers
#include "MyStack.h"

using namespace std;

// initialize static members
const string MyStack::DUMP_FILE_NAME = "dumpFile.txt";
int MyStack::stacksCount = 0;

/**
*   Creates empty stack with given capacity. If capacity wasn't privided then capacity
*   is equal to MyStack::DEFAULT_CAPACITY. Also assigns new id (MyStack::m_id) which is 
*   equal to the number of already existing stacks.
*
*   @param capacity - maximum number of elements in the stack.
*/
MyStack::MyStack(MyStack::size_type capacity) : m_size(0), m_capacity(0), 
		                        				m_id(stacksCount), m_data(NULL)
{
	if (stacksCount == 0)
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
    	message += " Hey, sth is wrong! Exception caught: " + error + 
	       		   ". (Input capacity:  " + to_string(capacity) + ")\n";
	}
	dump(message);
}

/**
*   Creates new stack as a copy of other stack.
*   
*   @param obj - a reference to a stack that is being used to initialize new stack.  
*/
MyStack::MyStack(const MyStack &obj)
{
	stacksCount++;
	string message = "Creating stack from copy constructor (copy stack #" + 
        			 to_string( obj.id() ) + ")... ";

	m_id = stacksCount;
	m_size = obj.m_size;
	m_capacity = obj.m_capacity;
	try
	{
		m_data = new value_type [m_capacity];

		for (size_type i = 0; i < m_size; i++)
			m_data[i] = obj.m_data[i];

		message += "Success!\n";
	} catch (exception &e)
	{
		string error = e.what();
		message = "We've got some problems! Exception caught: " + error + ".\n";
	}
	dump(message);
}

/**
*   Destroyes current stack. Frees allocated memory for stack elements. Writes result
*   messages in the dump file.
*/
MyStack::~MyStack()
{
	string message = "Freeing memory... ";
	if (m_data != NULL)	
	{
		message += "Success!\n";
		dump(message);
		delete [] m_data;
	}
	else
	{
		message += "Nothing to free - memory wasn't allocated.\n";
		dump(message);
	}
}

/**
*   Adds new value. In case of some problems writes messages in the dump file. Writes 
*   error messages in the dump file.
*   
*   @param value - value to be added in the stack.
*
*   @return @c true - if value was added; 
*   @return @c false - if value was not added. 
*/
bool MyStack::push(const value_type& value)
{
	bool ok = false;
	if (m_capacity == 0)
	{
		dump("Trying to push. Hmmmm... Something wrong with this stack! Capacity is 0 :(\n");
	}
	else	
	if (m_size >= m_capacity)
	{	
		string message = "Trying to push to full stack (value: " + to_string(value) + ").\n";	
		dump(message);
	}
	else
		m_data[m_size++] = value, ok = true;

	return ok;
}

/**
*   Returns and removes the top value from the stack. Writes error messages in the dump 
*   file.
*   
*   @return @c result - the value of the top removed element.
*/
MyStack::value_type MyStack::pop()
{
	value_type result = 0;	
	
	if ( m_size > 0  )
    	result = m_data[--m_size];	
    else
    	dump("Trying to pop from empty stack!\n");

	return result;
}

/**
*   Returns reference ont the top value. Writes error messages in the dump file.
*
*   @return @c result - the reference on the top element.
*/
MyStack::value_type& MyStack::top()
{
    string message = "Trying top()... ";
	value_type *result = NULL;

	if ( m_size > 0 )
		result = &m_data[m_size-1],
        message += "Success! Top element is: " + to_string(*result) +  ".\n"; 
	else
        message = "Stack is empty!\n", result = 0;
    dump(message);

	return *result; 
}

/**
*   Checks whether there's any elements in the stack.
*
*   @return @c true - if stack is empty (no elements);
*   @return @c false - if stack is not empty.
*/
bool MyStack::empty() const
{
	if (m_size == 0)
		return true;
	else 
		return false;
}

/**
*   Check whether stack is valid or not.
*
*   @return @c true - stack is valid;
*   @return @c false - stack is bad :(
*/
bool MyStack::ok() const
{
	return ( (m_capacity > 0) && (m_size <= m_capacity) );
}

/**
*   Writes debug messages to the file. File name is determined by the 
*   MyStack::DUMP_FILE_NAME variable. 
*   
*   @param message - message to write in the file.
*/
void MyStack::dump(const string &message) const
{
    // open dump file and write main info abot the stack
	ofstream dumpFile(DUMP_FILE_NAME, std::ios_base::app);
	dumpFile << "Stack #" << m_id << endl;
	dumpFile << "(Size: " << m_size << ", capacity: " << m_capacity << ")\n";

    // write elements of the stack into a string
	string elements = "";
	if (m_size == 0) 
		elements = "No elements.\n";
	else
		for (size_type i = 0; i < m_size; i++)
			elements += "[" +to_string(i) + "] = " + to_string(m_data[i]) + "\n";
    
    // write elements and message to the file and close it
	dumpFile << elements << message << endl;
	dumpFile.close();
}

MyStack& MyStack::operator=(MyStack &obj2)
{
	string message = "Assignment to stack #" + to_string( obj2.id() ) + "...\n";
	dump(message);
	if (this != &obj2)              // prevent self assignment
	{      
       	m_size = obj2.m_size;
       	m_capacity = obj2.m_capacity;
        if (m_data) 
            delete[] m_data; 
        m_data = new value_type [m_capacity];
        for (MyStack::size_type i = 0; i < m_size; i++) 
        	m_data[i] = obj2.m_data[i];
    }
	
	dump("...assignment completed.\n");
	return *this;
}

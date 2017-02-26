///   @file MyStack.h

// include guard 
#pragma once

// headers
#include <iostream>

/**
*   @class MyStack MyStack.h "MyStack.h"
*   @brief MyStack class.
*
*   My implementation of the stack structure.
*/

class MyStack
{
public:
    // types definition
	typedef float value_type;   ///< type of values stored in stack 
    typedef size_t size_type;   ///< type of indexes used inside the array 
    
    // constructors and destructor			
    MyStack(size_type capacity = DEFAULT_CAPACITY); ///< constructor
	MyStack(const MyStack &obj);                    ///< copy constructor
	~MyStack();                                     ///< destructor
    
    // main functions for stack
	bool push (const value_type&  value);    ///< add value to the stack
	value_type pop();                        ///< get and remove value from the stack
	value_type& top();                       ///< access the top element 	
	bool empty() const;                      ///< check if there's elements in the stack

    // operators overload
	MyStack& operator=(MyStack &obj2);      ///< assignment operator overload

    // getters	
    MyStack::size_type size() const;        ///< returns current number of elemetns in the stack
	MyStack::size_type capacity() const;    ///< returns the maximum number of elements
	MyStack::size_type id() const;          ///< returns id of the stack

private:
    // static class members
	static const size_type DEFAULT_CAPACITY = 6; ///< is used in constructor when capacity wasn't defined
	static const std::string DUMP_FILE_NAME;     ///< name of the file where debug information is stored
	static int stacksCount;                      ///< total amount of created stacks 

    // information about the stack
	size_type m_size;       ///< current number of elements in the stack
	size_type m_capacity;   ///< maximum numbers of elements in the stack
	size_type m_id;         ///< id of the stack 
	
	value_type *m_data;     ///< array of stack values 
	
    // check and debug functions
	bool ok() const;                           ///< check if the stack is valid
	void dump(const std::string &message = "" ) const; ///< write debug info in the file
};

// inline functions implementation
inline MyStack::size_type MyStack::capacity() const { return m_capacity; }
inline MyStack::size_type MyStack::id() const { return m_id; }
inline MyStack::size_type MyStack::size() const { return m_size; }

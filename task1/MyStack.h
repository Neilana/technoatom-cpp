#pragma once

#include <iostream>

class MyStack
{
public:
	typedef float value_type;
        typedef size_t size_type;
			
        MyStack(size_type capacity = DEFAULT_CAPACITY);
	~MyStack();

	bool push (value_type value);
	value_type pop();

	bool empty() const;
	value_type top() const;	
	MyStack::size_type size() const;

	MyStack::size_type capacity() const;
	MyStack::size_type id() const;

	MyStack& operator=(MyStack &obj2);
	void dump(const std::string &message = "", bool wantElements = true) const;

private:
	static const size_type DEFAULT_CAPACITY = 6;
	static const std::string DUMP_FILE_NAME;
	static int stacksCount;

	size_type m_size;
	size_type m_capacity;
	size_type m_id;
	
	value_type *m_data;
	
	bool ok() const;
};

inline MyStack::size_type MyStack::capacity() const { return m_capacity; }
inline MyStack::size_type MyStack::id() const { return m_id; }
inline MyStack::size_type MyStack::size() const { return m_size; }

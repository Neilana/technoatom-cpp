#pragma once

#include <iostream>

class MyStack
{
public:
	typedef float value_type;
	
	MyStack(size_t capacity = DEFAULT_CAPACITY);
	~MyStack();

	bool push (value_type value);
	value_type pop();

	bool empty() const;
	value_type top() const;	
	size_t size() const;		

	size_t capacity() const;
	size_t id() const;


private:
	static const size_t DEFAULT_CAPACITY = 6;	
	static const std::string DUMP_FILE_NAME;
	static int stacksCount;

	size_t m_size;
	size_t m_capacity;
	size_t m_id;
	
	value_type *m_data;
	
	bool isOk() const;
	void dump(const std::string &message = "", bool wantElements = true) const;

};

inline size_t MyStack::capacity() const { return m_capacity; } 
inline size_t MyStack::id() const { return m_id; } 
inline size_t MyStack::size() const { return m_size; } 

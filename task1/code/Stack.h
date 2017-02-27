/// @file Stack.h

// include guard 
#pragma once

// headers
#include <iostream>

/**
*   @class Stack Stack.h "Stack.h"
*   @brief Stack class.
*
*   My implementation of the stack structure.
*/
namespace MyNamespace
{
    class Stack
    {
    public:
        // types definition
        typedef float value_type;   ///< type of values stored in stack 
        typedef size_t size_type;   ///< type of indexes used inside the array 
        
        // constructors and destructor
        Stack(size_type capacity = DEFAULT_CAPACITY);   ///< constructor
        Stack(const Stack &obj);                        ///< copy constructor
        ~Stack();                                       ///< destructor
        
        // main functions for stack
        void push (const value_type&  value);   ///< add value to the stack
        void pop();                             ///< remove value from the stack
        value_type& top();                      ///< access the top element     
        bool empty() const;                     ///< check if there's elements in the stack

        // operators overload
        Stack& operator=(const Stack &obj2);          ///< assignment operator overload

        // getters  
        Stack::size_type capacity() const;
        Stack::size_type size() const;          ///< returns current number of elemetns in the stack
        Stack::size_type id() const;            ///< returns id of the stack

    private:
        // static class members
        static const size_type DEFAULT_CAPACITY = 6;///< is used in constructor when capacity wasn't defined
        static const size_type INCREMENT_CAPACITY = 6;
        static const value_type POISON_VALUE;
        static const std::string DUMP_FILE_NAME;    ///< name of the file where debug information is stored
        static int stacksCount;                     ///< total amount of created stacks 

        // information about the stack
        size_type m_size;       ///< current number of elements in the stack
        size_type m_capacity;   ///< maximum numbers of elements in the stack
        size_type m_id;         ///< id of the stack 
        
        value_type *m_data;     ///< array of stack values 
        
        // check and debug functions
        bool ok() const;                                    ///< check if the stack is valid
        void dump(const std::string &message = "" ) const;  ///< write debug info in the file
    };

    // inline functions implementation
    inline Stack::size_type Stack::capacity() const { return m_capacity; }
    inline Stack::size_type Stack::id() const { return m_id; }
    inline Stack::size_type Stack::size() const { return m_size; }
}

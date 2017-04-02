/// @file Stack.h

// include guard 
#pragma once

//  macroses
//#define DEBUG_ON
#if defined(DEBUG_ON)
#define DUMP(ch) do {this->dump(string(__PRETTY_FUNCTION__)+string(" ")+string(ch));} while(0);
#else
#define DUMP(ch)
#endif

// headers
#include <iostream>
#include <fstream>
#include <limits>
#include <exception>        // exception
#include <new>  
#include <algorithm>        // swap
#include <ctime>            // time for dump file

/* STACK: CLASS INTERFACE */

/**
*   @class Stack Stack.h "Stack.h"
*   @brief Stack class.
*
*   My implementation of the stack structure.
*/
namespace MyNamespace
{
    template <class T>
    class Stack
    {
    public:
        // types definition
        // FYI: Мне кажется, это уже излишне:
        //    1) объем памяти, занимаемой стеком >> sizeof(size_t)
        //    2) размер стека (capacity) не может быть больше, чем size_t, если мы конечно не биты в нем храним.
        typedef size_t size_type;   ///< type of indexes used inside the array 
        
        // constructors and destructor
        Stack(size_type capacity = DEFAULT_CAPACITY);   ///< constructor
        Stack(const Stack<T> &obj);                     ///< copy constructor
        ~Stack();                                       ///< destructor
        
        // main functions for stack
        void push (const T&  value);   ///< add value to the stack
        void pop();                    ///< remove value from the stack
        T& top();                      ///< access the top element     
        bool empty() const;            ///< check if there's elements in the stack

        // operators overload
        Stack<T>& operator=(const Stack<T> obj2);    ///< assignment operator overload

        // getters
        size_type capacity() const { return m_capacity; }
        size_type size() const { return m_size; }  ///< returns current number of elements in the stack
        size_type id() const { return m_id; }     ///< returns id of the stack

        std::string writeElementsToString() const;

    private:
        // static class members
        static const size_type DEFAULT_CAPACITY = 6;///< is used in constructor when capacity wasn't defined
        static const size_type INCREMENT_CAPACITY = 6;  ///< add this number to the current capacity when stack is full
        static const T POISON_VALUE;                ///< instead of deleted elements

        // FYI: В чем смысл этой переменной?! Если посмотреть, сколько стеков создается разными неявными вызовами конструкторов,
        // то логично в деструкторе уменьшать это число и убедится, что все сходится к 0.
        static int stacksCount;                     ///< total amount of created stacks 

        // information about the stack
        size_type m_size;       ///< current number of elements in the stack
        size_type m_capacity;   ///< maximum numbers of elements in the stack
        size_type m_id;         ///< id of the stack 
        
        T *m_data;     ///< array of stack values 
        
        std::string dumpFileName;   ///< name of the file where debug information is stored

        // check and debug functions
        bool ok() const;                                    ///< check if the stack is valid
        void dump(const std::string &message = "" ) const;  ///< write debug info in the file
    };

    // inline functions implementation
/*    template <class T>
    inline Stack<T>::size_type Stack<T>::capacity() const { return m_capacity; }

    template <class T>
    inline Stack<T>::size_type Stack<T>::id() const { return m_id; }

    template <class T>
    inline Stack<T>::size_type Stack<T>::size() const { return m_size; }*/
}


/* STACK: TEMPLATE FUNCTIONS IMPLEMENTATION */

using MyNamespace::Stack;

// лучше так, чем using namespace?
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::to_string;
using std::exception;

// initialize static members
template <class T>
int Stack<T>::stacksCount = 0;

/**
*   Creates empty stack with given capacity. If capacity wasn't privided then capacity
*   is equal to Stack::DEFAULT_CAPACITY. Also assigns new id (Stack::m_id) which is 
*   equal to the number of already existing stacks.
*
*   @param capacity - number of elements in the stack.
*/
template <class T>
Stack<T>::Stack(Stack::size_type capacity) : m_size(0), m_capacity(capacity),
                 m_id(stacksCount), m_data(NULL), dumpFileName("")
{
    /* FIXME: Мне кажется не логичным фиксировать имя файла с дампом. А если несколько программ
    параллельно захочется запустить?!

    + Обычно в таких случаях генерят имя файла, содержащее текущие дату/время и какую-нибудь
    случайную последовательность. + ко всему,

    - дампить всегда - плохое решение. Это отнимает время. Дампить надо только в дебаг режиме.
    Поэтому dump лучше делать макросом, печатающим только тогда, когда мы явно задали константу DEBUG при компиляции программы.
    - Впоследствии это все хорошо бы заменить логгером с несколькими приоритетами сообщений.*/

    // make new dump filename
    time_t nowTime = time(0);
    struct tm nowInfo = *localtime(&nowTime);
    char nowStr1 [40];

    strftime(nowStr1, 40, "%F %T", &nowInfo);
    string nowStr2 (nowStr1);
    dumpFileName = "dumps/"+ nowStr2;

    string message = "Creating stack...";   
    try 
    {
        // Вообще убрала POISON
        m_data = new T[DEFAULT_CAPACITY];
        stacksCount++;

        message += " Stack created!\n"; 
    } catch (exception& e)
    {                    
        string error = e.what();
        message += " Hey, sth is wrong! Exception caught: " + error; 
    }
    DUMP(message);
}

/**
*   Creates new stack as a copy of other stack.
*   
*   @param obj - a reference to a stack that is being used to initialize new stack.  
*/
template <class T>
Stack<T>::Stack(const Stack &obj)
{
    stacksCount++;
    m_id = stacksCount;
    m_size = obj.m_size;
    m_capacity = obj.m_capacity;
    try
    {
        m_data = new T [m_size];

       /* for (size_type i = 0; i < m_size; i++)
            m_data[i] = obj.m_data[i];*/
        memcpy( m_data, obj.m_data, sizeof(T) * m_size );
    } catch (exception &e)
    {
        // FIXME: Такого рода исключения лучше кидать наружу. А то ты фактически замалчиваешь проблему.
        /* не понимаю, как сделать обработку исключений. Если у меня new не сработает,
        то без try программа вылетит. Я понимаю, что мне надо исползовать throw и ловить
        снаружи, но не понимаю как это реализовать. Мне из catch надо кидать ещё одно
        исключение? */
        string error = e.what();
        string message = "We've got some problems! Exception caught: " + error + ".\n" +
                         __FUNCTION__ + " line: " + std::to_string(__LINE__) + "\n";
        DUMP(message);
    }
}

/**
*   Destroyes current stack. Frees allocated memory for stack elements. Writes result
*   messages in the dump file.
*/
template <class T>
Stack<T>::~Stack()
{
    DUMP("Freeing memory...\n");
    if (m_data != NULL) 
        delete [] m_data;
}

/**
*   Adds new value. In case of some problems writes messages in the dump file. Writes 
*   error messages in the dump file.
*   
*   @param value - value to be added in the stack.
*/
template <class T>
void Stack<T>::push(const T& value)
{
    if  (m_size >= m_capacity)
    {
        Stack <T> bufStack(*this);
        if (m_data) 
            delete [] m_data;
        m_capacity += INCREMENT_CAPACITY;
        try
        {
            m_data = new T [m_capacity];
            for (size_type i = 0; i < bufStack.m_size; i++)
                m_data[i] = bufStack.m_data[i];
            
            m_data[m_size++] = value;
        } catch (exception &e)
        {
            string error = e.what();
            string message = "Trying to push()... Exception caught: " + error + ".\n";
            DUMP(message);
        }
    }
    else
        m_data[m_size++] = value;
}

/**
*   Removes the top value from the stack. Writes error messages in the dump
*   file.
*/
template <class T>
void Stack<T>::pop()
{
    if (!empty())
        m_size--;
    else
    {
        DUMP("Trying pop()... Stack is empty!\n");
    }
}

/**
*   Returns reference on the top value. Writes error messages in the dump file.
*
*   @return @c result - the reference on the top element.
*/
template <class T>
T& Stack<T>::top()
{
    T *result = &m_data[0];     // we always have address of the 0th element

    if (!empty())
        result = &m_data[m_size-1];
    else
    {
        DUMP("Trying top()... Stack is empty!\n");
    }

    return *result; 
}

/**
*   Checks whether there's any elements in the stack.
*
*   @return @c true - if stack is empty (no elements);
*   @return @c false - if stack is not empty.
*/
template <class T>
bool Stack<T>::empty() const
{
    return (m_size == 0);
}

/**
*   Check whether stack is valid or not.
*
*   @return @c true - stack is valid;
*   @return @c false - stack is bad :(
*/
template <class T>
bool Stack<T>::ok() const
{
    return ( (m_size <= m_capacity) && (m_data != NULL) );
}

/**
*   Writes debug messages to the file. File name is determined by the 
*   Stack::DUMP_FILE_NAME variable. 
*   
*   @param message - message to write in the file.
*/
template <class T>
void Stack<T>::dump(const string &message) const
{
    // FYI: Лучше держать файл с логами всегда открытым и писать туда когда нужно.

    // open dump file and write main info abot the stack
   // std::ofstream dumpFile(dumpFileName);
    std::ofstream dumpFile(dumpFileName, std::ios_base::app);
    dumpFile << "Stack #" << m_id << endl;
    dumpFile << "(Size: " << m_size << ", capacity: " << m_capacity << ")\n";

    // write elements of the stack into a string
    string elements = "";
    if (m_size > 0) 
        for (size_type i = 0; i < m_size; i++)
            elements += "[" +to_string(i) + "] = " + to_string(m_data[i]) + "\n";

    // write elements and message to the file and close it
    dumpFile << elements << message << endl;
    dumpFile.close();
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T> obj2)
{
    // copy-swap
    // Не знаю почему, но оно компилилось...
    swap(m_size, obj2.m_size);
    swap(m_capacity, obj2.capacity);
    swap(m_data, obj2.m_data);
    
    return *this;
}

template <class T>
string Stack<T>::writeElementsToString() const
{
    string elements = "";
    if (m_size > 0)
       for (size_type i = 0; i < m_size; i++)
           elements += "    [" +to_string(i) + "] = " + to_string(m_data[i]) + "\n";
    return elements;
}

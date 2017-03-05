#pragma once

#define NAME_VAR(VAR) #VAR
#define DEBUG_ON
#if defined(DEBUG_ON)
    #define DUMP(ch) do {dump(string(__PRETTY_FUNCTION__)+string(ch));} while(0); //FIXME add line
    #define ASSERT_OK(cond) do { if (!cond)  {dump(string(__PRETTY_FUNCTION__) + string(" ")+ string(#cond));}} while(0);
    #define ASSERT_STR(str) do { dump(string(__PRETTY_FUNCTION__) + string(" ")+ str);} while(0);
#else
    #define ASSERT_OK(cond) do { if (!cond)  { assert(cond);}} while(0);
    #define ASSERT_STR(str) do { assert(!str);} while(0); //Ops
#define DUMP(ch)
#endif

#include <iostream>
#include <cassert>
using std::size_t;
using std::string;

namespace IlluminatiConfirmed
{
    template <class Tp> //FIXME Why class? How should dump works?
    class Array
    {
    public:
        /*!
         * \brief Array Constructs an empty array
         */
        Array();
        /*!
         * \brief Array Constructs a array with a size
         * \param size The size of the new array
         */
        Array(size_t capacity);
        /*!
         * \brief Array Overload
         * \param capacity
         * \param def Initialization with the default value
         */
        Array(size_t capacity, const Tp & def);
        /*!
         * \brief Array Copy constractor
         * \param other What is copied
         */
        Array(const Array<Tp> &other);
        ~Array();
        /*!
         * \brief operator = Assigns rhs to this vector
         * \param rhs The right array
         * \return Returns a reference to this vector
         */
        Array<Tp> & operator=(const Array<Tp> &rhs);
        /*!
         * \brief operator [] Returns the item at index position i as a modifiable reference.
         * \param i Must be a valid index position in the array.
         * \return Value
         */
        const Tp & operator[](size_t index) const;
        /*!
         * \brief operator [] Overload, denide access to a const value
         * \param index
         * \return
         */
        Tp & operator[](size_t index) { DUMP("in/out"); return const_cast<Tp &>(static_cast<const Array &>(*this)[index]);}
        /*!
         * \brief operator == Two vectors are considered equal if they contain the same values in the same order.
         *                    This function requires the value type to have an implementation of operator==().
         * \param rhs Right operand
         * \return Returns true if other is equal to this vector; otherwise returns false.
         */
        bool operator==(const Array<Tp> &rhs) const;
        /*!
         * \brief max_size Returns the maximum number of items that can be stored in the vector without forcing a reallocation.
         * \return Value
         */
        inline size_t max_size() const { DUMP("in/out"); return m_capacity;}
        /*!
         * \brief empty Returns true if the array has size 0; otherwise returns false.
         * \return True or false
         */
        inline bool empty() const { DUMP("in/out"); return m_capacity == 0;}
        /*!
         * \brief dump Debug information about the array's container
         * \param func Name of the function from which dump is called
         */
        void dump(std::string str) const;
        size_t size() const { DUMP("in/out"); return m_size; } //FIXME Mb it's number of uninitialized elements.. Just count for push, [] and other
        size_t capacity() const { DUMP("in/out"); return m_capacity; }
        void push_back(const Tp& value);
        Tp& at(size_t index) const;

    private:
        Tp *m_data;
        size_t m_size;
        size_t m_capacity;
        const size_t INCREMENT_CAPACITY = 5;
    };
}

#include <string>
#include <exception>
#include <new>
#include <fstream>
using std::exception;
using IlluminatiConfirmed::Array;

template <class Tp>
Array<Tp>::Array() : m_data(NULL), m_size(0), m_capacity(0)
{
    DUMP("in/out");
}

template <class Tp>
Array<Tp>::Array(size_t capacity) : m_data(NULL), m_size(0), m_capacity(0)
{
    DUMP("in");
    try
    {
        m_data = new Tp[capacity];
        m_capacity = capacity;
    } catch (exception& e)
    {
        ASSERT_STR(string(e.what()));
    }
    DUMP("out");
}

template<class Tp>
Array<Tp>::Array(size_t capacity, const Tp &def) : m_data(NULL), m_size(0), m_capacity(capacity)
{
    DUMP("in");
    try
    {
        m_data = new Tp[m_capacity];
        for (size_t i = 0; i<m_capacity; i++)
        {
            m_data[i] = def;
        }
    } catch (exception& e)
    {
        ASSERT_STR(string(e.what()));
    }
    DUMP("out");
}

template<class Tp>
Array<Tp>::Array(const Array<Tp> &other) :
    m_data(NULL),
    m_size(other.m_size),
    m_capacity(other.m_capacity)
{
    DUMP("in");
    try
    {
        m_data = new Tp[m_size];
        memcpy(m_data, other.m_data, sizeof(Tp) * m_capacity);
    } catch (exception &e)
    {
        ASSERT_STR(string(e.what()));
    }
    DUMP("out");
}

template<class Tp>
Array<Tp> &Array<Tp>::operator=(const Array<Tp> &rhs)
{
    DUMP("in");
    if (this != &rhs)
    {
        try
        {
            Tp *temp_data = new Tp [rhs.m_capacity];
            memcpy(temp_data, rhs.m_data, sizeof(Tp) * rhs.m_capacity);
            delete [] m_data;

            m_data = temp_data;
            m_capacity = rhs.m_capacity;
            m_size = rhs.m_size;
        } catch (exception &e)
        {
            ASSERT_STR(string(e.what()));
        }
    }
    DUMP("out");
    return *this;
}


template <class Tp>
Array<Tp>::~Array()
{
    DUMP("in");
    if (m_data != NULL)
        delete [] m_data;
    DUMP("out");
}


template <class Tp>
void Array<Tp>::push_back(const Tp& value)
{

    DUMP("in");
    Array <Tp> bufArr(*this);
    if (m_data != NULL)
        delete [] m_data;

    m_capacity++;// = INCREMENT_CAPACITY; //push_back should add a new element at the end.
    try
    {
        m_data = new Tp [m_capacity];
        memcpy(m_data, bufArr.m_data, sizeof(Tp) * m_capacity-1);
        m_data[m_capacity-1] = value;
    } catch (exception &e)
    {
        ASSERT_STR(string(e.what()));
    }
    DUMP("out");
}

template <class Tp>
const Tp& Array<Tp>::operator[](size_t index) const
{
    DUMP("in mb out");
    ASSERT_OK((index < m_capacity));
    if (index < m_capacity)
    {

        return m_data[index];
    }
    else
    {
        ASSERT_OK(!"Out of range");
        throw std::out_of_range("ERRROOOORRRRR");
    }
}

template<class Tp>
bool Array<Tp>::operator==(const Array<Tp> &rhs) const
{
    DUMP("in");
    //ASSERT_OK(rhs!= NULL&&rhs!=nullptr); //FIXME Maybe it's too much
    try
    {
        if (m_data == rhs.m_data)
            return true;
        if (m_capacity != rhs.m_capacity)
            return false;
        for (size_t i = 0; i < m_capacity; i++)
        {
            if (m_data[i] != rhs.m_data[i])
                return false;
        }
    } catch (exception &e)
    {
        ASSERT_STR(string(e.what()));
    }
    DUMP("out");
    return true;
}

template <class Tp>
Tp& Array<Tp>::at(size_t index) const
{
    DUMP("in mb out");
    ASSERT_OK((index < m_capacity));
    if (index < m_capacity)
        return m_data[index];
    else
    {
        ASSERT_OK(!"Out of range");
        throw std::out_of_range("ERRROOOORRRRR");
    }
}

template<class Tp>
void IlluminatiConfirmed::Array<Tp>::dump(string str) const
{
    std::ofstream file;
    file.open("dump_Array.txt",std::ofstream::out | std::ofstream::app);
    if(file.is_open())
    {
        auto space = [](unsigned int i) ->string {
            string sp = "";
            while (i-->0) sp += "    ";
            return sp;};
        std::time_t result = std::time(nullptr);
        file<<std::asctime(std::localtime(&result))<<std::endl;
        file<<"Array::"<<str<<std::endl<<"{"<<std::endl;
        file<<space(1)<<NAME_VAR(m_capacity)<<" = "<<m_capacity<<std::endl;
        file<<space(1)<<NAME_VAR(m_data)<<" "<<m_capacity<<std::endl;
        file<<space(2)<<"{"<<std::endl;
        if(!(m_data == NULL))
        {for (size_t j = 0; j < m_capacity;j++)
        {
            file<<space(2)<<"["<<j<<"]"<<" = "<<m_data[j]<<std::endl;
        }
        }
        file<<space(2)<<"}"<<std::endl;
        file<<space(1)<<"}"<<std::endl;
    }
    file.close();
}

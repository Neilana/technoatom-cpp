/// \file Array.h

// include guard
#pragma once

// macroses
#define NAME_VAR(VAR) #VAR
#define DEBUG_ON
#if defined(DEBUG_ON)
    #define DUMP(ch) do {dump(string(__PRETTY_FUNCTION__)+string(" ")+string(ch));} while(0);
    #define ASSERT_OK(cond) do { if (!cond)  {dump(string(__PRETTY_FUNCTION__) + string(" ")+ string(#cond));}} while(0);
    #define ASSERT_STR(str) do { dump(string(__PRETTY_FUNCTION__) + string(" ")+ str);} while(0);
#else
    #define ASSERT_OK(cond) do { if (!cond)  { assert(cond);}} while(0);
    #define ASSERT_STR(str) do { assert(!str);} while(0); //Ops Neilana: не разбиралась что здесь
#define DUMP(ch)
#endif

// usefull headers
#include <iostream>
#include <cassert>
#include <string>
#include <exception>
#include <new>
#include <fstream>
#include <ctime>

using std::size_t;
using std::string;
using std::exception;

// Illuminati Confirmed namespace and Array class declaration
namespace IlluminatiConfirmed
{
    template <class Tp>
    class Array
    {
    public:
        // constructors, destructors and assignment
        /*!
         * \brief Array Constructs an empty array
         */
        Array();

        /*!
         * \brief Array Overload
         * \param capacity
         * \param def Initialization with the default value
         */
        Array(size_t capacity, const Tp & def = Tp());

        /*!
         * \brief Array Copy constractor
         * \param other What is copied
         */
        Array(const Array<Tp> &other);

        Array(std::initializer_list<Tp> l);
        ~Array();

        /*!
         * \brief operator = Assigns rhs to this vector
         * \param rhs The right array
         * \return Returns a reference to this vector
         * \author penguinlav
         */
        Array<Tp> & operator=(const Array<Tp> &rhs);

        void assign (size_t capacity, const Tp& value);

        // element access
        /*!
         * \brief operator [] Returns the item at index position i as a modifiable reference.
         * \param i Must be a valid index position in the array.
         * \return Value
         * \author Neilana
         */
        const Tp & operator[](size_t index) const;

        // Neilana: крутой способ! \m/
        /*!
         * \brief operator [] Overload, denide access to a const value
         * \param index
         * \return
         * \author penguinlav
         */
        Tp & operator[](size_t index) { DUMP("in/out"); return const_cast<Tp &>(static_cast<const Array &>(*this)[index]);}

        /*!
         * \brief Returns a reference to the element at specified location pos, with bounds checking.
         * \param index position of element to return
         * \return reference to the requested element
         * \author Neilana
         */
        Tp& at(size_t index) const;

        /*!
         * \brief returns a reference to the first element
         * \return reference to the first element
         * \author Neilana
         */
        Tp& front() { if (m_data) return m_data[0]; }

        const Tp& front() const
        {
            DUMP("in/out");
            return const_cast<Tp &>(static_cast<const Array &>(*this)->front());
        }

        /*!
         * \brief returns reference to the last element
         * \return reference to the last element
         * \author Neilana
         */
        Tp& back() { DUMP("in/out"); if (m_data[m_size]) return m_data[m_size]; }

        const Tp& back() const
        {
            DUMP("in/out");
            return const_cast<Tp &>(static_cast<const Array &>(*this)->back());
        }

        // capacity
        /*!
         * \brief returns the maximum number of elements the container is able to hold due to system or library implementation limitations.
         * \return maximum number of elements.
         * \author Neilana
         */
        //inline size_t max_size() const { DUMP("in/out"); return m_capacity;}
        inline size_t max_size() const { DUMP("in/out"); return size_t(-1)/sizeof(Tp); }

        /*!
         * \brief empty Returns true if the array has size 0; otherwise returns false.
         * \return True or false
         * \author penguinlav
         */
        inline bool empty() const { DUMP("in/out"); return m_capacity == 0;}

        size_t size() const { DUMP("in/out"); return m_size; } //FIXME Mb it's number of uninitialized elements.. Just count for push, [] and other

        size_t capacity() const { DUMP("in/out"); return m_capacity; }

        /*!
         * \brief increase the capacity to a value that's greater or equal to new capacity
         * \param capacity new capacity
         * \author Neilana
         */
        void reserve(size_t capacity);

        // modifiers
        void push_back(const Tp& value);
        void pop_back();
        void clear();
        void swap (Array <Tp> & other);
        void resize( size_t capacity, Tp value = Tp() );

        // other functions
        /*!
         * \brief dump Debug information about the array's container
         * \param func Name of the function from which dump is called
         * \author penguinlav
         */
        void dump(std::string str) const;

        // operators overload
        /*!
         * \brief operator == Two vectors are considered equal if they contain the same values in the same order.
         *                    This function requires the value type to have an implementation of operator==().
         * \param rhs Right operand
         * \return Returns true if other is equal to this vector; otherwise returns false.
         * \author penguinlav
         */
        bool operator==(const Array<Tp> &rhs) const;

    private:
        Tp *m_data;
        size_t m_size;
        size_t m_capacity;
        const size_t INCREMENT_CAPACITY = 5;
    };
}

// Array class implementation
using IlluminatiConfirmed::Array;

template <class Tp>
Array<Tp>::Array() : m_data(nullptr), m_size(0), m_capacity(0)
{
    DUMP("in/out");
}

template<class Tp>
Array<Tp>::Array(size_t capacity, const Tp& def) : m_data(nullptr), m_size(0), m_capacity(0)
{
    DUMP("in");
    try
    {
        m_data = new Tp[capacity];
        m_capacity = capacity;
        m_size = capacity;

        for (size_t i = 0; i < m_capacity; i++)
            m_data[i] = def;
    } catch (exception& e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp>
Array<Tp>::Array(const Array<Tp> &other) :
    m_data(nullptr),
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
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp>
Array<Tp>::Array(std::initializer_list<Tp> l) :
    Array(l.size())
{
    DUMP("in");
        size_t i = 0;
        for (auto it = l.begin(); it!=l.end(); it++)
        {
            this->m_data[i++] = *it;
        }
    DUMP("out");
}

template<class Tp>
Array<Tp>& Array<Tp>::operator=(const Array<Tp> &rhs)
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
            ASSERT_STR( string(e.what()) );
        }
    }
    DUMP("out");
    return *this;
}

template <class Tp>
Array<Tp>::~Array()
{
    DUMP("in");
    if (m_data != nullptr)
        delete [] m_data;
    m_data = nullptr;
    DUMP("out");
}

template <class Tp>
void Array<Tp>::push_back(const Tp& value)
{
    DUMP("in");
    if (m_size == m_capacity)
        reserve(m_capacity + INCREMENT_CAPACITY);
    m_data[m_size++] = value;
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
void Array<Tp>::dump(string str) const
{
    std::ofstream file;
    file.open("dump_Array.txt",std::ofstream::out | std::ofstream::app);
    if(file.is_open())
    {
        // Neilana: зачёёёётная лямбда \m/
        auto space = [](unsigned int i) -> string
        {
            string sp = "";
            while (i-- > 0) sp += "    ";
            return sp;
        };
        std::time_t result = std::time(nullptr);
        file << std::asctime(std::localtime(&result)) << std::endl;

        file << "Array::" << str << std::endl << "{" << std::endl;
        file << space(1) << NAME_VAR(m_capacity) << " = " << m_capacity << std::endl;
        file << space(1) << NAME_VAR(m_size) << " " << m_size << std::endl;
        file << space(1) << NAME_VAR(m_data) << " " << m_capacity << std::endl;
        file << space(2) << "{" << std::endl;

        if (m_data != nullptr)
        {
            for (size_t j = 0; j < m_capacity;j++)
                file << space(2) << "[" << j << "]" << " = " << m_data[j] << std::endl;
        }
        file << space(2) << "}" << std::endl;
        file << space(1) << "}" << std::endl;
    }
    file.close();
}

template<class Tp>
void Array<Tp>::reserve(size_t capacity)
{
    if (capacity > m_capacity)
    {
        DUMP("in");
        Array bufArr(*this);
        if (m_data != nullptr)
            delete [] m_data;

        m_capacity = capacity;
        try
        {
            m_data = new Tp [m_capacity];
            memcpy(m_data, bufArr.m_data, sizeof(Tp) * m_capacity-1);
        } catch (exception &e)
        {
            ASSERT_STR( string(e.what()) );
        }

        DUMP("out");
    }
}

template<class Tp>
void Array<Tp>::assign(size_t capacity, const Tp& value)
{
    reserve(capacity);

    m_size = capacity;
    for (size_t i = 0; i < capacity; i++)
        m_data[i] = value;
}

template<class Tp>
void Array<Tp>::pop_back()
{
   if (m_size > 0)
       m_size--;
}

template<class Tp>
void Array<Tp>::clear()
{
   m_size = 0;
}

template<class Tp>
void Array<Tp>::swap(Array <Tp> & other)
{
    DUMP("in");
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_size, other.m_size);
    std::swap(m_data, other.m_data);
    DUMP("out");
}

template<class Tp>
void Array<Tp>::resize(size_t capacity, Tp value)
{
    DUMP("in");
    if (m_size > capacity)
        m_size = capacity;
    else
    {
        reserve(capacity);

        for (size_t i = m_size; i < capacity; i++)
            m_data[i] = value;
        m_size = capacity;
    }
    DUMP("out");
}

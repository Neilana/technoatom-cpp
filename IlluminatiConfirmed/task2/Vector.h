/// \file Vector.h

// include guard
#pragma once

// macroses
#define NAME_VAR(VAR) #VAR
#define DEBUG_ON
#if defined(DEBUG_ON)
    #define DUMP(ch) do {this->dump(string(__PRETTY_FUNCTION__)+string(" ")+string(ch));} while(0);
    #define ASSERT_OK(cond) do { if (!cond)  {this->dump(string(__PRETTY_FUNCTION__) + string(" ")+ string(#cond));}} while(0);
    #define ASSERT_STR(str) do { this->dump(string(__PRETTY_FUNCTION__) + string(" ")+ str);} while(0);
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

using std::size_t;
using std::string;
using std::exception;

#include "BaseContainer.h"
using IlluminatiConfirmed::BaseContainer;

// Illuminati Confirmed namespace and Vector class declaration
namespace IlluminatiConfirmed
{
    template <class Tp>
    class Vector : public BaseContainer<Tp>
    {
    public:
        // constructors, destructors and assignment
        /*!
         * \brief Vector Constructs an empty vector
         */
        Vector();

        /*!
         * \brief Vector Overload
         * \param capacity
         * \param def Initialization with the default value
         */
        Vector(size_t capacity, const Tp & def = Tp());

        /*!
         * \brief Vector Copy constractor
         * \param other What is copied
         */
        Vector(const Vector<Tp> &other);

        Vector(std::initializer_list<Tp> l);
        ~Vector();

        /*!
         * \brief operator = Assigns rhs to this vector
         * \param rhs The right vector
         * \return Returns a reference to this vector
         * \author penguinlav
         */
        Vector<Tp> & operator=(const Vector<Tp> &rhs);

        void assign (size_t capacity, const Tp& value);

        // element access
        /*!
         * \brief returns a reference to the first element
         * \return reference to the first element
         * \author Neilana
         */
        Tp& front() { if (m_data) return m_data[0]; }

        const Tp& front() const
        {
            DUMP("in/out");
            return const_cast<Tp &>(static_cast<const Vector &>(*this)->front());
        }

        /*!
         * \brief returns reference to the last element
         * \return reference to the last element
         * \author Neilana
         */
        Tp& back() { DUMP("in/out"); if (m_data[this->m_size]) return m_data[this->m_size]; }

        const Tp& back() const
        {
            DUMP("in/out");
            return const_cast<Tp &>(static_cast<const Vector &>(*this)->back());
        }

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
        void swap (Vector <Tp> & other);
        void resize( size_t capacity, Tp value = Tp() );

        // operators overload
        /*!
         * \brief operator == Two vectors are considered equal if they contain the same values in the same order.
         *                    This function requires the value type to have an implementation of operator==().
         * \param rhs Right operand
         * \return Returns true if other is equal to this vector; otherwise returns false.
         * \author penguinlav
         */
       // bool operator==(const Vector<Tp> &rhs) const;

    private:
        Tp *m_data;
        size_t m_capacity;
        const size_t INCREMENT_CAPACITY = 5;
    };
}

// Vector class implementation
using IlluminatiConfirmed::Vector;

template <class Tp>
Vector<Tp>::Vector() :  BaseContainer<Tp>(), m_data(nullptr), m_capacity(0)
{
    DUMP("in/out");
}

template<class Tp>
Vector<Tp>::Vector(size_t capacity, const Tp& def) : BaseContainer<Tp>(def), m_data(nullptr), m_capacity(0)

{
    DUMP("in");
    try
    {
        m_data = new Tp[capacity];
        m_capacity = capacity;

        this->m_size = capacity;
        this->m_dataPtr = m_data;

        for (size_t i = 0; i < m_capacity; i++)
            m_data[i] = def;
    } catch (exception& e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp>
Vector<Tp>::Vector(const Vector<Tp> &other) :
    BaseContainer<Tp>(other),
    m_data(nullptr),
    //this->m_size(other.this->m_size),
    m_capacity(other.m_capacity)

{
    DUMP("in");
    try
    {
        m_data = new Tp[this->m_size];
        this->m_dataPtr = m_data;

        memcpy(m_data, other.m_data, sizeof(Tp) * m_capacity);
    } catch (exception &e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp>
Vector<Tp>::Vector(std::initializer_list<Tp> initList) : BaseContainer<Tp>(initList), m_data(nullptr), m_capacity(0)
    /*Vector(initList.size()),  */
{
    DUMP("in");
    try
    {
        m_capacity = initList.size();
        this->m_size = initList.size();

        m_data = new Tp[this->m_size];
        this->m_dataPtr = m_data;

        size_t i = 0;
        for (auto it = initList.begin(); it != initList.end(); it++)
        {
            m_data[i++] = *it;
        }
    } catch (exception &e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp>
Vector<Tp>& Vector<Tp>::operator=(const Vector<Tp> &rhs)
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
            this->m_dataPtr = m_data;
            m_capacity = rhs.m_capacity;
            this->m_size = rhs.m_size;
        } catch (exception &e)
        {
            ASSERT_STR( string(e.what()) );
        }
    }
    DUMP("out");
    return *this;
}

template <class Tp>
Vector<Tp>::~Vector()
{
    DUMP("in");
    if (m_data != nullptr)
        delete [] m_data;
    m_data = nullptr;
    this->m_dataPtr = nullptr;
    DUMP("out");
}

template <class Tp>
void Vector<Tp>::push_back(const Tp& value)
{
    DUMP("in");
    if (this->m_size == m_capacity)
        reserve(m_capacity + INCREMENT_CAPACITY);
    m_data[this->m_size++] = value;
    DUMP("out");

}

template<class Tp>
void Vector<Tp>::reserve(size_t capacity)
{
    if (capacity > m_capacity)
    {
        DUMP("in");
        Vector bufArr(*this);
        if (m_data != nullptr)
            delete [] m_data;

        m_capacity = capacity;
        try
        {
            m_data = new Tp [m_capacity];
            this->m_dataPtr = m_data;
            std::copy(bufArr.begin(),bufArr.end(),this->begin());
            //memcpy(m_data, bufArr.m_data, sizeof(Tp) * m_capacity-1);
        } catch (exception &e)
        {
            ASSERT_STR( string(e.what()) );
        }

        DUMP("out");
    }
}

template<class Tp>
void Vector<Tp>::assign(size_t capacity, const Tp& value)
{
    reserve(capacity);

    this->m_size = capacity;
    for (size_t i = 0; i < capacity; i++)
        m_data[i] = value;
}

template<class Tp>
void Vector<Tp>::pop_back()
{
   if (this->m_size > 0)
       this->m_size--;
}

template<class Tp>
void Vector<Tp>::clear()
{
   this->m_size = 0;
}

template<class Tp>
void Vector<Tp>::swap(Vector <Tp> & other)
{
    DUMP("in");
    std::swap(m_capacity, other.m_capacity);
    std::swap(this->m_size, other.m_size);
    std::swap(m_data, other.m_data);
    DUMP("out");
}

template<class Tp>
void Vector<Tp>::resize(size_t capacity, Tp value)
{
    DUMP("in");
    if (this->m_size > capacity)
        this->m_size = capacity;
    else
    {
        reserve(capacity);

        for (size_t i = this->m_size; i < capacity; i++)
            m_data[i] = value;
        this->m_size = capacity;
    }
    DUMP("out");
}

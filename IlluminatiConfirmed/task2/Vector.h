/// \file Vector.h

// include guard
#pragma once

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

        /*!
         * \brief Vector Constructs with aggregate list. If the compiler supports C++11 initializer lists.
         * \param l List
         */
        Vector(std::initializer_list<Tp> l);
        ~Vector();

        /*!
         * \brief operator = Assigns rhs to this vector
         * \param rhs The right vector
         * \return Returns a reference to this vector
         * \author penguinlav
         */
        Vector<Tp> & operator=(const Vector<Tp> &rhs);

        /*!
         * \brief assign FIXME: Чо то делает
         * \param capacity
         * \param value
         * \author Neilana
         */
        void assign (size_t capacity, const Tp& value);

        // element access
        /*!
         * \brief returns a reference to the first element
         * \return reference to the first element
         * \author Neilana
         */
        Tp& front() { if (m_data) return m_data[0]; }

        /*!
         * \brief returns Overload
         * \return reference
         * \author Neilana
         */
        const Tp& front() const { DUMP("in/out"); return const_cast<Tp &>(static_cast<const Vector &>(*this)->front()); }

        /*!
         * \brief returns reference to the last element
         * \return reference to the last element
         * \author Neilana
         */
        Tp& back() { DUMP("in/out"); if (m_data[this->m_size]) return m_data[this->m_size]; }

        /*!
         * \brief back Overload
         * \return
         * \author Neilana
         */
        const Tp& back() const { DUMP("in/out"); return const_cast<Tp &>(static_cast<const Vector &>(*this)->back()); }

        /*!
         * \brief capacity Returns the maximum number of characters that can be stored in the string without forcing a reallocation.
         * \return Capacity
         */
        size_t capacity() const { DUMP("in/out"); return m_capacity; }

        /*!
         * \brief increase the capacity to a value that's greater or equal to new capacity
         * \param capacity new capacity
         * \author Neilana
         */
        void reserve(size_t capacity);

        /*!
         * \brief push_back Inserts value at the end of the vector.
         * \param value
         */
        void push_back(const Tp& value);

        /*!
         * \brief pop_back Removes the last item in the vector. Calling this function is
         *      equivalent to calling remove(size() - 1). The vector must not be empty.
         *      If the vector can be empty, call isEmpty() before calling this function.
         */
        void pop_back();

        /*!
         * \brief clear Removes all the elements from the vector and doesn't release
         *      the memory used by the vector. For releasing use for example "vector<T>().swap(x);"
         */
        void clear();

        /*!
         * \brief swap Swaps vector other with this vector. This operation is very fast and never fails.
         * \param other
         */
        void swap (Vector <Tp> & other);

        /*! //FIXME: aaaazazzazzzzzaazaz
         * \brief resize Resizes the container so that it contains n elements.
                  If n is smaller than the current container size, the content
                  is reduced to its first n elements, removing those beyond (and destroying them).
                  If n is greater than the current container size, the content
                  is expanded by inserting at the end as many elements as needed
                  to reach a size of n. If val is specified, the new elements are
                  initialized as copies of val, otherwise, they are value-initialized.
                  If n is also greater than the current container capacity, an automatic
                  reallocation of the allocated storage space takes place.
                  Notice that this function changes the actual content of the container
                  by inserting or erasing elements from it.
         * \param capacity
         * \param value
         */
        void resize( size_t capacity, Tp value = Tp() );
    private:
        Tp *m_data;
        size_t m_capacity;
        const size_t INCREMENT_CAPACITY = 5;
    };
}

// Vector class implementation
using IlluminatiConfirmed::Vector;

template <class Tp>
Vector<Tp>::Vector() : BaseContainer<Tp>(nullptr, 0), m_data(nullptr), m_capacity(0)
{
    DUMP("in/out");
}

template<class Tp>
Vector<Tp>::Vector(size_t capacity, const Tp& def) : BaseContainer<Tp>(nullptr, 0), m_data(nullptr), m_capacity(0)

{
    DUMP("in");
    try
    {
        m_data = new Tp[capacity];
        m_capacity = capacity;

        this->m_size = capacity;
        this->m_dataPtr = m_data;

        for (auto it = this->begin(); it != this->end(); it++)
            *it = def;
    } catch (exception& e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp>
Vector<Tp>::Vector(const Vector<Tp> &other) :
    BaseContainer<Tp>(nullptr, other.m_capacity),
    m_data(nullptr),
    //this->m_size(other.this->m_size),
    m_capacity(other.m_capacity)

{
    DUMP("in");
    try
    {
        m_data = new Tp[this->m_size];
        this->m_dataPtr = m_data;
        std::copy(other.begin(),other.end(),this->begin());
        //memcpy(m_data, other.m_data, sizeof(Tp) * this->m_size);
    } catch (exception &e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp>
Vector<Tp>::Vector(std::initializer_list<Tp> initList) : BaseContainer<Tp>(nullptr, initList.size()), m_data(nullptr), m_capacity(initList.size())
    /*Vector(initList.size()),  */
{
    DUMP("in");
    try
    {
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
        Vector temp(rhs);
        swap(temp);
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
    for (auto it = this->begin(); it != this->end(); it++)
        *it = value;
}

template<class Tp>
void Vector<Tp>::pop_back()
{
   if (this->m_size > 0)
       --(this->m_size);
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
    std::iter_swap(this->begin(),other.begin());
    std::swap(m_data, other.m_data);
    std::swap(this->m_dataPtr, other.m_dataPtr);
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

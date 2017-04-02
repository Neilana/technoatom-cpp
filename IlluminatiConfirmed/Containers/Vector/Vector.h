/// \file Vector.h

// include guard
#pragma once

// usefull headers and usings
#include <iostream>
#include <cassert>
#include <string>
#include <exception>
#include <new>
#include <fstream>
#include <cstring>

using std::size_t;
using std::string;
using std::exception;

// custom headers and usings
#include "ContainerInterface.h"

using IlluminatiConfirmed::ContainerInterface;

// Illuminati Confirmed namespace and Vector class declaration
namespace IlluminatiConfirmed
{
    template <class Tp>
    class Vector : public ContainerInterface<Tp>
    {
    public:
        typedef typename ContainerInterface<Tp>::iterator iterator;
        typedef typename ContainerInterface<Tp>::const_iterator const_iterator;

        // constructors, destructors and assignment
        /*!
         * \brief Vector Constructs an empty vector
         */
        Vector();

        Vector(size_t capacity);

        /*!
         * \brief Vector Overload
         * \param capacity
         * \param def Initialization with the default value
         */
        Vector(size_t capacity, const Tp & def);

        /*!
         * \brief Vector Copy constructor
         * \param other What is copied
         */
        Vector(const Vector<Tp> &other);

        /*!
         * \brief Vector Constructs with aggregate list. If the compiler supports C++11 initializer lists.
         * \param l List
         */
        Vector(const std::initializer_list<Tp> &l);
        ~Vector();

        /*!
         * \brief operator = Assigns rhs to this vector
         * \param rhs The right vector
         * \return Returns a reference to this vector
         * \author penguinlav
         */
        Vector<Tp> & operator=(const Vector<Tp> &rhs);

        /*!
         * \brief assign replaces the contents of the container.
         * \param capacity the new size of the container
         * \param value the value to initialize elements of the container with
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

        /*!
         * \brief resize resizes the container to contain count elements.
         * \param capacity new size of the container
         * \param value the value to initialize the new elements with
         * \author Neilana
         */
        void resize( size_t capacity, Tp value = Tp() );

        /*!
         * \brief new Allocates requested number of bytes.
         * \param size number of bytes to allocate
         * \param init the value to initialize the new elements with
         */
        void* operator new(size_t size, int init = 0);
        void* operator new[](size_t size, int init = 0);

        /*!
         * \brief insert inserts elements from range [first, last) before pos
         * \param pos Position
         * \param first Iterator
         * \param last Iterator
         * \return Iterator pointing to the last inserted value
         */
        iterator insert(iterator pos, const_iterator first, const_iterator last)
        {
            DUMP("in");

            std::ptrdiff_t offset = pos - this->begin();
            std::ptrdiff_t diff = last - first;
            if (this->m_size + diff > m_capacity)
            {
                reserve(m_capacity + ((diff > INCREMENT_CAPACITY) ? diff : INCREMENT_CAPACITY));
            }
            this->m_size += diff;
            for (auto it = this->end() - diff; it != this->begin() + offset - 1; --it)
            {
                *(it + diff) = *(it);
            }
            for(auto it = this->begin()+offset; it != this->begin() + diff + offset; ++it)
            {
                *it = *(first++);
            }
            DUMP("out");
            return this->begin() + offset + diff;
        }

        /*!
         * \brief insert Overload: inserts value before pos
         * \param index
         * \param value
         * \return
         */
        iterator insert(size_t index, const Tp & value)
        {
            return insert(this->begin() + index, const_iterator(&value), const_iterator(&value + 1));
        }

        /*!
         * \brief insert Overload: inserts elements from initializer list ilist before pos
         * \param index
         * \param l
         * \return
         */
        iterator insert(size_t index, const std::initializer_list<Tp> &l)
        {
            return insert(this->begin() + index, l.begin(), l.end());
        }
    private:
        Tp *m_data;                 /// pointer to the first element
        size_t m_capacity;          /// current maximum capacity of the vector
        const size_t INCREMENT_CAPACITY = 5; /// used when new memory allocated
    };

    // bool
    template <>
    class Vector <bool> : public ContainerInterface<bool>
    {
    public:
        typedef class Iterator <bool> iterator;

//        Vector();
        Vector(size_t capacity = 0);
        Vector(size_t capacity, const bool & def);
        Vector(const Vector<bool> &other);
        Vector(std::initializer_list<bool> l);
        ~Vector();
        Vector<bool> & operator=(const Vector<bool> &rhs);
        void assign (size_t capacity, const bool& value);
        BitPointer front() { if (m_data) return BitPointer(m_data, 0); }
        BitPointer back() { DUMP("in/out"); if (m_data) return BitPointer(m_data, this->m_size); }
        size_t capacity() const { /*DUMP("in/out"); */return m_capacity; }
        void reserve(size_t capacity);
        void push_back(const bool& value);
        void pop_back() { if (this->m_size > 0) --(this->m_size); }
        void clear() { this->m_size = 0; }
        void swap (Vector <bool> & other);
        void resize( size_t capacity, bool value = false );
    private:
        unsigned char * m_data;
        size_t m_capacity;
    };
}

// include template class implementation
#include "Vector.hpp"

#pragma once

#include <iostream>
#include <cassert>
using std::size_t;

namespace IlluminatiConfirmed
{
    template <class Tp>
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
        Array(size_t size);
        Array(const Array<Tp> &other) = default;
        ~Array();
        Array<Tp> & operator=(const Array<Tp> &rhs) = default;
        /*!
         * \brief operator [] Returns the item at index position i as a modifiable reference.
         * \param i Must be a valid index position in the array.
         * \return Value
         */
        Tp & operator[](size_t index) const;
        /*!
         * \brief max_size Returns the maximum number of items that can be stored in the vector without forcing a reallocation.
         * \return Value
         */
        inline size_t max_size() const;
        /*!
         * \brief empty Returns true if the array has size 0; otherwise returns false.
         * \return True or false
         */
        inline bool empty() const;
        /*!
         * \brief dump Debug information about the array's container
         * \param func Name of the function from which dump is called
         */
        void dump(std::string str) const;

        size_t size() const { return m_size; };
        size_t capacity() const { return m_capacity; };
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
#include <exception>        // exception
#include <new>
using std::string;
using std::exception;
using IlluminatiConfirmed::Array;

template <class Tp>
Array<Tp>::Array() : m_data(NULL), m_size(0), m_capacity(0)
{

}

template <class Tp>
Array<Tp>::Array(size_t capacity) : m_data(NULL), m_size(0), m_capacity(0)
{
    try
    {
        m_data = new Tp[capacity];
        m_capacity = capacity;
    } catch (exception& e)
    {
        string error = e.what();
    }
}

template <class Tp>
Array<Tp>::~Array()
{
    if (m_data != NULL)
        delete [] m_data;
}


template <class Tp>
void Array<Tp>::push_back(const Tp& value)
{
    if  (m_size >= m_capacity)
    {
        Array <Tp> bufArr(*this);
        if (m_data)
            delete [] m_data;
        m_capacity += INCREMENT_CAPACITY;
        try
        {
            m_data = new Tp [m_capacity];
            for (size_t i = 0; i < bufArr.m_size; i++)
                m_data[i] = bufArr.m_data[i];

            m_data[m_size++] = value;
        } catch (exception &e)
        {
            string error = e.what();
        }
    }
    else
        m_data[m_size++] = value;
}

template <class Tp>
Tp& Array<Tp>::operator[](size_t index) const
{
    if ((index < m_size) && (index < m_capacity))
        return m_data[index];
    else
        throw std::out_of_range("ERRROOOORRRRR");
}


template <class Tp>
Tp& Array<Tp>::at(size_t index) const
{
    if ((index < m_size) && (index < m_capacity))
        return m_data[index];
    else
        throw std::out_of_range("ERRROOOORRRRR");
}

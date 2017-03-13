/// \file Array.h

// include guard
#pragma once

// usefull headers and usings
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

// custom headers and usings
#include "ContainerInterface.h"
#include "Iterator.h"

using IlluminatiConfirmed::ContainerInterface;
using IlluminatiConfirmed::Iterator;

// Illuminati Confirmed namespace and Array class declaration
namespace IlluminatiConfirmed
{
    template <class Tp, size_t TpSize>
    class Array : public ContainerInterface<Tp>
    {
    public:
        typedef class IlluminatiConfirmed::Iterator <Tp const> const_iterator;
        typedef class IlluminatiConfirmed::Iterator <Tp> iterator;

        /*!
         * \brief Array Constract array with def value
         * \param def Initialization with the default value
         */
        Array(const Tp & def = Tp());

        /*!
         * \brief Array Copy constractor
         * \param other What is copied
         */
        Array(const Array<Tp, TpSize> &other);

        /*!
         * \brief Array Constructs with aggregate list. If the compiler supports C++11 initializer lists.
         * \param l List
         */
        Array(std::initializer_list<Tp> l);
        ~Array();

        /*!
         * \brief operator = Assigns rhs to this vector
         * \param rhs The right array
         * \return Returns a reference to this vector
         * \author penguinlav
         */
        Array<Tp, TpSize> & operator=(const Array<Tp, TpSize> &rhs);

        /*!
         * \brief swap Swaps other array with this array. This operation is very fast and never fails.
         * \param other
         */
        void swap (Array <Tp, TpSize> & other);

    private:
        Tp m_data[TpSize];          /// array of elements
    };
}

// Array class implementation
using IlluminatiConfirmed::Array;

template<class Tp, size_t TpSize>
Array<Tp, TpSize>::Array(const Tp& def) : ContainerInterface<Tp>(m_data, TpSize)
{    DUMP("in");
    try
    {
        for (size_t i = 0; i < TpSize; i++)
            m_data[i] = def;
        this->m_dataPtr = m_data; this->m_size = TpSize;
    } catch (exception& e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp, size_t TpSize>
Array<Tp, TpSize>::Array(const Array<Tp, TpSize> &other) : ContainerInterface<Tp>(nullptr, TpSize),
    m_data(nullptr)
{
    DUMP("in");
    try
    {
        //m_data = new Tp[TpSize];
        memcpy(m_data, other.m_data, sizeof(Tp) * TpSize);
        this->m_dataPtr = m_data;this->m_size = TpSize;
    } catch (exception &e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp, size_t TpSize>
Array<Tp, TpSize>::Array(std::initializer_list<Tp> initList) : ContainerInterface<Tp>(m_data, initList.size())
{
    DUMP("in");

    if (initList.size() > TpSize)
        throw std::printf("Too large list size.");

    size_t i = 0;
    for (auto it = initList.begin(); it != initList.end(); it++)
        m_data[i++] = *it;

    if (initList.size() < TpSize)
        while (i < TpSize)
            m_data[i++] = Tp();

    this->m_dataPtr = m_data;
    this->m_size = TpSize;

    DUMP("out");
}

template<class Tp, size_t TpSize>
Array<Tp, TpSize>& Array<Tp, TpSize>::operator=(const Array<Tp, TpSize> &rhs)
{
    DUMP("in");
    if (this != &rhs)
    {
        try
        {
            for (size_t i = 0; i < TpSize; i++)
                m_data[i] = rhs.m_data[i];
        } catch (exception &e)
        {
            ASSERT_STR( string(e.what()) );
        }
    }
    DUMP("out");
    return *this;
}

template <class Tp, size_t TpSize>
Array<Tp, TpSize>::~Array()
{
    DUMP("in/out");
    // само удаляется, если оставить - будет ошибка сегментации
}

template<class Tp, size_t TpSize>
void Array<Tp, TpSize>::swap(Array <Tp, TpSize> & other)
{
    DUMP("in");
    iterator it1 = this->begin();
    iterator it2 = other.begin();
    while (it1 != this->end())
    {
        std::iter_swap(it1, it2);
        ++it1;
        ++it2;
    }
    DUMP("out");
}

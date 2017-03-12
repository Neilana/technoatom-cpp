/// \file Array.h

// include guard
#pragma once

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

#include "BaseContainer.h"
using IlluminatiConfirmed::BaseContainer;

// Illuminati Confirmed namespace and Array class declaration
namespace IlluminatiConfirmed
{
    template <class Tp, size_t TpSize>
    class Array : public BaseContainer<Tp>
    {
    public:
        /*!
         * \brief Array Constract array with def value
         * \param capacity
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
         * \brief swap Swaps vector other with this vector. This operation is very fast and never fails.
         * \param other
         */
        void swap (Array <Tp, TpSize> & other);

    private:
        Tp m_data[TpSize];
    };
}

// Array class implementation
using IlluminatiConfirmed::Array;


template<class Tp, size_t TpSize>
Array<Tp, TpSize>::Array(const Tp& def) : BaseContainer<Tp>(m_data, TpSize)
{    DUMP("in");
    try
    {
        //m_data = new Tp[size];
      //  TpSize = size;

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
Array<Tp, TpSize>::Array(const Array<Tp, TpSize> &other) : BaseContainer<Tp>(nullptr, TpSize),
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
Array<Tp, TpSize>::Array(std::initializer_list<Tp> initList) : BaseContainer<Tp>(m_data, initList.size())
{
    DUMP("in");

    if (initList.size() > TpSize)
    {
        throw std::printf("Too large list size.");
        size_t i = 0;
        for (auto it = initList.begin(); it != initList.end(); it++)
        {
            m_data[i++] = *it;
            if (i > TpSize) break; //FIXME
        }
    } else
    {
        size_t i = 0;
        for (auto it = initList.begin(); it != initList.end(); it++)
        {
            m_data[i++] = *it;
        }

        this->m_dataPtr = m_data;
        this->m_size = TpSize;
    }

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
            //Tp *temp_data = new Tp [rhs.TpSize];
            //memcpy(temp_data, rhs.m_data, sizeof(Tp) * rhs.TpSize);
            //delete [] m_data;

           // m_data = temp_data;
           // TpSize = rhs.TpSize;
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

    //DUMP("in");
    //if (m_data != nullptr)
     //delete m_data;
    //m_data = nullptr;
    //DUMP("out");
}


template<class Tp, size_t TpSize>
void Array<Tp, TpSize>::swap(Array <Tp, TpSize> & other)
{
    DUMP("in");
    std::iter_swap(this->begin(), other.begin());
    DUMP("out");
}

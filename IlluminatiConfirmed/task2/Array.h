/// \file Array.h

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

// Illuminati Confirmed namespace and Array class declaration
namespace IlluminatiConfirmed
{
    template <class Tp, size_t TpSize>
    class Array : public BaseContainer<Tp>
    {
    public:
        // constructors, destructors and assignment
        /*!
         * \brief Array Constructs an empty array
         */
    //    Array();

        /*!
         * \brief Array Overload
         * \param capacity
         * \param def Initialization with the default value
         */
        Array(const Tp & def = Tp());

        /*!
         * \brief Array Copy constractor
         * \param other What is copied
         */
        Array(const Array<Tp, TpSize> &other);

        Array(std::initializer_list<Tp> l);
        ~Array();

        /*!
         * \brief operator = Assigns rhs to this vector
         * \param rhs The right array
         * \return Returns a reference to this vector
         * \author penguinlav
         */
        Array<Tp, TpSize> & operator=(const Array<Tp, TpSize> &rhs);

        // modifiers
        void swap (Array <Tp, TpSize> & other);

    private:
        //Tp *m_data;
        Tp m_data[TpSize];
        //size_t m_size;
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
    std::swap(m_data, other.m_data);
    DUMP("out");
}

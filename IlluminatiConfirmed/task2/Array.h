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
    template <class Tp, size_t TpSize = 1>
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
Array<Tp, TpSize>::Array(const Tp& def) : ContainerInterface<Tp>(m_data, TpSize) //FIXME:: а если нет конструктора по умолчанию?
{                                                                                //        все же это не универсальное решение
    DUMP("in");

    for(auto &it : *this)
        it = def;

    DUMP("out");
}

template<class Tp, size_t TpSize>
Array<Tp, TpSize>::Array(const Array<Tp, TpSize> &other) : ContainerInterface<Tp>(m_data, TpSize)
{
    DUMP("in");

    std::copy(other.begin(),other.end(),this->begin());

    DUMP("out");
}

template<class Tp, size_t TpSize>
Array<Tp, TpSize>::Array(std::initializer_list<Tp> initList) : ContainerInterface<Tp>(m_data, TpSize)
{
    DUMP("in");

    ASSERT_OK(TpSize <= initList.size());

    auto itThis = this->begin();
    auto itList = initList.begin();
    while (itList != initList.end())
            *(itThis++) = *(itList++);

    if (initList.size() < this->m_size)
        while (itThis != this->end())
            *(itThis++) = Tp();
    DUMP("out");
}

template<class Tp, size_t TpSize>
Array<Tp, TpSize>& Array<Tp, TpSize>::operator=(const Array<Tp, TpSize> &rhs)
{
    DUMP("in");

    if (this != &rhs)
    {
        ASSERT_OK(rhs.size() <= this->size());
        auto itRhs = rhs.begin();
        for (auto &itThis : *this)
            itThis = *(itRhs++);
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

    ASSERT_OK(this->size() == other.size());

    std::swap_ranges(this->begin(),this->end(),other.begin());

    DUMP("out");
}

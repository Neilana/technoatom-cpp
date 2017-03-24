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
        typedef typename ContainerInterface<Tp>::iterator iterator;
        typedef typename ContainerInterface<Tp>::const_iterator const_iterator;

        /*!
         * \brief Array Constructs array with def value
         * \param def Initialization with the default value
         */
        Array();

        /*!
         * \brief Array Constructs with default value
         * \param def
         */
        Array(const Tp& def);
        /*!
         * \brief Array Copy constructor
         * \param other What is copied
         */
        Array(const Array<Tp, TpSize> &other);

        /*!
         * \brief Array Constructs with aggregate list. If the compiler supports C++11 initializer lists.
         * \param l List
         */
        Array(const std::initializer_list<Tp> &l);
        ~Array();

        /*!
         * \brief operator = Assigns rhs to this array
         * \param rhs The right array
         * \return Returns a reference to this array
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

// include template class implementation
#include "Array.hpp"

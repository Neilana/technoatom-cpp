/// \file ContainerInterface.h

// include guard
#pragma once

// macroses
#define UNUSED(var) (void)var;
#define NAME_VAR(VAR) #VAR
//#define DEBUG_ON
#if defined(DEBUG_ON)
#define DUMP(ch) do {this->dump(string(__PRETTY_FUNCTION__)+string(" ")+string(ch));} while(0);
#define ASSERT_OK(cond) do { if (!cond)  {this->dump(string(__PRETTY_FUNCTION__) + string(" ")+ string(#cond));}} while(0);
#define ASSERT_STR(str) do { this->dump(string(__PRETTY_FUNCTION__) + string(" ")+ str);} while(0);
#else
#define ASSERT_OK(cond) do { if (!cond)  { /*assert(cond);*/}} while(0);
#define ASSERT_STR(str) do { printf(str.c_str()); /*assert(!" trouble");*/} while(0);
#define DUMP(ch)
#endif

// usefull headers and usings
#include <iostream>
#include <cassert>
#include <string>
#include <exception>
#include <new>
#include <fstream>
#include <typeinfo>
#include <ctime>

using std::size_t;
using std::string;
using std::exception;

// custom headers
#include "BitPointer.h"               //for ContainerInterface<bool>
#include "Iterator.h"
using IlluminatiConfirmed::BitPointer;
using IlluminatiConfirmed::Iterator;

namespace IlluminatiConfirmed
{
    // for all types except for bool
    template <class Tp>
    class ContainerInterface
    {
    public:
        typedef Iterator <Tp const> const_iterator;
        typedef Iterator <Tp> iterator;

        ContainerInterface(Tp * data_Ptr, size_t size) : m_dataPtr(data_Ptr), m_size (size){ DUMP("in/out");}
        virtual  ~ContainerInterface() = 0;

        // element access
        /*!
         * \brief operator [] Returns the item at index position i as a modifiable reference.
         * \param i Must be a valid index position in the array.
         * \return Value
         * \author Neilana
         */
        const Tp & operator[](size_t index) const;

        /*!
          * \brief operator [] Overload, denide access to a const value
          * \param index
          * \return
          * \author penguinlav
        */
        Tp & operator[](size_t index) { DUMP("in/out"); return const_cast<Tp &>(static_cast<const ContainerInterface &>(*this)[index]);}

        /*!
          * \brief Returns a reference to the element at specified location pos, with bounds checking.
          * \param index position of element to return
          * \return reference to the requested element
          * \author Neilana
          */
        Tp& at(size_t index);

        /*!
          * \brief Returns Overloaded
          * \param index position of element to return
          * \return const reference to the requested element
          * \author penguinlav
          */
        const Tp& at(size_t index) const { DUMP("in/out"); return begin()[index]; }

        // capacity
        /*!
          * \brief empty Returns true if the vector has size 0; otherwise returns false.
          * \return True or false
          * \author penguinlav
          */
        inline bool empty() const { DUMP("in/out"); return this->m_size == 0;}
        /*!
         * \brief size Returns the number of elements in the container.
         * \return The number of elements in the container.
         * \author penguinlav
         */
        size_t size() const { DUMP("in/out"); return this->m_size; }

        /*!
          * \brief returns the maximum number of elements the container is able to hold due to system or library implementation limitations.
          * \return maximum number of elements.
          * \author Neilana
         */
        inline size_t max_size() const { DUMP("in/out"); return size_t(-1)/sizeof(Tp); /*return std::numeric_limits<size_t>::max();*/ }

        // other functions
        /*!
          * \brief dump Debug information about the array's container
          * \param func Name of the function from which dump is called
          * \author penguinlav
          */
        void dump(std::string str) const;

        /*!
          * \brief operator == Two vectors are considered equal if they contain the same values in the same order.
          *                    This function requires the value type to have an implementation of operator==().
          * \param rhs Right operand
          * \return Returns true if other is equal to this vector; otherwise returns false.
          * \author penguinlav
          */
        virtual bool operator==(const ContainerInterface<Tp> &rhs) const;

        //virtual void swap( /*I don't know what the signature should be here*/) = 0;

        /*!
         * \brief begin Returns an STL-style Iterator pointing to the first item in the vector.
         * \return Iterator to begin
         */
        iterator begin() { return iterator(m_dataPtr); }

        /*!
         * \brief end Returns an STL-style Iterator pointing to the imaginary item after the last item in the vector.
         * \return Iterator to end
         */
        iterator end() { return iterator(m_dataPtr + m_size); }

        /*!
         * \brief begin Overload
         * \return
         */
        const_iterator begin() const { return const_iterator(m_dataPtr); }

        /*!
         * \brief end
         * \return
         */
        const_iterator end() const { return const_iterator(m_dataPtr + m_size); }

    protected:
        Tp *m_dataPtr;          /// pointer at the first element
        size_t m_size;          /// the number of elements in the container
    };

    // bool
    template <>
    class ContainerInterface <bool>
    {
        typedef Iterator <bool const> const_iterator;
        typedef Iterator <bool> iterator;
    public:
        ContainerInterface(unsigned char * data_Ptr, size_t size) : m_dataPtr(data_Ptr), m_size (size){ DUMP("in/out"); }
        virtual ~ContainerInterface() {}

        BitPointer operator[](int n) const
        {
            BitPointer result (m_dataPtr, n);
            return result;
        }

        /*!
         * \brief begin Returns an STL-style Iterator pointing to the first item in the vector.
         * \return Iterator to begin
         */
        iterator begin() { return iterator( BitPointer(m_dataPtr, 0) ); }

        /*!
         * \brief end Returns an STL-style Iterator pointing to the imaginary item after the last item in the vector.
         * \return Iterator to end
         */
        iterator end() { return iterator( BitPointer(m_dataPtr, m_size) ); }

        /*!
         * \brief begin Overload
         * \return
         */
        //const_iterator begin() const { return const_iterator( BitPointer(m_dataPtr, 0) ); }

        /*!
         * \brief end
         * \return
         */
        //const_iterator end() const { return const_iterator( BitPointer(m_dataPtr, m_size) ); }
        BitPointer at(size_t index) const { return operator[](index); }
        size_t size() const { /*DUMP("in/out");*/ return this->m_size; }
        inline bool empty() const { DUMP("in/out"); return this->m_size == 0;}
        inline size_t max_size() const { DUMP("in/out"); return size_t(-1)/sizeof(unsigned char);} // !!! * 8 ?
        // other functions
        /*!
          * \brief dump Debug information about the array's container
          * \param func Name of the function from which dump is called
          * \author penguinlav
          */
        void dump(std::string str) const;

    protected:
        unsigned char* m_dataPtr;
        size_t m_size;
    };
}

// inlcude template class implementation
#include "ContainerInterface.hpp"

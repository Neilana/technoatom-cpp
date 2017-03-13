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

using std::size_t;
using std::string;
using std::exception;

// custom headers
#include "Iterator.h"

namespace IlluminatiConfirmed
{
    template <class Tp>
    class ContainerInterface
    {
    public:
        typedef class IlluminatiConfirmed::Iterator <Tp const> const_iterator;
        typedef class IlluminatiConfirmed::Iterator <Tp> iterator;

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
        const Tp& at(size_t index) const { DUMP("in/out"); return this->begin()[index]; }

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
        inline size_t max_size() const { DUMP("in/out"); return size_t(-1)/sizeof(Tp); }

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
        bool operator==(const ContainerInterface<Tp> &rhs) const;

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
}

using IlluminatiConfirmed::ContainerInterface;

template <class Tp>
const Tp& ContainerInterface<Tp>::operator[](size_t index) const
{
    DUMP("in mb out");
    ASSERT_OK((index < m_size));
    if (index < m_size)
    {
         return m_dataPtr[index];
    }
    else
    {
        ASSERT_OK(!"Out of range");
        throw std::out_of_range("ERRROOOORRRRR");
    }
}

template <class Tp>
Tp& ContainerInterface<Tp>::at(size_t index)
{
    DUMP("in mb out");
    ASSERT_OK((index < m_size));
    if (index < m_size)
    {
        return m_dataPtr[index];
    }
    else
    {
        ASSERT_OK(!"Out of range");
        throw std::out_of_range("ERRROOOORRRRR");
    }
}

template<class Tp>
void ContainerInterface<Tp>::dump(string str) const
{
    std::ofstream file;
    file.open("dump.txt",std::ofstream::out | std::ofstream::app);
    if(file.is_open())
    {
        auto space = [](unsigned int i) -> string
        {
            string sp = "";
            while (i-- > 0) sp += "    ";
            return sp;
        };
        std::time_t result = std::time(nullptr);
        file << std::asctime(std::localtime(&result)) << std::endl;

      //  file << "Array::" << str << std::endl << "{" << std::endl;
        file << str << std::endl << "{" << std::endl;
        file << space(1) << NAME_VAR(m_size) << " " << m_size << std::endl;
        file << space(1) << NAME_VAR(m_dataPtr) << " " << m_size << std::endl;
        file << space(2) << "{" << std::endl;
        std::string type(typeid(Tp).name());

        if (m_dataPtr != nullptr)
        {
            if(type.size() < 4)         //I'm tired of catching bugs from the dump
            {
                for (size_t j = 0; j < m_size;j++)
                    file << space(2) << "[" << j << "]" << " = " << m_dataPtr[j] << std::endl;
            }
            else { file<< space(3)<<"I cannot show array. It isn't a primitive data type."<<std::endl;}
        }
        file << space(2) << "}" << std::endl;
        file << space(1) << "}" << std::endl;
    }
    file.close();
}

template<class Tp>
bool ContainerInterface<Tp>::operator==(const ContainerInterface<Tp> &rhs) const
{
    DUMP("in");
    if (m_size != rhs.m_size) return false;
    for (size_t i = 0; i < m_size; i++)
    {
        if (m_dataPtr[i] != rhs.m_dataPtr[i])
        return false;
    }
    DUMP("out");
    return true;
}

template<class Tp>
ContainerInterface<Tp>::~ContainerInterface()
{
    DUMP("in/out");
}

/// \file Array.h

// include guard
#pragma once

// macroses
#define NAME_VAR(VAR) #VAR
#define DEBUG_ON
#if defined(DEBUG_ON)
    #define DUMP(ch) do {dump(string(__PRETTY_FUNCTION__)+string(" ")+string(ch));} while(0);
    #define ASSERT_OK(cond) do { if (!cond)  {dump(string(__PRETTY_FUNCTION__) + string(" ")+ string(#cond));}} while(0);
    #define ASSERT_STR(str) do { dump(string(__PRETTY_FUNCTION__) + string(" ")+ str);} while(0);
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

// Illuminati Confirmed namespace and Array class declaration
namespace IlluminatiConfirmed
{
    template <class Tp, size_t m_size>
    class Array
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
        Array(const Array<Tp, m_size> &other);

        Array(std::initializer_list<Tp> l);
        ~Array();

        /*!
         * \brief operator = Assigns rhs to this vector
         * \param rhs The right array
         * \return Returns a reference to this vector
         * \author penguinlav
         */
        Array<Tp, m_size> & operator=(const Array<Tp, m_size> &rhs);


        // element access
        /*!
         * \brief operator [] Returns the item at index position i as a modifiable reference.
         * \param i Must be a valid index position in the array.
         * \return Value
         * \author Neilana
         */
        const Tp & operator[](size_t index) const;

        // Neilana: крутой способ! \m/
        /*!
         * \brief operator [] Overload, denide access to a const value
         * \param index
         * \return
         * \author penguinlav
         */
        Tp & operator[](size_t index) { DUMP("in/out"); return const_cast<Tp &>(static_cast<const Array &>(*this)[index]);}

        /*!
         * \brief Returns a reference to the element at specified location pos, with bounds checking.
         * \param index position of element to return
         * \return reference to the requested element
         * \author Neilana
         */
        Tp& at(size_t index);

        // capacity
        /*!
         * \brief returns the maximum number of elements the container is able to hold due to system or library implementation limitations.
         * \return maximum number of elements.
         * \author Neilana
         */
        inline size_t max_size() const { DUMP("in/out"); return size_t(-1)/sizeof(Tp); }

        /*!
         * \brief empty Returns true if the array has size 0; otherwise returns false.
         * \return True or false
         * \author penguinlav
         */
        inline bool empty() const { DUMP("in/out"); return m_size == 0;}

        size_t size() const { DUMP("in/out"); return m_size; } //FIXME Mb it's number of uninitialized elements.. Just count for push, [] and other

        // modifiers
        void swap (Array <Tp, m_size> & other);

        // other functions
        /*!
         * \brief dump Debug information about the array's container
         * \param func Name of the function from which dump is called
         * \author penguinlav
         */
        void dump(std::string str) const;

        // operators overload
        /*!
         * \brief operator == Two vectors are considered equal if they contain the same values in the same order.
         *                    This function requires the value type to have an implementation of operator==().
         * \param rhs Right operand
         * \return Returns true if other is equal to this vector; otherwise returns false.
         * \author penguinlav
         */
        bool operator==(const Array<Tp, m_size> &rhs) const;

    private:
        //Tp *m_data;
        Tp m_data[m_size];
        //size_t m_size;
    };
}

// Array class implementation
using IlluminatiConfirmed::Array;


template<class Tp, size_t m_size>
Array<Tp, m_size>::Array(const Tp& def)
{    DUMP("in");
    try
    {
        //m_data = new Tp[size];
      //  m_size = size;

        for (size_t i = 0; i < m_size; i++)
            m_data[i] = def;
    } catch (exception& e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp, size_t m_size>
Array<Tp, m_size>::Array(const Array<Tp, m_size> &other) :
    m_data(nullptr)
{
    DUMP("in");
    try
    {
        m_data = new Tp[m_size];
        memcpy(m_data, other.m_data, sizeof(Tp) * m_size);
    } catch (exception &e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp, size_t m_size>
Array<Tp, m_size>::Array(std::initializer_list<Tp> initList)
{
    DUMP("in");
    size_t i = 0;
    for (auto it = initList.begin(); it != initList.end(); it++)
    {
        m_data[i++] = *it;
    }
    DUMP("out");
}

template<class Tp, size_t m_size>
Array<Tp, m_size>& Array<Tp, m_size>::operator=(const Array<Tp, m_size> &rhs)
{
    DUMP("in");
    if (this != &rhs)
    {
        try
        {
            //Tp *temp_data = new Tp [rhs.m_size];
            //memcpy(temp_data, rhs.m_data, sizeof(Tp) * rhs.m_size);
            //delete [] m_data;

           // m_data = temp_data;
           // m_size = rhs.m_size;
            for (size_t i = 0; i < m_size; i++)
                m_data[i] = rhs.m_data[i];

        } catch (exception &e)
        {
            ASSERT_STR( string(e.what()) );
        }
    }
    DUMP("out");
    return *this;
}

template <class Tp, size_t m_size>
Array<Tp, m_size>::~Array()
{
    // само удаляется, если оставить - будет ошибка сегментации

    //DUMP("in");
    //if (m_data != nullptr)
     //delete m_data;
    //m_data = nullptr;
    //DUMP("out");
}

template <class Tp, size_t m_size>
const Tp& Array<Tp, m_size>::operator[](size_t index) const
{
    DUMP("in mb out");
    ASSERT_OK((index < m_size));
    if (index < m_size)
    {
        return m_data[index];
    }
    else
    {
        ASSERT_OK(!"Out of range");
        throw std::out_of_range("ERRROOOORRRRR");
    }
}

template<class Tp, size_t m_size>
bool Array<Tp, m_size>::operator==(const Array<Tp, m_size> &rhs) const
{
    DUMP("in");
    //ASSERT_OK(rhs!= NULL&&rhs!=nullptr); //FIXME Maybe it's too much
    try
    {
//        if (m_data == rhs.m_data)
 //           return true;
      //  if (m_size != rhs.m_size)
         //   return false;
        for (size_t i = 0; i < m_size; i++)
        {
            if (m_data[i] != rhs.m_data[i])
            return false;
        }
    } catch (exception &e)
    {
        ASSERT_STR(string(e.what()));
    }
    DUMP("out");
    return true;
}

template <class Tp, size_t m_size>
Tp& Array<Tp, m_size>::at(size_t index)
{
    DUMP("in mb out");
    ASSERT_OK((index < m_size));
    if (index < m_size)
    {
        return m_data[index];
    }
    else
    {
        ASSERT_OK(!"Out of range");
        throw std::out_of_range("ERRROOOORRRRR");
    }
}

template<class Tp, size_t m_size>
void Array<Tp, m_size>::dump(string str) const
{
    std::ofstream file;
    file.open("dump_Array.txt",std::ofstream::out | std::ofstream::app);
    if(file.is_open())
    {
        // Neilana: зачёёёётная лямбда \m/
        auto space = [](unsigned int i) -> string
        {
            string sp = "";
            while (i-- > 0) sp += "    ";
            return sp;
        };
        std::time_t result = std::time(nullptr);
        file << std::asctime(std::localtime(&result)) << std::endl;

        file << "Array::" << str << std::endl << "{" << std::endl;
        file << space(1) << NAME_VAR(m_size) << " " << m_size << std::endl;
        file << space(1) << NAME_VAR(m_data) << " " << m_size << std::endl;
        file << space(2) << "{" << std::endl;

        if (m_data != nullptr)
        {
            for (size_t j = 0; j < m_size;j++)
                file << space(2) << "[" << j << "]" << " = " << m_data[j] << std::endl;
        }
        file << space(2) << "}" << std::endl;
        file << space(1) << "}" << std::endl;
    }
    file.close();
}

template<class Tp, size_t m_size>
void Array<Tp, m_size>::swap(Array <Tp, m_size> & other)
{
    DUMP("in");
    std::swap(m_data, other.m_data);
    DUMP("out");
}

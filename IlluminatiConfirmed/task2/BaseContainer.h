/// \file BaseContainer.h

// include guard
#pragma once
#define UNUSED(var) (void)var;
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

template <class Tp>
class iterator;
template <class Tp>
class const_iterator;

namespace IlluminatiConfirmed
{
    template <class Tp>
    class BaseContainer
    {
    public:
        typedef iterator <Tp> iterator;
        typedef const_iterator <Tp> const_iterator;
        BaseContainer(const Tp & def = Tp()) : m_dataPtr(nullptr), m_size (0){ UNUSED(def); DUMP("in/out");}
        BaseContainer(const BaseContainer<Tp> &other) : m_dataPtr(nullptr), m_size(other.m_size) { DUMP("in/out");}

        BaseContainer(std::initializer_list<Tp> l) :m_dataPtr(nullptr),  m_size (l.size()) { DUMP("in/out");}
        virtual  ~BaseContainer() {}

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
         Tp & operator[](size_t index) { DUMP("in/out"); return const_cast<Tp &>(static_cast<const BaseContainer &>(*this)[index]);}

         /*!
          * \brief Returns a reference to the element at specified location pos, with bounds checking.
          * \param index position of element to return
          * \return reference to the requested element
          * \author Neilana
          */
         Tp& at(size_t index);

         // capacity
         /*!
          * \brief empty Returns true if the vector has size 0; otherwise returns false.
          * \return True or false
          * \author penguinlav
          */
         inline bool empty() const { DUMP("in/out"); return this->m_size == 0;}

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

         // operators overload
         /*!
          * \brief operator == Two vectors are considered equal if they contain the same values in the same order.
          *                    This function requires the value type to have an implementation of operator==().
          * \param rhs Right operand
          * \return Returns true if other is equal to this vector; otherwise returns false.
          * \author penguinlav
          */
         bool operator==(const BaseContainer<Tp> &rhs) const;

         iterator begin() { return iterator(m_dataPtr); }
         iterator end() { return iterator(m_dataPtr + m_size); }
         const_iterator begin() const { return const_iterator(m_dataPtr); }
         const_iterator end() const { return const_iterator(m_dataPtr + m_size); }


    protected:
        Tp *m_dataPtr;
        size_t m_size;
    };
}

template <class Tp>
class iterator
 {
public:
    typedef iterator self_type;
    typedef Tp value_type;
    typedef Tp & reference;
    typedef Tp * pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int difference_type;
    iterator() : m_ptr(nullptr) { }
    iterator(pointer ptr) : m_ptr(ptr) { }
    ~iterator() = default;
    inline self_type operator++() { m_ptr++; return *this; }
    inline self_type operator++(int) { self_type i = *this; m_ptr++; return i; }
    inline self_type &operator--() { m_ptr--; return *this; }
    inline self_type operator--(int) { pointer n = m_ptr; m_ptr--; return n; }
    inline reference operator*() const { return *m_ptr; }
    inline pointer operator->() const { return m_ptr; }
    inline bool operator==(const self_type& rhs) const { return m_ptr == rhs.m_ptr; }
    inline bool operator!=(const self_type& rhs) const { return m_ptr != rhs.m_ptr; }
    inline bool operator<(const self_type& other) const { return m_ptr < other.m_ptr; }
    inline bool operator<=(const self_type& other) const { return m_ptr <= other.m_ptr; }
    inline bool operator>(const self_type& other) const { return m_ptr > other.m_ptr; }
    inline bool operator>=(const self_type& other) const { return m_ptr >= other.m_ptr; }
private:
    pointer m_ptr;
 };

template <class Tp>
class const_iterator
{
public:
    typedef const_iterator self_type;
    typedef Tp value_type;
    typedef Tp & reference;
    typedef Tp * pointer;
    typedef int difference_type;
    typedef std::forward_iterator_tag iterator_category;
    const_iterator() : m_ptr(nullptr) { }
    const_iterator(pointer ptr) : m_ptr(ptr) { }
    ~const_iterator() = default;
    inline self_type operator++() { m_ptr++; return *this; }
    inline self_type operator++(int) { self_type i = *this; m_ptr++; return i; }
    inline self_type &operator--() { m_ptr--; return *this; }
    inline self_type operator--(int) { pointer n = m_ptr; m_ptr--; return n; }
    inline const reference operator*() const { return *m_ptr; }
    inline const pointer operator->() const { return m_ptr; }
    inline bool operator==(const self_type& rhs) const { return m_ptr == rhs.m_ptr; }
    inline bool operator!=(const self_type& rhs) const { return m_ptr != rhs.m_ptr; }
    inline bool operator<(const self_type& other) const { return m_ptr < other.m_ptr; }
    inline bool operator<=(const self_type& other) const { return m_ptr <= other.m_ptr; }
    inline bool operator>(const self_type& other) const { return m_ptr > other.m_ptr; }
    inline bool operator>=(const self_type& other) const { return m_ptr >= other.m_ptr; }
private:
    pointer m_ptr;
};

using IlluminatiConfirmed::BaseContainer;

template <class Tp>
const Tp& BaseContainer<Tp>::operator[](size_t index) const
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
Tp& BaseContainer<Tp>::at(size_t index)
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
void BaseContainer<Tp>::dump(string str) const
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

        if (m_dataPtr != nullptr)
        {
            for (size_t j = 0; j < m_size;j++)
                file << space(2) << "[" << j << "]" << " = " << m_dataPtr[j] << std::endl;
        }
        file << space(2) << "}" << std::endl;
        file << space(1) << "}" << std::endl;
    }
    file.close();
}

template<class Tp>
bool BaseContainer<Tp>::operator==(const BaseContainer<Tp> &rhs) const
{
    DUMP("in");
    //ASSERT_OK(rhs!= NULL&&rhs!=nullptr); //FIXME Maybe it's too much
    if (m_size != rhs.m_size) return false;
    try
    {
//        if (m_data == rhs.m_data)
 //           return true;
      //  if (TpSize != rhs.TpSize)
         //   return false;
        for (size_t i = 0; i < m_size; i++)
        {
            if (m_dataPtr[i] != rhs.m_dataPtr[i])
            return false;
        }
    } catch (exception &e)
    {
        ASSERT_STR(string(e.what()));
    }
    DUMP("out");
    return true;
}

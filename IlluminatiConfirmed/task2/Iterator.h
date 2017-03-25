#pragma once

#include "BitPointer.h"
#include <cstddef>

/*!
 * \brief The Iterator class An Iterator is any object that, pointing to some element in
 *              a range of elements (such as an array or a container), has the ability to iterate
 *              through the elements of that range using a set of operators.
 */
namespace IlluminatiConfirmed
{
    template <class Tp>
    class Iterator
    {
    public:
        typedef Iterator self_type;
        typedef Tp value_type;
        typedef Tp & reference;
        typedef Tp * pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;

        Iterator() : m_ptr(nullptr) { }
        Iterator(pointer ptr) : m_ptr(ptr) { }
        ~Iterator() = default;

        inline self_type operator++() { ++m_ptr; return *this; }
        inline self_type operator++(int) { self_type i = *this; ++m_ptr; return i; }
        inline self_type& operator--() { --m_ptr; return *this; }
        inline self_type operator--(int) { pointer n = m_ptr; --m_ptr; return n; }
        inline self_type operator+(int j) const { return self_type(m_ptr + j); }
        inline self_type operator-(int j) const { return self_type(m_ptr - j); }
        inline reference operator*() const { return *m_ptr; }
        inline pointer operator->() const { return m_ptr; }
        inline reference operator[](int j) const { return *(m_ptr + j); }
        inline bool operator==(const self_type& rhs) const { return m_ptr == rhs.m_ptr; }
        inline bool operator!=(const self_type& rhs) const { return m_ptr != rhs.m_ptr; }
        inline pointer base() const { return m_ptr;}

    private:
        pointer m_ptr;
    };

    template <class Tp>
    inline std::ptrdiff_t operator-(const Iterator<Tp> &lhs, const Iterator<Tp> &rhs) { return (lhs.base() - rhs.base()); }

    // bool
    template <>
    class Iterator <bool>
    {
    public:
        typedef Iterator self_type;
        typedef BitPointer value_type;
        //typedef BitPointer & reference;
        //typedef BitPointer * pointer;
        //typedef std::forward_iterator_tag iterator_category;

        Iterator() : m_bitPtr( BitPointer(nullptr, -1) ) { }
        Iterator(BitPointer ptr) : m_bitPtr(ptr) { }
        ~Iterator() = default;

        // !!! для + - надо запилить проверки на выход за 0 и за макс размер контейнера
        // запуталась в конст-итераторах...

        inline self_type operator++() { m_bitPtr.m_index++; return *this; }
        inline self_type operator++(int) { self_type i = m_bitPtr; m_bitPtr.m_index++; return i; }
        inline self_type& operator--() { m_bitPtr.m_index--; return *this; }
        inline self_type operator--(int) { self_type i = m_bitPtr; m_bitPtr.m_index--; return i; }
        inline self_type operator+(int j) const
        {
            BitPointer tmp(m_bitPtr.m_dataPtr, m_bitPtr.m_index + j);
            return self_type(tmp);
        }
        inline self_type operator-(int j) const
         {
             BitPointer tmp(m_bitPtr.m_dataPtr, m_bitPtr.m_index - j);
             return self_type(tmp);
         }

        inline BitPointer operator*() const { return m_bitPtr; }

        // не оч поняла, как здесь правильно надо
        //inline pointer operator->() const { return m_bitPtr; }

        // и здесь...
        //inline reference operator[](int j) const { return *(m_bitPtr + j); }

        inline bool operator==(const self_type& rhs) const
        {
            return ( (m_bitPtr.m_dataPtr == rhs.m_bitPtr.m_dataPtr) &&
                     (m_bitPtr.m_index == rhs.m_bitPtr.m_index) );
        }

        inline bool operator!=(const self_type& rhs) const
        {
            return ( (m_bitPtr.m_dataPtr != rhs.m_bitPtr.m_dataPtr) ||
                     (m_bitPtr.m_index != rhs.m_bitPtr.m_index) );
        }

      /*  inline bool operator<(const self_type& rhs) const
        {
            return (m_bitPtr.m_dataPtr == rhs.m_bitPtr.m_dataPtr) &&
                    (m_bitPtr.m_index < rhs.m_bitPtr.m_index);
        }

        inline bool operator<=(const self_type& rhs) const
        {
            return (m_bitPtr.m_dataPtr == rhs.m_bitPtr.m_dataPtr) &&
                    (m_bitPtr.m_index <= rhs.m_bitPtr.m_index) ;
        }

        inline bool operator>(const self_type& rhs) const
        {
            return (m_bitPtr.m_dataPtr == rhs.m_bitPtr.m_dataPtr) &&
                    (m_bitPtr.m_index > rhs.m_bitPtr.m_index);
        }

        inline bool operator>=(const self_type& rhs) const
        {
            return (m_bitPtr.m_dataPtr == rhs.m_bitPtr.m_dataPtr) &&
                    (m_bitPtr.m_index >= rhs.m_bitPtr.m_index);
        }

        self_type operator=(const self_type& rhs) { m_bitPtr.m_dataPtr = rhs.m_bitPtr.m_dataPtr; m_bitPtr.m_index = rhs.m_bitPtr.m_index; return *this; }
      */
      // inline pointer base() const { return m_ptr;}

    private:
        BitPointer m_bitPtr;
    };
}


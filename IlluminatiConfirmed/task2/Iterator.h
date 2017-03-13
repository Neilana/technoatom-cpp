#pragma once

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
        typedef int difference_type;

        Iterator() : m_ptr(nullptr) { }
        Iterator(pointer ptr) : m_ptr(ptr) { }
        ~Iterator() = default;
        inline self_type operator++() { ++m_ptr; return *this; }
        inline self_type operator++(int) { self_type i = *this; ++m_ptr; return i; }
        inline self_type &operator--() { --m_ptr; return *this; }
        inline self_type operator--(int) { pointer n = m_ptr; --m_ptr; return n; }
        inline self_type operator+(int j) const { return self_type(m_ptr+j); }
        inline self_type operator-(int j) const { return self_type(m_ptr-j); }
        inline reference operator*() const { return *m_ptr; }
        inline pointer operator->() const { return m_ptr; }
        inline reference operator[](int j) const { return *(m_ptr + j); }
        inline bool operator==(const self_type& rhs) const { return m_ptr == rhs.m_ptr; }
        inline bool operator!=(const self_type& rhs) const { return m_ptr != rhs.m_ptr; }
        inline bool operator<(const self_type& other) const { return m_ptr < other.m_ptr; }
        inline bool operator<=(const self_type& other) const { return m_ptr <= other.m_ptr; }
        inline bool operator>(const self_type& other) const { return m_ptr > other.m_ptr; }
        inline bool operator>=(const self_type& other) const { return m_ptr >= other.m_ptr; }
    private:
        pointer m_ptr;
    };
}

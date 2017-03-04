#pragma once

#include <iostream>
#include <cassert>
using std::size_t;

namespace IlluminatiConfirmed
{
    template <typename Tp>
    class Array
    {
    public:
        /*!
         * \brief Array Constructs an empty array
         */
        Array();
        /*!
         * \brief Array Constructs a array with a size
         * \param size The size of the new array
         */
        Array(size_t size);
        Array(const Array<Tp> &other) = default;
        ~Array();
        Array<Tp> & operator=(const Stack<Tp> &rhs) = default;
        /*!
         * \brief operator [] Returns the item at index position i as a modifiable reference.
         * \param i Must be a valid index position in the array.
         * \return Value
         */
        Tp & operator[](int index) const;
        /*!
         * \brief max_size Returns the maximum number of items that can be stored in the vector without forcing a reallocation.
         * \return Value
         */
        inline size_t max_size() const;
        /*!
         * \brief empty Returns true if the array has size 0; otherwise returns false.
         * \return True or false
         */
        inline bool empty() const;
        /*!
         * \brief dump Debug information about the array's container
         * \param func Name of the function from which dump is called
         */
        void dump(std::string str) const;
    private:
        Tp *mData;
        size_t mSize;
    };
}

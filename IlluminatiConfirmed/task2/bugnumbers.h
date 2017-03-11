
#include "Array.h"



namespace IlluminatiConfirmed
{




template <class Tp, size_t N>
class BugNumbers
{
    //template <class Tp, size_t size>
    struct Count
    {
        size_t assigment;
        size_t access;
        size_t multiplication;
        size_t division;
        Tp numbers[N];
    };
public:
    BugNumbers(std::initializer_list<Tp> l);
    Tp & operator[](size_t index);
    BugNumbers<Tp,N>& operator=(BugNumbers<Tp,N> &rhs) = default;
    BugNumbers<Tp,N>& operator*(BugNumbers<Tp,N> &rhs);
    BugNumbers<Tp,N>& operator/(BugNumbers<Tp,N> &rhs);
private:
    Count m_count;
};

}

using IlluminatiConfirmed::Array;
using IlluminatiConfirmed::BugNumbers;

template <class Tp, size_t N>
BugNumbers<Tp,N>::BugNumbers(std::initializer_list<Tp> l) : m_count ({0,0,0,0})
{
    assert(l.size() >= N);
    size_t i = 0;
    for (auto it = l.begin(); it!=l.end(); it++)
    {
        m_count.numbers[i++] = *it;
    }
}

template <class Tp, size_t N>
Tp& BugNumbers<Tp,N>::operator[](size_t index)
{
    assert(index < N);
    if (index < N)
    {
        ++m_count.access;
        return this->Count.numbers[index];
    }
    else
    {
        throw std::out_of_range("ERRROOOORRRRR");
    }
}


template <class Tp, size_t N>
BugNumbers<Tp,N>& BugNumbers<Tp,N>::operator*(BugNumbers<Tp,N> &rhs)
{
    if (this->m_count.multiplication == 3)
    {
        std::cout<< "Pay me 10d for operator*"<<std::endl;
        return *this;
    }
    ++this->m_count.multiplication;
    ++rhs.m_count.multiplication;
    for (size_t i = 0; i < N; i++)
    {
        this->m_count.numbers[i] *= rhs.m_count.numbers[i];
    }
    return *this;
}

template <class Tp, size_t N>
BugNumbers<Tp,N>& BugNumbers<Tp,N>::operator/(BugNumbers<Tp,N> &rhs)
{
    if (this->m_count.division == 3)
    {
        std::cout<< "Pay me 10d for operator/"<<std::endl;
        return *this;
    }
    ++this->m_count.division;
    ++rhs.m_count.division;
    for (size_t i = 0; i < N; i++)
    {
        this->m_count.numbers[i] /= rhs.m_count.numbers[i];
    }
    return *this;
}



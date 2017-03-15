
#include "Array.h"



namespace IlluminatiConfirmed
{

    template <class Tp>
    class BugNumbers : public Array<Tp>
    {
        struct Count
        {
            size_t comparison;
            size_t multiplication;
            size_t division;
        };
    public:
        enum payment {comparison, multiplication, division};
        BugNumbers(const Tp &def);
        BugNumbers<Tp>& operator*(BugNumbers<Tp> &rhs);
        BugNumbers<Tp>& operator/(BugNumbers<Tp> &rhs);
        BugNumbers<Tp> operator==(BugNumbers<Tp> &rhs);
        void pay(payment p);


    private:
        Count m_count;
    };
    typedef class BugNumbers<int> Int;
    typedef enum BugNumbers<int>::payment pay;
}

using IlluminatiConfirmed::Array;
using IlluminatiConfirmed::BugNumbers;

template <class Tp>
BugNumbers<Tp>::BugNumbers(const Tp &def) : Array<Tp,1>(def), m_count ({0,0,0})
{

}

template <class Tp>
BugNumbers<Tp>& BugNumbers<Tp>::operator*(BugNumbers<Tp> &rhs)
{
    if (this->m_count.multiplication > 3)
    {
        std::cout<< "Pay me "<<this->m_count.multiplication<<" $ for operator*."<<std::endl;
        return *this;
    } else
    {
        if(rhs.m_count.multiplication > 3)
        {
            std::cout<< "Pay me "<<10<<" $ for operator* for right element."<<std::endl;
            return rhs;
        }
    }
    ++this->m_count.multiplication;
    ++rhs.m_count.multiplication;
    auto it = this->begin();
    *it *= rhs.at(0);
    return *this;
}

template <class Tp>
BugNumbers<Tp>& BugNumbers<Tp>::operator/(BugNumbers<Tp> &rhs)
{
    if (this->m_count.division > 3)
    {
        std::cout<< "Pay me "<<10<<" $ for operator/."<<std::endl;
        return *this;
    } else
    {
        if(rhs.m_count.division > 3)
        {
            std::cout<< "Pay me "<<10<<" $ for operator/ for right element."<<std::endl;
            return rhs;
        }
    }
    ++this->m_count.division;
    ++rhs.m_count.division;
    auto it = this->begin();
    *it /= rhs.at(0);
    return *this;
}

template <class Tp>
BugNumbers<Tp> BugNumbers<Tp>::operator==(BugNumbers<Tp> &rhs)
{
    if (this->m_count.comparison > 3)
    {
        std::cout<< "Pay me "<<this->m_count.comparison*10<<" $ for operator==, otherwise false."<<std::endl;
        return false;
    } else
    {
        if(rhs.m_count.comparison > 3)
        {
            std::cout<< "Pay me "<<this->m_count.comparison*10<<" $ for operator== for right element, otherwise false."<<std::endl;
            return false;
        }
    }
    ++this->m_count.comparison;
    ++rhs.m_count.comparison;

    return ContainerInterface<Tp>::operator ==(rhs);
}

template <class Tp>
void BugNumbers<Tp>::pay(BugNumbers<Tp>::payment p)
{
    switch (p) {
    case comparison:
        m_count.comparison = 0;
        std::cout<< "Than you may use compare."<<std::endl;
        break;
    case multiplication:
        m_count.multiplication = 0;
        std::cout<< "Than you may use multiplication."<<std::endl;
        break;
    case division:
        m_count.division = 0;
        std::cout<< "Than you may use division."<<std::endl;
        break;
    default:
        break;
    }
}


#pragma once

// Array class implementation
using IlluminatiConfirmed::Array;

template<class Tp, size_t TpSize>
Array<Tp, TpSize>::Array() : ContainerInterface<Tp>(m_data, TpSize)
{
    DUMP("in/out");
}

template<class Tp, size_t TpSize>
Array<Tp, TpSize>::Array(const Tp& def) :
    ContainerInterface<Tp>(m_data, TpSize) //FIXME:: а если нет конструктора по умолчанию?
{                                                                                //        все же это не универсальное решение
    DUMP("in");
    for(auto &it : *this)
        it = def;
    DUMP("out");
}

template<class Tp, size_t TpSize>
Array<Tp, TpSize>::Array(const Array<Tp, TpSize> &other) :
    ContainerInterface<Tp>(m_data, TpSize)
{
    DUMP("in");
    std::copy(other.begin(), other.end(), this->begin());
    DUMP("out");
}

template<class Tp, size_t TpSize>
Array<Tp, TpSize>::Array(const std::initializer_list<Tp>& initList) :
    ContainerInterface<Tp>(m_data, TpSize)      
{
    DUMP("in");
    ASSERT_OK(TpSize <= initList.size());
    std::copy(initList.begin(), initList.end(), this->begin());
    DUMP("out");
}

template<class Tp, size_t TpSize>
Array<Tp, TpSize>& Array<Tp, TpSize>::operator=(const Array<Tp, TpSize> &rhs)
{
    DUMP("in");
    if (this != &rhs)
    {
        ASSERT_OK(rhs.size() <= this->size());
        std::copy(rhs.begin(), rhs.end(), this->begin());
    }
    DUMP("out");
    return *this;
}

template <class Tp, size_t TpSize>
Array<Tp, TpSize>::~Array()
{
    DUMP("in/out");
    // само удаляется, если оставить - будет ошибка сегментации
}

template<class Tp, size_t TpSize>
void Array<Tp, TpSize>::swap(Array <Tp, TpSize> & other)
{
    DUMP("in");
    ASSERT_OK(this->size() == other.size());
    std::swap_ranges(this->begin(), this->end(), other.begin());
    DUMP("out");
}

// bool
template <size_t TpSize>
Array <bool, TpSize>::Array(bool value) :
    ContainerInterface<bool>(m_data, TpSize)
{
    unsigned char intValue = 0;
    if (value) intValue = 255;

    for (size_t i = 0; i <= TpSize/8; i++)
        m_data[i] = intValue;
    DUMP("in/out");
}

template <size_t TpSize>
Array <bool, TpSize>::Array(const Array<bool, TpSize> &other) :
     ContainerInterface<bool>(m_data, TpSize)
{
 //   std::copy(other.begin(), other.end(), this->begin());
     memcpy(m_data, other.m_data, (TpSize / 8) + 1 );
}

template<size_t TpSize>
Array<bool, TpSize>::Array(const std::initializer_list<bool>& initList) :
    ContainerInterface<bool>(m_data, TpSize)
{
    auto itThis = this->begin();
    auto itList = initList.begin();

    while (itList != initList.end())
    {
        *itThis = *itList;
        itThis++;
        itList++;
    }

    if (initList.size() < TpSize)
        while (itThis != this->end())
           *(itThis++) = false;
}

template<size_t TpSize>
Array<bool, TpSize> & Array<bool, TpSize>::operator=(const Array<bool, TpSize> &rhs)
{
    DUMP("in");
    if (this != &rhs)
    {
        ASSERT_OK(rhs.size() <= this->size());
        memcpy(m_data, rhs.m_data, (TpSize / 8) + 1 );
        //std::copy(rhs.begin(), rhs.end(), this->begin());
    }
    DUMP("out");
    return *this;
}

template<size_t TpSize>
void Array<bool, TpSize>::swap(Array <bool, TpSize> & other)
{
    DUMP("in");
    std::swap(m_data, other.m_data);
    DUMP("out");
}

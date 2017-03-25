// http://stackoverflow.com/questions/4445654/multiple-definition-of-template-specialization-when-using-different-objects

#include "Vector.h"


using IlluminatiConfirmed::Vector;
using IlluminatiConfirmed::ContainerInterface;

// bool
//Vector<bool>::Vector() : ContainerInterface<bool>(nullptr, 0), m_data(nullptr), m_capacity(0)
//{
//    DUMP("in/out");
//}

Vector<bool>::Vector(size_t capacity) :
    ContainerInterface<bool>(nullptr, 0),
    m_data(nullptr),
    m_capacity(0)
{
    DUMP("in");
    try
    {
        m_data = new unsigned char [(capacity/8) + 1];
        //m_capacity = capacity;
        m_capacity = ((capacity / 8) + 1) * 8;
        this->m_size = capacity;
        this->m_dataPtr = m_data;
    } catch (exception& e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

Vector<bool>::Vector(size_t capacity, const bool& value) :
    ContainerInterface<bool>(nullptr, 0),
    m_data(nullptr),
    m_capacity(0)
{
    DUMP("in");
    try
    {
        m_data = new unsigned char [(capacity/8) + 1];
        m_capacity = capacity;
        this->m_size = capacity;
        this->m_dataPtr = m_data;

        unsigned char intValue = 0;
        if (value) intValue = 255;

        for (size_t i = 0; i <= capacity/8; i++)
            m_data[i] = intValue;

        //for (auto it : *this)
        //    it = def;
    } catch (exception& e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

Vector<bool>::Vector(const Vector<bool> &other) :
    ContainerInterface<bool>(nullptr, other.m_size),
    m_data(nullptr),
    m_capacity(other.m_capacity)
{
    DUMP("in");
    try
    {
        m_data = new unsigned char[this->m_size/8 + 1];
        this->m_dataPtr = m_data;
        memcpy(m_data, other.m_data, (this->m_size / 8) + 1 );
       // std::copy(other.begin(),other.end(),this->begin());
    } catch (exception &e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");

}

Vector<bool>::~Vector()
{
    DUMP("in");
    if (m_data != nullptr)
        delete [] m_data;
    m_data = nullptr;
    this->m_dataPtr = nullptr;
    DUMP("out");
}

Vector<bool>::Vector(std::initializer_list<bool> initList) :
    ContainerInterface<bool>(nullptr, initList.size()),
    m_data(nullptr),
    m_capacity(0)
{
    DUMP("in");
    try
    {
        m_data = new unsigned char[this->m_size/8 + 1];
        this->m_dataPtr = m_data;

        m_capacity = ((initList.size() / 8) + 1) * 8;
        auto itThis = this->begin();
        for (auto it : initList)
            *(itThis++) = it;
    } catch (exception &e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

Vector<bool>& Vector<bool>::operator=(const Vector<bool> &rhs)
{
    DUMP("in");
    if (this != &rhs)
    {
//        Vector temp(rhs);
        //swap(temp);
        this->m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;
        memcpy(m_data, rhs.m_data, rhs.m_size/8 +1);
    }
    DUMP("out");
    return *this;
}

void Vector<bool>::swap(Vector <bool> & other)
{
    DUMP("in");
    std::swap(m_capacity, other.m_capacity);
    std::swap(this->m_size, other.m_size);
    std::swap(this->m_dataPtr, other.m_dataPtr);
    std::swap(m_data, other.m_data);
    DUMP("out");
}

void Vector<bool>::reserve(size_t capacity)
{
    if (capacity > m_capacity)
    {
        DUMP("in");
        Vector bufArr(*this);
        if (m_data != nullptr)
            delete [] m_data;

        m_capacity = ((capacity / 8) + 1) * 8;
        try
        {
            m_data = new unsigned char [m_capacity/8 + 1];
            this->m_dataPtr = m_data;
            memcpy(m_data, bufArr.m_data, bufArr.m_size/8 +1);
            //std::copy(bufArr.begin(),bufArr.end(),this->begin());
        } catch (exception &e)
        {
            ASSERT_STR( string(e.what()) );
        }
        DUMP("out");
    }
}

void Vector<bool>::resize(size_t capacity, bool value)
{
    DUMP("in");
    if (this->m_size >= capacity)
        this->m_size = capacity;
    else
    {
        reserve(capacity);

        //auto it2 = (this->begin() + 0);

        for (auto it = this->begin()+this->m_size; it != this->end()+capacity-this->m_size; it++)
            *it = value; //на сотой итерации изменения кода прошел тест. Я у мамы упорный
        this->m_size = capacity;
        //for (size_t i = this->m_size; i < capacity; i++)
        //    m_data[i] = value;

    }
    DUMP("out");
}

void Vector<bool>::push_back(const bool& value)
{
    DUMP("in");
    if (this->m_size == m_capacity)
        reserve(m_capacity + 1); // само увеличится на 8
    auto it = this->begin() + this->m_size;
    *it = value;
    this->m_size++;
    //m_data[this->m_size++] = value;
    DUMP("out");
}

void Vector<bool>::assign(size_t capacity, const bool& value)
{
    reserve(capacity);

    this->m_size = capacity;
    for (auto it = this->begin(); it != this->end()+capacity-this->m_size; it++)
        *it = value; //на сотой итерации изменения кода прошел тест. Я у мамы упорный

}

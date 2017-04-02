#pragma once


// Vector class implementation
using IlluminatiConfirmed::Vector;

template <class Tp>
Vector<Tp>::Vector() : ContainerInterface<Tp>(nullptr, 0), m_data(nullptr), m_capacity(0)
{
    DUMP("in/out");
}

template<class Tp>
Vector<Tp>::Vector(size_t capacity) :
    ContainerInterface<Tp>(nullptr, 0),
    m_data(nullptr),
    m_capacity(0)
{
    DUMP("in");
    try
    {
        m_data = new Tp[capacity];
        m_capacity = capacity;
        //this->m_size = capacity;
        this->m_size = 0;
        this->m_dataPtr = m_data;

    } catch (exception& e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp>
Vector<Tp>::Vector(size_t capacity, const Tp& def) :
    ContainerInterface<Tp>(nullptr, 0),
    m_data(nullptr),
    m_capacity(0)
{
    DUMP("in");
    try
    {
        m_data = new Tp[capacity];
        m_capacity = capacity;
        this->m_size = capacity;
        this->m_dataPtr = m_data;
        for (auto &it : *this)
            it = def;
    } catch (exception& e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp>
Vector<Tp>::Vector(const Vector<Tp> &other) :
    ContainerInterface<Tp>(nullptr, other.m_capacity),
    m_data(nullptr),
    m_capacity(other.m_capacity)
{
    DUMP("in");
    try
    {
        m_data = new Tp[this->m_size];
        this->m_dataPtr = m_data;
        std::copy(other.begin(),other.end(),this->begin());
    } catch (exception &e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp>
Vector<Tp>::Vector(const std::initializer_list<Tp> &initList) :
    ContainerInterface<Tp>(nullptr, initList.size()),
    m_data(nullptr),
    m_capacity(initList.size())
{
    DUMP("in");
    try
    {
        m_data = new Tp[this->m_size];
        this->m_dataPtr = m_data;

        auto itThis = this->begin();
        for (auto &it : initList)
            *(itThis++) = it;
    } catch (exception &e)
    {
        ASSERT_STR( string(e.what()) );
    }
    DUMP("out");
}

template<class Tp>
Vector<Tp>& Vector<Tp>::operator=(const Vector<Tp> &rhs)
{
    DUMP("in");
    if (this != &rhs)
    {
        Vector temp(rhs);
        swap(temp);
    }
    DUMP("out");
    return *this;
}

template <class Tp>
Vector<Tp>::~Vector()
{
    DUMP("in");
    if (m_data != nullptr)
        delete [] m_data;
    m_data = nullptr;
    this->m_dataPtr = nullptr;
    DUMP("out");
}

template <class Tp>
void Vector<Tp>::push_back(const Tp& value)
{
    DUMP("in");
    if (this->m_size == m_capacity)
        reserve(m_capacity + INCREMENT_CAPACITY);
    m_data[this->m_size++] = value;
    DUMP("out");
}

template<class Tp>
void Vector<Tp>::reserve(size_t capacity)
{
    if (capacity > m_capacity)
    {
        DUMP("in");
        Vector bufArr(*this);
        if (m_data != nullptr)
            delete [] m_data;

        m_capacity = capacity;
        try
        {
            m_data = new Tp [m_capacity];
            this->m_dataPtr = m_data;
            std::copy(bufArr.begin(),bufArr.end(),this->begin());
        } catch (exception &e)
        {
            ASSERT_STR( string(e.what()) );
        }
        DUMP("out");
    }
}

template<class Tp>
void Vector<Tp>::assign(size_t capacity, const Tp& value)
{
    reserve(capacity);

    this->m_size = capacity;
    for(auto &it : *this)
        it = value;
}

template<class Tp>
void Vector<Tp>::pop_back()
{
    if (this->m_size > 0)
        --(this->m_size);
}

template<class Tp>
void Vector<Tp>::clear()
{
    this->m_size = 0;
}

template<class Tp>
void Vector<Tp>::swap(Vector <Tp> & other)
{
    DUMP("in");
    std::swap(m_capacity, other.m_capacity);
    std::swap(this->m_size, other.m_size);
    std::swap(this->m_dataPtr, other.m_dataPtr);
    std::swap(m_data, other.m_data);
    DUMP("out");
}

template<class Tp>
void Vector<Tp>::resize(size_t capacity, Tp value)
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

template<class Tp>
void* Vector<Tp>::operator new(size_t size, int init)
{
    void *p = malloc(size);
    if (!p)
        throw std::bad_alloc();
    std::memset(p, init, size);
    //std::cout << "New vector with address: " <<  p << "\n";
    return p;
}

template<class Tp>
void* Vector<Tp>::operator new[](size_t size, int init)
{
    void *p = malloc(size);
    if (!p)
        throw std::bad_alloc();
    std::memset(p, init, size);
    // std::cout << "New array of vector with address: " <<  p << "\n";
    return p;
}



#pragma once

#include <iostream>

// все типы
template <class T>
class SimpleClass
{
public:
    SimpleClass(T newX) : x(newX) { y = 1; };
    //void print();
    T x;

protected:
    int y;
};

//template <class T>
//void SimpleClass<T>::print()
//{
//    std::cout << x << " I'm not bool :( \n";
//}

// специализация для bool
template <>
class SimpleClass <bool>
{
public:
    SimpleClass(bool newX) : x(newX) { y = 2; };
   // void print();
    bool x;

protected:
    int y;
};

//void SimpleClass<bool>::print()
//{
//    std::cout << x << " Hey, I'm bool! :) \n";
//};

// Not simple class

// все типы
template <class T>
class DerivedClass : public SimpleClass<T>
{
public:
    // можно получить доступ к y
    DerivedClass(T newX) : SimpleClass<T>(newX) { std::cout << this->y; };
};

// bool
template <>
class DerivedClass <bool> : public SimpleClass<bool>
{
public:
    // нельзя получить доступ к y
    DerivedClass(bool newX) : SimpleClass<bool>(newX) { std::cout << this->y; };
};

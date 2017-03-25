/**
*   @file       main.cpp
*   @briefi     Task #1: Stack 
*   @details    Implements stack structure. 
*   @author     Alina Voropaeva
*   @date       2017
*/  

// headers
#include <iostream>
#include "gtest/gtest.h"

// my headers
#include "Stack.h"

//FIXME: С макросами всегда надо быть осторожней. Представь себе, что у тебя был кусок кода:
// if(a)
//   MY_TEST(cond)
// else {
//   b();
// }
// Код под else будет выполнен совсем не тогда, когда ты этого ожидаешь.
// Если кратко, то единственным универсальным решением будет убрать код макроса под do { } while (false)
// в этом и только в этом случае MY_TEST(...) будет синтаксически эквивалентно выхову функции.
// Подробнее об этом можно почитать тут http://stackoverflow.com/questions/154136/why-use-apparently-meaningless-do-while-and-if-else-statements-in-c-c-macros
// simple unit-test
#define MY_TEST( condition )  \
    if ( ! (condition) )    \
    cout << "Test failed: " << #condition << endl;  

// FIXME: Лучше сразу привыкай не использовать имена типа My***. Это перестает работать как только в проекте появляется больше 1 человека.
using MyNamespace::Stack;

int main(int argc, char** argv)
{

    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    
    return 0;
}

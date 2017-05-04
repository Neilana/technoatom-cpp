// usefull headers and usings
#include <iostream>
#include "gtest/gtest.h"

// custom headers and usings
#include "Vector.h"
#include "Array.h"
#include "BugNumbers.h"
#include "Print.h"

using IlluminatiConfirmed::Array;
using IlluminatiConfirmed::Int;
using IlluminatiConfirmed::Vector;
using IlluminatiConfirmed::pay;

#define SHOWING_USE(str) do { std::cout<<"Showing the use of the "<< str<<":"<< std::endl;} while (0);

int main(int argc, char *argv[])
{
    SHOWING_USE("Bug numbers")
    {
        Int num1 = 1;
        Int num2 = 2;
        Int num3 = 1;
        num3 = num1*num2;
        num3 = num1*num2;
        num3 = num1*num2;
        num3 = num1*num2;
        num3 = num1*num2;

        num3 = num1/num2;
        num3 = num1/num2;
        num3 = num1/num2;
        num3 = num1/num2;
        num3 = num1/num2;

        num3 = num1==num2;
        num3 = num1==num2;
        num3 = num1==num2;
        num3 = num1==num2;
        num3 = num1==num2;

        num1.pay(pay::division);
        num2.pay(pay::division);
        num3 = num1/num2;
    }
    SHOWING_USE("Print")
    {
        IlluminatiConfirmed::print("I have #, # and #$.", "a car", "bro", 10);
    }

    return 0;
}

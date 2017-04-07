#include <iostream>
#include "Exception.h"
#include "..\Containers\Array\Array.h"

using std::string;
using std::cout;
using std::endl;
string stage1_an_exception_is_thrown_here (IlluminatiConfirmed::Array<string, 3> &a1, int i);
string stage2 (IlluminatiConfirmed::Array<string, 3> &a1);
int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    {
        IlluminatiConfirmed::Array<string, 3> simpleArray = {"Shla", "Sasha", "na"};
        try
        {
            cout << stage2(simpleArray);
        } catch (IlluminatiConfirmed::Exception &e)
        {
            cout << e.what();
        }
    }

    return 0;
}

string stage1_an_exception_is_thrown_here (IlluminatiConfirmed::Array<string, 3>& a1,int i)
{
    string temp = "";
    try
    {
        temp = a1.at(i);
    } catch (IlluminatiConfirmed::Exception &e)
    {
        throw EXCEPTION("stage1", &e);
    }
    temp+= string(" ");
    return temp;
}

string stage2 (IlluminatiConfirmed::Array<string, 3>& a1)
{
    string temp = "";

    for (int i = 0; i < 4; ++i)
    {
        try
        {
            temp += stage1_an_exception_is_thrown_here(a1, i);
        } catch (IlluminatiConfirmed::Exception &e)
        {
            throw EXCEPTION("stage2", &e);
        }
    }
    return temp;
}


#include <iostream>
#include "Exception.h"
#include "..\Containers\Array\Array.h"

#define TEST(str) do { std::cout<<"Start testing "<<str<<std::endl; }while(0);
#define END() do { std::cout<<"Test complete "<<std::endl; }while(0);

using std::string;
using std::cout;
using std::endl;
string uberfunc1 (IlluminatiConfirmed::Array<string, 8>& a1, int i);
string uberfunc2 (IlluminatiConfirmed::Array<string, 8>& a1);
int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    TEST("Simple ex")
    {
        IlluminatiConfirmed::Exception e1(33,"Sorce", __LINE__, __FILE__, __PRETTY_FUNCTION__);
        IlluminatiConfirmed::Exception e2(42,"Msg_1", __LINE__, __FILE__, __PRETTY_FUNCTION__);
        cout<<(e1 + e2).what();
        cout<<endl;
        cout<<endl;
        cout<<(e2 + e1).what();
    }
    END()

    TEST("Simple ex with array")
    {
        IlluminatiConfirmed::Array<string, 8> a1 = {"One", "two", "three", "four", "five", "bunny", "went out for",  "a walk"};

        try
        {
            cout << a1.at(20);
        } catch(IlluminatiConfirmed::Exception &e)
        {
            cout << e.what();
        }
    }
    END()

    TEST("Ex with array")
    {
        IlluminatiConfirmed::Array<string, 8> a2 = {"One", "two", "three", "four", "five", "bunny", "went out for",  "a walk"};
        try
        {
            cout << uberfunc2(a2);
        } catch (IlluminatiConfirmed::Exception &e)
        {
            cout << e.what();
        }
    }
    END()

    return 0;
}

string uberfunc1 (IlluminatiConfirmed::Array<string, 8>& a1,int i)
{
    string temp = "";
    try
    {
        temp = a1.at(i);
    } catch (IlluminatiConfirmed::Exception &e)
    {
        throw IlluminatiConfirmed::Exception(100, "Oh and oh", __LINE__, __FILE__,__PRETTY_FUNCTION__ ) + e;
    }
    temp+= string(" ");
    return temp;
}


string uberfunc2 (IlluminatiConfirmed::Array<string, 8>& a1)
{
    string temp = "";

    for (int i = 0; i < 10; ++i)
    {
        try
        {
            temp += uberfunc1(a1, i);
        } catch (IlluminatiConfirmed::Exception &e)
        {
            throw IlluminatiConfirmed::Exception(200, "Vah vah luchshiy exception in the whole world", __LINE__, __FILE__, __PRETTY_FUNCTION__ ) + e;
        }
    }
    return temp;
}


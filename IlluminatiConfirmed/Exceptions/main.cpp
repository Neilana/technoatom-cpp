#include <iostream>
#include "Exception.h"
#include "..\Containers\Array\Array.h"


using std::string;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    /*{
        IlluminatiConfirmed::Exception e1(33,"Msg_1", __LINE__, __FILE__, __PRETTY_FUNCTION__);
        IlluminatiConfirmed::Exception e2(42,"Msg_1", __LINE__, __FILE__, __PRETTY_FUNCTION__);
        cout<<(e1 + e2).what();
        cout<<endl;
        cout<<endl;
        cout<<(e2 + e1).what();
    }*/
    IlluminatiConfirmed::Array<string, 8> a1 = {"One", "two", "three", "four", "five", "bunny", "went out for",  "a walk"};

    try
    {
        cout << a1.at(20);
    } catch(IlluminatiConfirmed::Exception &e)
    {
        cout << e.what();
    }

//FIXME: не ловится, хотя должно.. по крайней мере на мсдн есть пример с лямбдами и трай кач блоками
    auto uberfunc = [a1]()->string
            {
                string temp = "";
                auto uberfunc = [a1](int i)->string
                        {
                            string temp = "";
                            try
                            {
                                temp = a1.at(i);
                            } catch (IlluminatiConfirmed::Exception &e)
                            {
                                cout<<"tadams";
                                throw IlluminatiConfirmed::Exception(100, "Oh and oh", 1, "__FILE__",__PRETTY_FUNCTION__ ) + e;
                            }
                            temp+= string(" ");
                            return temp;
                        };

                for (int i = 0; i < 10; ++i)
                {
                    try
                    {
                        temp += uberfunc(i);
                    } catch (IlluminatiConfirmed::Exception &e)
                    {
                        throw IlluminatiConfirmed::Exception(200, "Vah vah", 1, "__FILE__", __PRETTY_FUNCTION__ ) + e;
                    }
                }
                return temp;
            };
    try
    {
        cout << uberfunc();
    } catch (IlluminatiConfirmed::Exception &e)
    {
        cout << e.what();
    }


    return 0;
}

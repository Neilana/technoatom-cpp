#include <iostream>
#include "Exception.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    IlluminatiConfirmed::Exception e1(42,"Msg_1", "LINE11"/*I dont know what is this command*/, __PRETTY_FUNCTION__);
    IlluminatiConfirmed::Exception e2(33,"Msg_1", "LINE12"/*I dont know what is this command*/, __PRETTY_FUNCTION__);
    cout<<e1.what();
    cout<<e2.what();
    cout<<(e2 + e1).what();
    return 0;
}

#include <iostream>
#include "..\Containers\Array\Array.h"
#include "Exception.h"

using std::string;
using std::cout;
using std::endl;
using namespace IlluminatiConfirmed;

string stage1_an_exception_is_thrown_here(Array<string, 3>& a1, unsigned int i);
string stage2_replay_exception_from_stage1(Array<string, 3>& a1);
int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  {
    Array<string, 3> simpleArray = {"Shla", "Sasha", "na"};
    try {
      cout << stage2_replay_exception_from_stage1(simpleArray);
    } catch (Exception& e) {
      cout << e.what();
    }
  }
  return 0;
}

string stage1_an_exception_is_thrown_here(Array<string, 3>& a1,
                                          unsigned int i) {
  string temp;
  try {
    temp = a1.at(i);
  } catch (Exception& e) {
    throw EXCEPTION("stage1", &e);
  }
  temp += string(" ");
  return temp;
}

string stage2_replay_exception_from_stage1(Array<string, 3>& a1) {
  string temp;
  for (unsigned int i = 0; i < 4; ++i) {
    try {
      temp += stage1_an_exception_is_thrown_here(a1, i);
    } catch (IlluminatiConfirmed::Exception& e) {
      throw EXCEPTION("stage2", &e);
    }
  }
  return temp;
}

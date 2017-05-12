#include <iostream>
#include "Logger.h"

using namespace std;
using IlluminatiConfirmed::Logger;
using IlluminatiConfirmed::ManagerLoggers;

class foo1 {
  INIT_LOG(IlluminatiConfirmed::multiStream, "../Logger/", "foo1")
 public:
  foo1() {
    logger << "foo 1"
           << "\n";
  }
};

class foo2 {
  INIT_LOG(IlluminatiConfirmed::multiStream, "../Logger/", "foo2")
 public:
  foo2() {
    logger << "foo 2"
           << "\n";
    LOGGER("foo2") << "yeah"
                   << "\n";
  }
};

int main(int argc, char *argv[]) {
  foo1 t1;
  foo2 t2;
  return 0;
}

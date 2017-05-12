#include <iostream>
#include "gtest/gtest.h"

#include "../Exceptions/Exception.h"
#include "assembler.h"

using namespace std;

int main(int argc, char *argv[]) {
  cout << "Hello World!" << endl;

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

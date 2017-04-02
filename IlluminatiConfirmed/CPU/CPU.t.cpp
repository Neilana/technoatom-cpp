#include "gtest/gtest.h"
#include <iostream>

#include "CPU.h"

using IlluminatiConfirmed::CPU;
using IlluminatiConfirmed::Command;

TEST(CPUTest, Check1)
{
    CPU cpu1;
    cpu1.writeCommandToMemory(Command::PushConst, 10);
    cpu1.writeCommandToMemory(Command::PushConst, 3);
    cpu1.writeCommandToMemory(Command::Add);
    cpu1.writeCommandToMemory(Command::PushConst, 20);
    cpu1.writeCommandToMemory(Command::Sub);

    cpu1.runProgram();
    //Command buf = static_cast<Command> (1);
//    cpu1.saveFromMemoryToFile();
   // cpu1.dump();
}

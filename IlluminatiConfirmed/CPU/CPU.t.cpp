#include "gtest/gtest.h"
#include <iostream>

#include "CPU.h"

using IlluminatiConfirmed::CPU;
using IlluminatiConfirmed::Command;

TEST(CPUTest, Check1)
{
    CPU cpu1;

    // заполняем память командами (типа напрямую записываем в процессор)
    cpu1.writeCommandToMemory(Command::PushConst, 10);
    cpu1.writeCommandToMemory(Command::PushConst, 3);
    cpu1.writeCommandToMemory(Command::Add);
    cpu1.writeCommandToMemory(Command::PushConst, 20);
    cpu1.writeCommandToMemory(Command::Sub);
    cpu1.writeCommandToMemory(Command::End);

    // имитируем запуск программы
    cpu1.runProgram();

    cpu1.saveMemoryToTextFile();
    cpu1.saveMemoryToBinaryFile();

    CPU cpu2;
    //cpu2.loadMemoryFromTextFile();
    cpu2.loadMemoryFromBinaryFile();        // проверяем ручками дампы - всё океюшки, память cpu1 == cpu2


    //Command buf = static_cast<Command> (1);
//    cpu1.saveFromMemoryToFile();
   // cpu1.dump();
}

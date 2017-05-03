#include <iostream>
#include <algorithm>
#include "gtest/gtest.h"
#include "disassembler.h"
#include "cpu.h"

using namespace IlluminatiConfirmed;

TEST(disassembler, runMemory)
{
    //given
    IlluminatiConfirmed::Dissasembler dis;

    dis.runDisassemblerForMemory(std::vector<CPU::value_type>({CPU::info.at(Command::PushConst).id, 100,
                                                               CPU::info.at(Command::PushReg).id, 1,
                                                               CPU::info.at(Command::Add).id,
                                                               CPU::info.at(Command::PushConst).id, 100,
                                                               CPU::info.at(Command::PushReg).id, 1,
                                                               CPU::info.at(Command::Add).id,
                                                               CPU::info.at(Command::PushConst).id, 100,
                                                               CPU::info.at(Command::PushReg).id, 1,
                                                               CPU::info.at(Command::Add).id,
                                                               CPU::info.at(Command::Jmp).id, 6,
                                                               CPU::info.at(Command::Jmp).id, 4,
                                                               CPU::info.at(Command::Jmp).id, 0,
                                                               CPU::info.at(Command::End).id }), "disasm_runMemory.code");
    std::string excepted = "m0:\npushConst 100\npushReg x1\nadd\npushConst 100\nm4:\npushReg x1\nadd\nm6:\npushConst 100\npushReg x1\nadd\njmp m6:\njmp m4:\njmp m0:\nend\n";
    std::ifstream checkFile("disasm_runMemory.code");
    ASSERT_TRUE(checkFile.is_open());
    std::string actual;
    actual.assign((std::istreambuf_iterator<char>(checkFile.rdbuf())), std::istreambuf_iterator<char>());
    checkFile.close();

    ASSERT_EQ(excepted, actual);
}


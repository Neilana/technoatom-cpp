#include <iostream>
#include <algorithm>
#include "gtest/gtest.h"
#include "disassembler.h"
#include "cpu.h"

using namespace IlluminatiConfirmed;

TEST(disassembler, hz)
{
    IlluminatiConfirmed::Dissasembler dis;

    dis.runDisassemblerForMemory(std::vector<IlluminatiConfirmed::CPU::value_type>({CPU::info.at(Command::PushConst).id, 100,
                                                                                    CPU::info.at(Command::PushReg).id, 1,
                                                                                    CPU::info.at(Command::Add).id, CPU::info.at(Command::End).id }), "azz");

    auto list = dis.getStringList();

    std::for_each( list.begin(), list.end(),[](const auto & buf){ std::cout << buf << std::endl; } );
}

TEST(disassembler, runMemory)
{
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
                                                               CPU::info.at(Command::End).id }), "azz");

    auto list = dis.getStringList();

    std::for_each( list.begin(), list.end(),[](const auto & buf){ std::cout << buf << std::endl; } );
}

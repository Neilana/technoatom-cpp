#include "gtest/gtest.h"

#include "cpu.h"

using namespace IlluminatiConfirmed;

TEST (cpu, set_getMemory)
{
    //given
    CPU cpu;
    std::vector<CPU::value_type> excpected = { 1, 200, 1, 100, 18 };

    //when
    cpu.setMemory(excpected);
    std::vector<CPU::value_type> actual = cpu.getMemory();

    //then
    ASSERT_EQ(excpected, actual);
}

TEST (cpu, set_getRegister)
{
    //given
    CPU cpu;
    std::array<CPU::value_type, 6> excpected = { 1, 200, 1, 100, 18, 0};

    //when
    cpu.setRegisters(excpected);
    std::array<CPU::value_type, CPU::REGISTERS_COUNT>  actual = cpu.getRegisters();

    //then
    ASSERT_EQ(excpected, actual);
}

TEST (cpu, run)
{
    //given

    std::vector<CPU::value_type> memory = { CPU::info.at(Command::PushConst).id, 100, CPU::info.at(Command::PushConst).id, 200,
                                            CPU::info.at(Command::Add).id, CPU::info.at(Command::Pop).id, 1, CPU::info.at(Command::End).id};
    CPU cpu;
    cpu.setMemory(memory);
    std::array<CPU::value_type, CPU::REGISTERS_COUNT> registers = {0, 0, 0, 0, 0, 0};
    cpu.setRegisters(registers);
    cpu.run();

    //when
    std::array<CPU::value_type, CPU::REGISTERS_COUNT> excpected = {0, 100 + 200, 0, 0, 0, 0};
    std::array<CPU::value_type, CPU::REGISTERS_COUNT>  actual = cpu.getRegisters();

    //then
    ASSERT_EQ(excpected, actual);
}

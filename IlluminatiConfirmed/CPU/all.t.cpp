#include <fstream>
#include <iostream>
#include "assembler.h"
#include "cpu.h"
#include "disassembler.h"
#include "gtest/gtest.h"

using namespace IlluminatiConfirmed;

TEST(all, pushConstRegPopEnd) {
  std::ofstream createTestFile;
  createTestFile.open(("all_push_.code"));
  if (!createTestFile.is_open()) throw;
  createTestFile << "push 100" << std::endl
                 << "jmp m1:" << std::endl
                 << "push 200" << std::endl
                 << "add" << std::endl
                 << "end" << std::endl
                 << "m1:" << std::endl
                 << "push 1" << std::endl
                 << "add" << std::endl
                 << "pop x1" << std::endl
                 << "push 2" << std::endl
                 << "push x1" << std::endl
                 << "add" << std::endl
                 << "pop x3" << std::endl
                 << "end" << std::endl;
  std::array<CPU::value_type, CPU::REGISTERS_COUNT> expected = {0,   101, 0,
                                                                103, 0,   0};
  createTestFile.close();

  Assembler asem;
  asem.runAssemblerForFile("all_push_.code");
  asem.saveMemoryToTextFile("all_push_.asm");

  Dissasembler disasem;
  disasem.runDisassemblerForTxtFile("all_push_.asm", "dis_all_push_.code");

  Assembler asem2;
  asem2.runAssemblerForFile("dis_all_push_.code");
  asem2.saveMemoryToTextFile("dis_all_push_.asm");

  CPU cpu;
  cpu.loadMemoryFromTextFile("dis_all_push_.asm");
  cpu.run();
  std::array<CPU::value_type, CPU::REGISTERS_COUNT> actual = cpu.getRegisters();
  ASSERT_EQ(actual, expected);
}

TEST(all, fib) {
  try {
    // given
    Assembler asem;
    asem.runAssemblerForFile("../CPU/savings/fib_.code");
    asem.saveMemoryToTextFile("../CPU/savings/fib_.asm");

    Dissasembler disasem;
    disasem.runDisassemblerForTxtFile("../CPU/savings/fib_.asm",
                                      "../CPU/savings/dis_fib_.code");

    Assembler asem2;
    asem2.runAssemblerForFile("../CPU/savings/dis_fib_.code");
    asem2.saveMemoryToTextFile("../CPU/savings/dis_fib_.asm");

    CPU cpu;
    cpu.loadMemoryFromTextFile("../CPU/savings/dis_fib_.asm");
    cpu.setRegisters({20, 0, 0, 0, 0, 0});
    cpu.run();

    // when
    int expected = 6765;
    int actual = cpu.getRegisters().at(4);

    // then
    ASSERT_EQ(actual, expected);
  } catch (Exception &e) {
    std::cout << e.what();
    ASSERT_FALSE(1);
  }
}

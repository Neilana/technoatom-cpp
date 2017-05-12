#include <algorithm>
#include <iostream>
#include "cpu.h"
#include "disassembler.h"
#include "gtest/gtest.h"

using namespace IlluminatiConfirmed;

TEST(disassembler, runMemory) {
  try {
    // given
    IlluminatiConfirmed::Dissasembler dis;

    dis.runDisassemblerForMemory(
        std::vector<CPU::value_type>({CPU::info.at(Command::PushConst).id,
                                      100,
                                      CPU::info.at(Command::PushReg).id,
                                      1,
                                      CPU::info.at(Command::Add).id,
                                      CPU::info.at(Command::PushConst).id,
                                      100,
                                      CPU::info.at(Command::PushReg).id,
                                      1,
                                      CPU::info.at(Command::Add).id,
                                      CPU::info.at(Command::PushConst).id,
                                      100,
                                      CPU::info.at(Command::PushReg).id,
                                      1,
                                      CPU::info.at(Command::Add).id,
                                      CPU::info.at(Command::Jmp).id,
                                      4,
                                      CPU::info.at(Command::Jmp).id,
                                      9,
                                      CPU::info.at(Command::Jmp).id,
                                      0,
                                      CPU::info.at(Command::End).id}),
        "disasm_runMemory.code");

    // when
    std::string excepted =
        "m0:\npushConst 100\npushReg x1\nm4:\nadd\npushConst 100\npushReg "
        "x1\nm9:\nadd\npushConst 100\npushReg x1\nadd\njmp m4:\njmp m9:\njmp "
        "m0:\nend\n";
    std::ifstream checkFile("disasm_runMemory.code");
    ASSERT_TRUE(checkFile.is_open());
    std::string actual;
    actual.assign((std::istreambuf_iterator<char>(checkFile.rdbuf())),
                  std::istreambuf_iterator<char>());
    checkFile.close();

    // then
    ASSERT_EQ(excepted, actual);
  } catch (Exception &e) {
    std::cout << e.what();
    ASSERT_TRUE(0);
  }
}

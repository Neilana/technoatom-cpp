#include <fstream>
#include <iostream>
#include "assembler.h"
#include "gtest/gtest.h"

TEST(assembler, reedFile) {
  // given
  std::ofstream createTestFile;
  createTestFile.open(("test_reedFile_.code"));
  if (!createTestFile.is_open()) throw;
  createTestFile << "push\n"
                 << 100 << "\npush\n"
                 << 200 << "\nadd\n"
                 << "\nend\n"
                 << "push    " << 100 << " push    " << 200 << "  add "
                 << "    end ";
  std::vector<IlluminatiConfirmed::CPU::value_type> expected = {
      1, 100, 1, 200, 4, 18, 1, 100, 1, 200, 4, 18};
  createTestFile.close();

  // when
  IlluminatiConfirmed::Assembler as;
  as.runAssemblerForFile("test_reedFile_.code");
  std::vector<IlluminatiConfirmed::CPU::value_type> actual = as.getMemory();

  // then
  ASSERT_EQ(expected, actual);
}

TEST(assembler, writeFile) {
  // given
  std::ofstream createTestFile;
  createTestFile.open(("test_writeFile_create.code"));
  if (!createTestFile.is_open()) throw;
  createTestFile << "push\n"
                 << 100 << "\npush\n"
                 << 200 << "\nadd\n"
                 << "\nend\n";
  createTestFile.close();
  std::string expected("1 100 1 200 4 18 ");

  // when
  IlluminatiConfirmed::Assembler as;
  as.runAssemblerForFile("test_writeFile_create.code");
  as.saveMemoryToTextFile("writeFile_write.code");
  std::ifstream checkFile("writeFile_write.code");
  ASSERT_TRUE(checkFile.is_open());
  std::string actual;
  actual.assign((std::istreambuf_iterator<char>(checkFile.rdbuf())),
                std::istreambuf_iterator<char>());
  checkFile.close();

  // then
  ASSERT_EQ(expected, actual);
}

TEST(assembler, labels) {
  // given
  std::ofstream createTestFile;
  createTestFile.open(("test_label_create.code"));
  if (!createTestFile.is_open()) throw;
  createTestFile << "jmp m1:\n"
                 << "push\n"
                 << 100 << "\nm1:\n"
                           "\npush\n"
                 << 200 << "\nm2:\n"
                 << "\nadd\n"
                 << "\nend\n"
                 << "jmp m1:\n"
                 << "jmp m1:\n"
                 << "jmp m2:\n";
  createTestFile.close();
  std::string expected("8 4 1 100 1 200 4 18 8 4 8 4 8 6 ");

  // when
  IlluminatiConfirmed::Assembler as;
  as.runAssemblerForFile("test_label_create.code");
  as.saveMemoryToTextFile("test_label_write.code");
  std::ifstream checkFile("test_label_write.code");
  ASSERT_FALSE(0);
  ASSERT_TRUE(checkFile.is_open());
  std::string actual;
  actual.assign((std::istreambuf_iterator<char>(checkFile.rdbuf())),
                std::istreambuf_iterator<char>());
  checkFile.close();

  // then
  ASSERT_EQ(expected, actual);
}

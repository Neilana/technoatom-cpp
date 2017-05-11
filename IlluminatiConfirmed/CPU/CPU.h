#pragma once
#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include "../Exceptions/Exception.h"

namespace IlluminatiConfirmed {
enum class Command {
  // push/pop commands
  Push,       // not sure we need it
  PushConst,  ///< push constant value (e.g. push 2)
  PushReg,    ///< push value from the specified register (e.g. push
              /// m_registres[0])
  Pop,        ///< pop last value

  // math commands
  Add,  ///< addition (add together two last values from the stack and push the
        /// result back)
  Sub,  ///< subtraction (get value before the last and subtract the last value
        /// and push the result back)
  Div,  ///< division (get value before the last and divide by the last value
        /// and push the reuslt back)
  Mul,  ///< multiplication (multiplicate two last values and push the result
        /// back)

  // jump and conditional commands
  Jmp,  ///< jump to the label without any questions
  Ja,   ///< jump if previous > last
  Jae,  ///< jump if previous >= last
  Jb,   ///< jump if previous < last
  Jbe,  ///< jump if previous <= last
  Je,   ///< jump if previous == last
  Jne,  ///< jump if previous != last

  // functions
  Call,   ///< call function
  Ret,    ///< return from function
  Label,  ///< begining of the segment

  End  ///< end of program
};

struct CommandInfo {
  int id;
  unsigned char argsCount;
  std::string name;
};

class CPU {
 public:
  /*!
   * \brief CPU Throw IlluminatiConfirmed::Exception if not all the commands are
   * defined
   */
  CPU() : m_memory(MEMORY_CAPACITY), m_registres({0, 0, 0, 0, 0, 0}) {
    if (info.size() != m_commandsInfoCPU.size())
      throw EXCEPTION("Not all the commands are defined in the cpu", nullptr);
  }

  typedef int value_type;    ///< type of memory cells, stack, registres
  typedef size_t size_type;  ///< type of indexes used in the memory
  static const size_type MEMORY_CAPACITY =
      100;  ///< maximum number of memory "cells" (one cell = one number
            ///(command or command's argument) )
  static const size_type REGISTERS_COUNT =
      6;                                   ///< number of availible registers
  static const int ITERATIONS_MAX = 2000;  ///< maximum number of iterations (in
                                           /// order to prevent endless cycles)
  // static const std::pair<Command, CommandInfo> infoPair[];
  static const std::map<Command, CommandInfo> info;

  struct CommandInfoCPU {
    std::function<void(std::vector<value_type>::iterator &)> run;
  };

  /*!
   * \brief loadMemoryFromTextFile
   * \param fileName Opens file with this name for reading,
   * IlluminatiConfirmed::Exception if cannot open file
   */
  void loadMemoryFromTextFile(const std::string &fileName);

  /*!
   * \brief setMemory Allows to directly change the memory.
   * \param memory
   */
  inline void setMemory(const std::vector<value_type> &memory) {
    m_memory = memory;
  }

  /*!
   * \brief getMemory Gets memory
   * \return Memory
   */
  inline const std::vector<value_type> &getMemory() { return m_memory; }

  /*!
   * \brief run Run the program
   */
  void run();

  /*!
   * \brief setRegisters Sets registers
   * \param reg
   */
  void setRegisters(const std::array<value_type, REGISTERS_COUNT> &reg);

  /*!
   * \brief getRegisters Gets registers
   * \return
   */
  inline const std::array<value_type, REGISTERS_COUNT> &getRegisters() {
    return m_registres;
  }

  /*!
   * \brief setStack Sets the stack
   * \param stack
   */
  void setStack(const std::stack<value_type> &stack);

 private:
  /*!
   * \brief makeInfo Creates info map for cpu
   * \return
   */
  std::map<Command, CPU::CommandInfoCPU> makeInfo();

  std::vector<value_type> m_memory;
  std::stack<int> m_calls;
  std::array<value_type, REGISTERS_COUNT> m_registres;
  std::stack<value_type> m_stack;
  const std::map<Command, CommandInfoCPU> m_commandsInfoCPU = makeInfo();
};
}

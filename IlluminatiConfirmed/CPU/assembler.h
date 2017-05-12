#pragma once

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "../Exceptions/Exception.h"
#include "cpu.h"

namespace IlluminatiConfirmed {
class Assembler {
 public:
  /*!
   * \brief Assembler Throw IlluminatiConfirmed::Exception if not all the
   * commands are defined
   */
  Assembler() : m_memory(CPU::MEMORY_CAPACITY) {
    if (CPU::info.size() != m_commandsInfoAssembler.size())
      throw EXCEPTION("Not all the commands are defined in the assembler",
                      nullptr);
  }

  /*!
   * \brief runAssemblerForFile
   * \param input Opens file with this name for reading,
   * IlluminatiConfirmed::Exception if cannot open file
   */
  void runAssemblerForFile(const std::string &input);

  /*!
   * \brief saveMemoryToTextFile
   * \param fileName Creates/rewrites file with this name,
   * IlluminatiConfirmed::Exception if cannot create/open file
   */
  void saveMemoryToTextFile(const std::string &fileName);

  /*!
   * \brief getMemory Allows to receive a memory bypassing the recording stage
   * \return
   */
  const std::vector<CPU::value_type> &getMemory() { return m_memory; }

 private:
  struct CommandInfoAssembler {
    std::function<void(std::vector<std::string>::iterator &)> parse;
  };

  /*!
   * \brief oneAsmPass One parsing pass, may throw
   * IlluminatiConfirmed::Exception
   * \param buffer
   */
  void oneAsmPass(std::vector<std::string> &buffer);

  /*!
   * \brief makeInfo Creates info map for assembler
   * \return
   */
  std::map<Command, Assembler::CommandInfoAssembler> makeInfo();

  std::vector<CPU::value_type> m_memory;
  std::multimap<std::string, CPU::value_type> m_labels;
  const std::map<Command, CommandInfoAssembler> m_commandsInfoAssembler =
      makeInfo();
};
}

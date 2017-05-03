#pragma once

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include <stack>
#include <fstream>
#include <array>
#include <list>
#include <algorithm>

#include "../Exceptions/Exception.h"
#include "cpu.h"


namespace  IlluminatiConfirmed
{

    class Dissasembler
    {
    public:
        /*!
         * \brief Dissasembler Throw IlluminatiConfirmed::Exception if not all the commands are defined
         */
        Dissasembler() : m_memory(CPU::MEMORY_CAPACITY), argCount(0)
        {
            if (CPU::info.size() != m_commandsInfoDisassembler.size())
                throw EXCEPTION("Not all the commands are defined in the disassembler", nullptr);
        }

        /*!
         * \brief runDisassemblerForTxtFile Runs d isassembler for txt File, , IlluminatiConfirmed::Exception if cannot open file
         * \param input
         * \param output
         */
        void runDisassemblerForTxtFile(const std::string &input, const std::string &output);

        /*!
         * \brief runDisassemblerForMemory Runs disassembler for memory, IlluminatiConfirmed::Exception if cannot open file
         * \param memory
         * \param output
         */
        void runDisassemblerForMemory(const std::vector<CPU::value_type> &memory, const std::string &output);

        /*!
         * \brief getMemory Gets memory
         * \return
         */
        inline const auto& getMemory() { return m_memory; }

        /*!
         * \brief getStringList Gets string list
         * \return
         */
        inline const auto& getStringList() { return m_stringList; }

    private:
        struct CommandInfoDissassembler
        {
            std::function<void(std::vector<CPU::value_type>::iterator &)> parse;
        };

        /*!
         * \brief saveStringListToFile Saves string list to file, IlluminatiConfirmed::Exception if cannot open file
         * \param output
         */
        inline void saveStringListToFile(const std::string &output);

        /*!
         * \brief makeInfo Creates info map for disassembler
         * \return
         */
        std::map<Command, CommandInfoDissassembler> makeInfo();

        std::vector<CPU::value_type> m_memory;
        int argCount;
        std::map<int, bool> m_labels;
        std::list<std::pair<std::string, int>> m_stringList;

        const std::map<Command, CommandInfoDissassembler> m_commandsInfoDisassembler = makeInfo();
    };
}

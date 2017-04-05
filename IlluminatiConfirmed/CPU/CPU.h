#pragma once

//  macroses
#define DEBUG_CPU_ON
#if defined(DEBUG_CPU_ON)
#define DUMP_CPU(ch) do { this->dump(string(__PRETTY_FUNCTION__) + string("\nMessage: ") + string(ch)); } while(0);
#else
#define DUMP_CPU(ch)
#endif

// standart headers
#include <iostream>
#include <string>
#include <map>

// custom headers
#include "Vector.h"
#include "Array.h"
#include "Stack.h"

// standart usings
using std::size_t;
using std::string;
using std::map;

// custom usings
using IlluminatiConfirmed::Vector;
using MyNamespace::Stack;

namespace  IlluminatiConfirmed
{
    /// enum for CPU commands
    enum class Command
    {
        // push/pop commands
        Push,           // not sure we need it
        PushConst,      ///< push constant value (e.g. push 2)
        PushReg,        ///< push value from the specified register (e.g. push m_registres[0])
        Pop,            ///< pop last value

        // math commands
        Add,            ///< addition (add together two last values from the stack and push the result back)
        Sub,            ///< subtraction (get value before the last and subtract the last value and push the result back)
        Div,            ///< division (get value before the last and divide by the last value and push the reuslt back)
        Mul,            ///< multiplication (multiplicate two last values and push the result back)

        // jump and conditional commands
        Jmp,            ///< jump to the label without any questions
        Ja,             ///< jump if previous > last
        Jae,            ///< jump if previous >= last
        Jb,             ///< jump if previous < last
        Jbe,            ///< jump if previous <= last
        Je,             ///< jump if previous == last
        Jne,            ///< jump if previous != last

        // functions
        Call,           ///< call function
        Ret,            ///< return from function
        Label,          ///< begining of the segment

        End             ///< end of program
    };

    /// enum for arguments types
    enum class ArgType
    {
        None,           ///< command has no arguments (e.g. add, div)
        Value,          ///< argument is a value (register or constant) (e.g. push)
        Label           ///< argument is a label to jump
    };

    /// structure for command
    struct CommandInfo
    {
        int id;
        //Command cmd;
        unsigned char argsCount;
        ArgType argType;
        string name;
        bool operator!=(const CommandInfo& rhs) const { return (id != rhs.id); }
    };

    /// CPU class
    class CPU
    {
    public:
        typedef int value_type;         ///< type of memory cells, stack, registres
        typedef size_t size_type;       ///< type of indexes used in the memory

        CPU();                                              ///< constructor

        // operations for commands
        void writeCommandToMemory(Command cmd, int arg1 = 0);
        void runProgram();
        int getCommandId(Command cmd) { return static_cast<value_type>(cmd); }


        // assembler
        bool runAssemblerForFile(const string &fileName = "../savings/example1.code");
        //void readAssemblerCodeFromFile(const string &fileName = "../savings/example1.code");

        //disassembler

        // memory file operations
        bool saveMemoryToTextFile(const string &fileName = "../savings/save.memory.txt");
        bool loadMemoryFromTextFile(const string &fileName = "../savings/save.memory.txt");
        bool saveMemoryToBinaryFile(const string &fileName = "../savings/save.memory.bin");
        bool loadMemoryFromBinaryFile(const string &fileName = "../savings/save.memory.bin");

    private:
        // constants
        static const size_type STACK_CAPACITY = 20;            ///< maximum number of commands stored int the CPU's stack
        static const size_type REGISTERS_COUNT = 6;            ///< number of availible registers
        static const size_type MEMORY_CAPACITY = 100;          ///< maximum number of memory "cells" (one cell = one number (command or command's argument) )

        // не уверена, что эта штука должна находится внутри класса
        static const int ITERATIONS_MAX = 2000;                ///< maximum number of iterations (in order to prevent endless cycles)

        // private atributes
        Stack<value_type> m_stack;
        Array<value_type, REGISTERS_COUNT> m_registres;
        Vector<value_type> m_memory;                               ///< stores commands to perform

        Stack<int> m_calls;                                 ///< to remember IP's where functions where called

        //Vector<CommandInfo> m_commandsInfo;   ///< stores information about all CPU commands (names, arguments count)
        map<Command, CommandInfo> m_commandsInfo;     ///< stores information about all CPU commands (names, arguments count)
        map<string, Command> m_commandsByName;        ///< stores commands that can be accessed by its string name
        map<string, size_type> m_labels;                    ///< stores info about m_labels and its IP

        string m_dumpFileName;        ///< name of the file where debug information is stored

        // private methods
        void dump(const string &message) const;
        void initializeCommandsInfo();      ///< fill information about commands (names, arguments count)
    };
}

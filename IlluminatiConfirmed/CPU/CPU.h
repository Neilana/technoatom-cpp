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

        End             ///< end of program
    };

//    enum class ArgsType
//    {
//        None,           ///< command has no arguments (e.g. add, div)
//        Value,          ///< argument is a value (register or constant) (e.g. push)
//        Label           ///< argument is a label to jump
//    }

    /// structure for command
    struct CommandInfo
    {
        int id;
        //Command cmd;
        //ArgType arg;
        unsigned char argsCount;
        string name;
        bool operator!=(const CommandInfo& rhs) const { return (id != rhs.id); }
    };

    /// CPU class
    class CPU
    {
    public:
        CPU();                                              ///< constructor

        // operations for commands
        void writeCommandToMemory(Command cmd, int arg1 = 0);
        void runProgram();

        // file operations
        bool saveMemoryToTextFile(string fileName = "../savings/file1.txt");
        bool loadMemoryFromTextFile(string fileName = "../savings/file1.txt");
        bool saveMemoryToBinaryFile(string fileName = "../savings/file1.bin");
        bool loadMemoryFromBinaryFile(string fileName = "../savings/file1.bin");

    private:
        // constants
        static const size_t STACK_CAPACITY = 20;            ///< maximum number of commands stored int the CPU's stack
        static const size_t REGISTERS_COUNT = 6;            ///< number of availible registers
        static const size_t MEMORY_CAPACITY = 100;          ///< maximum number of memory "cells" (one cell = one number (command or command's argument) )

        // private atributes
        Stack<int> m_stack;
        Array<int, REGISTERS_COUNT> m_registres;
        //Array<int, MEMORY_CAPACITY> m_memory;
        Vector<int> m_memory;                               ///< stores commands to perform

        //Vector<CommandInfo> commandsInfo;   ///< stores information about all CPU commands (names, arguments count)
        map<Command, CommandInfo> commandsInfo;   ///< stores information about all CPU commands (names, arguments count)

        string dumpFileName;        ///< name of the file where debug information is stored

        // private methods
        void dump(const string &message) const;
        void initializeCommandsInfo();      ///< fill information about commands (names, arguments count)
    };
}

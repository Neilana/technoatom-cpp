// standart headers
#include <string>
#include <ctime>            // time for dump file
#include <fstream>

// custom heasders
#include "CPU.h"
#include "Vector.h"
#include "Stack.h"

//standart usings
using std::cout;
using std::end;
using std::string;

// custom usings
using IlluminatiConfirmed::CPU;
using IlluminatiConfirmed::Command;
using IlluminatiConfirmed::CommandInfo;

using IlluminatiConfirmed::Vector;
using MyNamespace::Stack;

CPU::CPU() :
    m_stack(STACK_CAPACITY), m_memory(MEMORY_CAPACITY), commandsInfo(), dumpFileName("")
{
    // generate dump file name
    time_t nowTime = time(0);
    struct tm nowInfo = *localtime(&nowTime);
    char nowStr1 [40];

    strftime(nowStr1, 40, "%F %T", &nowInfo);
    string nowStr2 (nowStr1);
    dumpFileName = "../dumps/"+ nowStr2;

    string message = "Creating CPU...";
    DUMP_CPU(message);

    // initialize commands info
    initializeCommandsInfo();
}

void CPU::dump(const std::string &message) const
{
    // open dump file and write main info about the CPU
    std::ofstream dumpFile(dumpFileName, std::ios_base::app);
    dumpFile << message << endl;
    dumpFile << "CPU: " << endl;
    dumpFile << "   (Stack size: " << m_stack.size() << ", stack capacity: " << m_stack.capacity() << ")\n";
    dumpFile << "   (Registers count: " << m_registres.size() << ")\n";
    dumpFile << "   (Memory size: " << m_memory.size() << ", memory capacity: " << m_memory.capacity() << ")\n";

    // write memory state into file
    dumpFile << "Memory state:  ";
    for (auto it : m_memory)
        dumpFile << it << " ";
    dumpFile << "\n";

    // write stack state into file
    string stackElements = "";
    stackElements = m_stack.writeElementsToString();
    dumpFile << "Stack state: \n" << stackElements << "\n";

    dumpFile.close();
}

void CPU::initializeCommandsInfo()
{
    // push/pop commands
    commandsInfo[Command::PushConst] = CommandInfo{static_cast<int>(Command::PushConst), 1, "push"};
    commandsInfo[Command::PushReg] = CommandInfo{static_cast<int>(Command::PushReg), 1, "push"};
    commandsInfo[Command::Pop] = CommandInfo{static_cast<int>(Command::Pop), 0, "pop"};

    // math commands
    commandsInfo[Command::Add] = CommandInfo{static_cast<int>(Command::Add), 0, "add"};
    commandsInfo[Command::Sub] = CommandInfo{static_cast<int>(Command::Sub), 0, "sub"};
    commandsInfo[Command::Div] = CommandInfo{static_cast<int>(Command::Div), 0, "div"};
    commandsInfo[Command::Mul] = CommandInfo{static_cast<int>(Command::Mul), 0, "mul"};

    // jump commands
    commandsInfo[Command::Jmp] = CommandInfo{static_cast<int>(Command::Jmp), 1, "jmp"};        // Argument::None, Value, Label ???
    commandsInfo[Command::Ja] = CommandInfo{static_cast<int>(Command::Ja), 1, "ja"};
    commandsInfo[Command::Jae] = CommandInfo{static_cast<int>(Command::Jae), 1, "jae"};
    commandsInfo[Command::Jb] = CommandInfo{static_cast<int>(Command::Jb), 1, "jb"};
    commandsInfo[Command::Jbe] = CommandInfo{static_cast<int>(Command::Jbe), 1, "jbe"};
    commandsInfo[Command::Je] = CommandInfo{static_cast<int>(Command::Je), 1, "je"};
    commandsInfo[Command::Jne] = CommandInfo{static_cast<int>(Command::Jne), 1, "jne"};

    // functions
    commandsInfo[Command::Call] = CommandInfo{static_cast<int>(Command::Call), 1, "call"};
    commandsInfo[Command::Ret] = CommandInfo{static_cast<int>(Command::Ret), 1, "ret"};

    commandsInfo[Command::End] = CommandInfo{static_cast<int>(Command::End), 0, "end"};
}

// just writes commands in memory, we don't need to actualy run any command yet (no operation with stack)
void CPU::writeCommandToMemory(Command cmd, int arg1)
{
    // if we have enough free memory
    if (m_memory.size() + commandsInfo[cmd].argsCount + 1 <= m_memory.capacity())
    {
        m_memory.push_back(commandsInfo[cmd].id);

        if (commandsInfo[cmd].argsCount == 1)
          m_memory.push_back(arg1);
    }
}

// run commands from memory
void CPU::runProgram()
{
    DUMP_CPU("Start program...");

    size_t ip = 0;
    while (ip < m_memory.size())
    {
        Command cmd = static_cast<Command> (m_memory[ip]);

        switch (cmd)
        {
            case Command::PushConst:
                m_stack.push(m_memory[ip + 1]);
            break;

            case Command::Add:
            {
                int buf1 = m_stack.top();
                m_stack.pop();
                int buf2 = m_stack.top();
                m_stack.pop();
                m_stack.push(buf1 + buf2);
            }
            break;

            case Command::Sub:
            {
                int buf1 = m_stack.top();
                m_stack.pop();
                int buf2 = m_stack.top();
                m_stack.pop();
                m_stack.push(buf2 - buf1);
            }
            break;

            case Command::Div:
            {
                int buf1 = m_stack.top();
                m_stack.pop();
                int buf2 = m_stack.top();
                m_stack.pop();
                m_stack.push(buf2 / buf1);
            }
            break;

            case Command::Mul:
            {
                int buf1 = m_stack.top();
                m_stack.pop();
                int buf2 = m_stack.top();
                m_stack.pop();
                m_stack.push(buf1 * buf2);
            }
            break;

            default:
            break;
        }

        // if not jmp
        ip = ip + 1 + commandsInfo[cmd].argsCount;
        DUMP_CPU(to_string(ip));
    }
    DUMP_CPU("...program finished.");
}

// // run commands from memory
//void CPU::runProgram()
//{
//    while (!onePass()) {};
//}


// save (not binary)
bool CPU::saveMemoryToTextFile(string fileName)
{
    bool result = false;
    try
    {
        std::ofstream saveFile(fileName);
        for (auto it : m_memory)
            saveFile << it << " ";
        saveFile.close();
        result = true;
    }
    catch (...)
    {
        result = false;
    }
    return result;
}

// load (not binary)
bool CPU::loadMemoryFromTextFile(string fileName)
{
    DUMP_CPU("Loading memory from text file...");

    m_memory.clear();
    bool result = false;
    try
    {
        std::ifstream loadFile(fileName);
        int buf;
        while (loadFile >> buf)
        {
            m_memory.push_back(buf);
        }

        loadFile.close();
        result = true;
    }
    catch (...)
    {
        result = false;
    }

    DUMP_CPU("...loading finished.");
    return result;
}

// save (binary)
bool CPU::saveMemoryToBinaryFile(string fileName)
{
    bool result = false;
    try
    {
        std::ofstream saveFile(fileName, std::ios::binary);

        // magic with writing vector into a file explained here:
        // http://stackoverflow.com/questions/14089266/how-to-correctly-write-vector-to-binary-file-in-c
        saveFile.write( (char*)&m_memory[0], sizeof(int) * m_memory.size() );

        saveFile.close();
        result = true;
    }
    catch (...)
    {
        result = false;
    }
    return result;
}

// load (binary)
bool CPU::loadMemoryFromBinaryFile(string fileName)
{
    DUMP_CPU("Loading memory from binary file...");

    bool result = false;
    m_memory.clear();
    try
    {
        std::ifstream loadFile(fileName, std::ios::binary);
        //loadFile.read(reinterpret_cast<char*>(&m_memory[0]), 3 * sizeof(int)); // or &buf[0]
        int buf;
        while (loadFile.read(reinterpret_cast<char*>(&buf), sizeof(buf)))
        {
            m_memory.push_back(buf);
        }

        loadFile.close();
        result = true;
    }
    catch (...)
    {
        result = false;
    }

    DUMP_CPU("...loading finished.");
    return result;
}

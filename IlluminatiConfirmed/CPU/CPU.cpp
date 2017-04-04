// standart headers
#include <algorithm>        // transform (string to lowercase)
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
    m_stack(STACK_CAPACITY), m_memory(MEMORY_CAPACITY), m_calls(), commandsInfo(),
    commandsByName(), labels(), dumpFileName("")
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
    commandsInfo[Command::Push] = CommandInfo{static_cast<int>(Command::Push), 1, ArgType::Value, "push"};
    commandsInfo[Command::PushConst] = CommandInfo{static_cast<int>(Command::PushConst), 1, ArgType::Value, "push"};
    commandsInfo[Command::PushReg] = CommandInfo{static_cast<int>(Command::PushReg), 1, ArgType::Value, "push"};
    commandsInfo[Command::Pop] = CommandInfo{static_cast<int>(Command::Pop), 0, ArgType::None, "pop"};

    // math commands
    commandsInfo[Command::Add] = CommandInfo{static_cast<int>(Command::Add), 0, ArgType::None, "add"};
    commandsInfo[Command::Sub] = CommandInfo{static_cast<int>(Command::Sub), 0, ArgType::None, "sub"};
    commandsInfo[Command::Div] = CommandInfo{static_cast<int>(Command::Div), 0, ArgType::None, "div"};
    commandsInfo[Command::Mul] = CommandInfo{static_cast<int>(Command::Mul), 0, ArgType::None, "mul"};

    // jump commands
    commandsInfo[Command::Jmp] = CommandInfo{static_cast<int>(Command::Jmp), 1, ArgType::Label, "jmp"};        // Argument::None, Value, Label ???
    commandsInfo[Command::Ja] = CommandInfo{static_cast<int>(Command::Ja), 1, ArgType::Label, "ja"};
    commandsInfo[Command::Jae] = CommandInfo{static_cast<int>(Command::Jae), 1, ArgType::Label, "jae"};
    commandsInfo[Command::Jb] = CommandInfo{static_cast<int>(Command::Jb), 1, ArgType::Label, "jb"};
    commandsInfo[Command::Jbe] = CommandInfo{static_cast<int>(Command::Jbe), 1, ArgType::Label, "jbe"};
    commandsInfo[Command::Je] = CommandInfo{static_cast<int>(Command::Je), 1, ArgType::Label, "je"};
    commandsInfo[Command::Jne] = CommandInfo{static_cast<int>(Command::Jne), 1, ArgType::Label, "jne"};

    // functions
    commandsInfo[Command::Call] = CommandInfo{static_cast<int>(Command::Call), 1, ArgType::Label, "call"};
    commandsInfo[Command::Ret] = CommandInfo{static_cast<int>(Command::Ret), 0, ArgType::None, "ret"};

    commandsInfo[Command::End] = CommandInfo{static_cast<int>(Command::End), 0, ArgType::None, "end"};

    // names
    // push/pop commands
    commandsByName["push"] = Command::Push;    // not obvious! (const or reg)
    commandsByName["pop"] = Command::Pop;

    // math commands
    commandsByName["add"] = Command::Add;
    commandsByName["sub"] = Command::Sub;
    commandsByName["div"] = Command::Div;
    commandsByName["mul"] = Command::Mul;

    // jump commands
    commandsByName["jmp"] = Command::Jmp;
    commandsByName["ja"] = Command::Ja;
    commandsByName["jae"] = Command::Jae;
    commandsByName["jb"] = Command::Jb;
    commandsByName["jbe"] = Command::Jbe;
    commandsByName["je"] = Command::Je;
    commandsByName["jne"] = Command::Jne;

    // function commands
    commandsByName["call"] = Command::Call;
    commandsByName["ret"] = Command::Ret;
//    commandsByName[""] = Command::Label;

    commandsByName["end"] = Command::End;
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
            {
                m_stack.push(m_memory[ip + 1]);
                ip = ip + 2;
            }
            break;

            case Command::Add:
            {
                int buf1 = m_stack.top();
                m_stack.pop();
                int buf2 = m_stack.top();
                m_stack.pop();

                m_stack.push(buf1 + buf2);

                 ip = ip + 1;
            }
            break;

            case Command::Sub:
            {
                int buf1 = m_stack.top();
                m_stack.pop();
                int buf2 = m_stack.top();
                m_stack.pop();

                m_stack.push(buf2 - buf1);

                ip = ip + 1;
            }
            break;

            case Command::Div:
            {
                int buf1 = m_stack.top();
                m_stack.pop();

                int buf2 = m_stack.top();
                m_stack.pop();

                m_stack.push(buf2 / buf1);

                ip = ip + 1;
            }
            break;

            case Command::Mul:
            {
                int buf1 = m_stack.top();
                m_stack.pop();

                int buf2 = m_stack.top();
                m_stack.pop();

                m_stack.push(buf1 * buf2);

                 ip = ip + 1;
            }
            break;

            case Command::Jmp:
            {
                ip = m_memory[ip + 1];
            }
            break;

            case Command::Ja:
            {
                int second = m_stack.top();
                m_stack.pop();

                int first = m_stack.top();
                m_stack.pop();

                if (first > second)
                    ip = m_memory[ip + 1];
                else
                    ip = ip + 2;
            }
            break;

            case Command::Jae:
            {
                int second = m_stack.top();
                m_stack.pop();

                int first = m_stack.top();
                m_stack.pop();

                if (first >= second)
                    ip = m_memory[ip + 1];
                else
                    ip = ip + 2;
            }
            break;

            case Command::Jb:
            {
                int second = m_stack.top();
                m_stack.pop();

                int first = m_stack.top();
                m_stack.pop();

                if (first < second)
                    ip = m_memory[ip + 1];
                else
                    ip = ip + 2;
            }
            break;

            case Command::Jbe:
            {
                int second = m_stack.top();
                m_stack.pop();

                int first = m_stack.top();
                m_stack.pop();

                if (first <= second)
                    ip = m_memory[ip + 1];
                else
                    ip = ip + 2;
            }
            break;

            case Command::Je:
            {
                int second = m_stack.top();
                m_stack.pop();

                int first = m_stack.top();
                m_stack.pop();

                if (first == second)
                    ip = m_memory[ip + 1];
                else
                    ip = ip + 2;
            }
            break;

            case Command::Jne:
            {
                int second = m_stack.top();
                m_stack.pop();

                int first = m_stack.top();
                m_stack.pop();

                if (first != second)
                    ip = m_memory[ip + 1];
                else
                    ip = ip + 2;
            }
            break;

            case Command::Call:
            {
                m_calls.push(ip);
                ip = m_memory[ip + 1];
            }
            break;

            case Command::Ret:
            {
                ip = m_calls.top();
                m_calls.pop();
            }
            break;

            case Command::End:
            {
                ip = ip + 1;
            }
            break;

            default:
            break;
        }

        // if not jmp

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
bool CPU::saveMemoryToTextFile(const string &fileName)
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
bool CPU::loadMemoryFromTextFile(const string &fileName)
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
bool CPU::saveMemoryToBinaryFile(const string &fileName)
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
bool CPU::loadMemoryFromBinaryFile(const string &fileName)
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

// text file
bool CPU::runAssemblerForFile(const string &fileName)
{
    DUMP_CPU("Run assembler for text file...");

    m_memory.clear();
    bool result = false;
    try
    {
        std::ifstream loadFile(fileName);
        string buf;
        while (loadFile >> buf)
        {
            std::transform(buf.begin(), buf.end(), buf.begin(), ::tolower);  // buf to lower case
            std::cout << buf << std::endl;
            // search for ":" (label)

            std::size_t found = buf.find(":");
            if (found != std::string::npos)    // if label
                labels[buf] = m_memory.size();      // label is pointing to the current (next) command
            else
            {
                Command cmd = commandsByName[buf];
                // if we have enough memory
                if ((m_memory.size() + 1 + commandsInfo[cmd].argsCount) < m_memory.capacity())
                {
                   // if (commandsInfo[cmd].argsCount == 1)
                    //    loadFile >> buf;

                    if (cmd == Command::Push)
                    {
                        m_memory.push_back(static_cast<int>(Command::PushConst));
                        int bufInt;
                        loadFile >> bufInt;
                        m_memory.push_back(bufInt);
                        // a register
                        // get register #
                        // m_memory.push_back(static_cast<int>(Command::PushReg));
                        // m_memory.push_back(#); // register #
                    }
                    else        // not push
                    {
                        //    Command cmd = commandsByName[buf];
                        m_memory.push_back(static_cast<int>(cmd));

                        // if cmd == jmp or smth
                        if (commandsInfo[cmd].argType == ArgType::Label)  // jmp, call, ja etc
                        {
                            string bufLabel;
                            loadFile >> bufLabel;

                            int bufIp = -1; // by default label not found
                            if (labels.count(bufLabel) > 0)     // if label was found
                                bufIp = labels[bufLabel];
                            m_memory.push_back(bufIp);
                        }
                    }
                }
            }
        }

        loadFile.close();
        result = true;
    }
    catch (...)
    {
        result = false;
    }

    DUMP_CPU("...finished.");
    return result;
}

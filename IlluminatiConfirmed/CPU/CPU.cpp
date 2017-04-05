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
    m_stack(STACK_CAPACITY), m_registres(0), m_memory(MEMORY_CAPACITY), m_calls(), m_commandsInfo(),
    m_commandsByName(), m_labels(), m_dumpFileName("")
{
    // generate dump file name
    time_t nowTime = time(0);
    struct tm nowInfo = *localtime(&nowTime);
    char nowStr1 [40];

    strftime(nowStr1, 40, "%F %T", &nowInfo);
    string nowStr2 (nowStr1);
    m_dumpFileName = "../dumps/"+ nowStr2;

    string message = "Creating CPU...";
    DUMP_CPU(message);

    // initialize commands info
    initializeCommandsInfo();
}

void CPU::dump(const std::string &message) const
{
    // open dump file and write main info about the CPU
    std::ofstream dumpFile(m_dumpFileName, std::ios_base::app);
    dumpFile << message << endl;
    dumpFile << "CPU: " << endl;
    dumpFile << "   (Stack size: " << m_stack.size() << ", stack capacity: " << m_stack.capacity() << ")\n";
    dumpFile << "   (Registers count: " << m_registres.size() << ")\n";
    dumpFile << "   (Memory size: " << m_memory.size() << ", memory capacity: " << m_memory.capacity() << ")\n";

    // registres
    dumpFile << "Registres: \n" ;
    int i = 0;
    for (auto it = m_registres.begin(); it != m_registres.end(); ++it, i++)
        dumpFile << "   x"<< i << " = " << *it << "\n";

    dumpFile << "\n";

    // write memory state into file
    dumpFile << "Memory state:  ";
    for (auto it : m_memory)
        dumpFile << it << " ";
    dumpFile << "\n";

    // write stack state into file
    string stackElements = "";
    stackElements = m_stack.writeElementsToString();
    dumpFile << "Stack state: \n" << stackElements << "\n";

    // known labels
    dumpFile << "Known labels: \n" ;
    for (auto it = m_labels.begin(); it != m_labels.end(); ++it)
        dumpFile << "   " << it->first << " (" << it->second << ")\n";
    dumpFile << "\n";

    dumpFile.close();
}

void CPU::initializeCommandsInfo()
{
    // push/pop commands
    m_commandsInfo[Command::Push] = CommandInfo{static_cast<value_type>(Command::Push), 1, ArgType::Value, "push"};
    m_commandsInfo[Command::PushConst] = CommandInfo{static_cast<value_type>(Command::PushConst), 1, ArgType::Value, "push"};
    m_commandsInfo[Command::PushReg] = CommandInfo{static_cast<value_type>(Command::PushReg), 1, ArgType::Value, "push"};
    m_commandsInfo[Command::Pop] = CommandInfo{static_cast<value_type>(Command::Pop), 0, ArgType::None, "pop"};

    // math commands
    m_commandsInfo[Command::Add] = CommandInfo{static_cast<value_type>(Command::Add), 0, ArgType::None, "add"};
    m_commandsInfo[Command::Sub] = CommandInfo{static_cast<value_type>(Command::Sub), 0, ArgType::None, "sub"};
    m_commandsInfo[Command::Div] = CommandInfo{static_cast<value_type>(Command::Div), 0, ArgType::None, "div"};
    m_commandsInfo[Command::Mul] = CommandInfo{static_cast<value_type>(Command::Mul), 0, ArgType::None, "mul"};

    // jump commands
    m_commandsInfo[Command::Jmp] = CommandInfo{static_cast<value_type>(Command::Jmp), 1, ArgType::Label, "jmp"};        // Argument::None, Value, Label ???
    m_commandsInfo[Command::Ja] = CommandInfo{static_cast<value_type>(Command::Ja), 1, ArgType::Label, "ja"};
    m_commandsInfo[Command::Jae] = CommandInfo{static_cast<value_type>(Command::Jae), 1, ArgType::Label, "jae"};
    m_commandsInfo[Command::Jb] = CommandInfo{static_cast<value_type>(Command::Jb), 1, ArgType::Label, "jb"};
    m_commandsInfo[Command::Jbe] = CommandInfo{static_cast<value_type>(Command::Jbe), 1, ArgType::Label, "jbe"};
    m_commandsInfo[Command::Je] = CommandInfo{static_cast<value_type>(Command::Je), 1, ArgType::Label, "je"};
    m_commandsInfo[Command::Jne] = CommandInfo{static_cast<value_type>(Command::Jne), 1, ArgType::Label, "jne"};

    // functions
    m_commandsInfo[Command::Call] = CommandInfo{static_cast<value_type>(Command::Call), 1, ArgType::Label, "call"};
    m_commandsInfo[Command::Ret] = CommandInfo{static_cast<value_type>(Command::Ret), 0, ArgType::None, "ret"};

    m_commandsInfo[Command::End] = CommandInfo{static_cast<value_type>(Command::End), 0, ArgType::None, "end"};

    // names
    // push/pop commands
    m_commandsByName["push"] = Command::Push;    // not obvious! (const or reg)
    m_commandsByName["pop"] = Command::Pop;

    // math commands
    m_commandsByName["add"] = Command::Add;
    m_commandsByName["sub"] = Command::Sub;
    m_commandsByName["div"] = Command::Div;
    m_commandsByName["mul"] = Command::Mul;

    // jump commands
    m_commandsByName["jmp"] = Command::Jmp;
    m_commandsByName["ja"] = Command::Ja;
    m_commandsByName["jae"] = Command::Jae;
    m_commandsByName["jb"] = Command::Jb;
    m_commandsByName["jbe"] = Command::Jbe;
    m_commandsByName["je"] = Command::Je;
    m_commandsByName["jne"] = Command::Jne;

    // function commands
    m_commandsByName["call"] = Command::Call;
    m_commandsByName["ret"] = Command::Ret;
//    m_commandsByName[""] = Command::Label;

    m_commandsByName["end"] = Command::End;
}

// just writes commands in memory, we don't need to actualy run any command yet (no operation with stack)
void CPU::writeCommandToMemory(Command cmd, int arg1)
{
    // if we have enough free memory
    if (m_memory.size() + m_commandsInfo[cmd].argsCount + 1 <= m_memory.capacity())
    {
        m_memory.push_back(m_commandsInfo[cmd].id);

        if (m_commandsInfo[cmd].argsCount == 1)
          m_memory.push_back(arg1);
    }
}

// run commands from memory
void CPU::runProgram()
{
    DUMP_CPU("Start program...");

    size_type ip = 0;
    int pass = 0;
    bool end = false;
    //while (ip < m_memory.size() && pass < ITERATIONS_MAX)
    while (!end && pass < ITERATIONS_MAX)
    {
        Command cmd = static_cast<Command> (m_memory[ip]);
        ++pass;
        //std::cout << pass << " ";
        switch (cmd)
        {
            case Command::PushConst:
            {
                m_stack.push(m_memory[ip + 1]);
                ip = ip + 2;
            }
            break;

            case Command::PushReg:
            {
                // value tupe -> size type ???
                size_type regNumber = m_memory[ip + 1];
                m_stack.push(m_registres[regNumber]);
                ip = ip + 2;
            }
            break;

            case Command::Add:
            {
                value_type buf1 = m_stack.top();
                m_stack.pop();
                value_type buf2 = m_stack.top();
                m_stack.pop();

                m_stack.push(buf1 + buf2);

                 ip = ip + 1;
            }
            break;

            case Command::Sub:
            {
                value_type buf1 = m_stack.top();
                m_stack.pop();
                value_type buf2 = m_stack.top();
                m_stack.pop();

                m_stack.push(buf2 - buf1);

                ip = ip + 1;
            }
            break;

            case Command::Div:
            {
                value_type buf1 = m_stack.top();
                m_stack.pop();

                value_type buf2 = m_stack.top();
                m_stack.pop();

                m_stack.push(buf2 / buf1);

                ip = ip + 1;
            }
            break;

            case Command::Mul:
            {
                value_type buf1 = m_stack.top();
                m_stack.pop();

                value_type buf2 = m_stack.top();
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
                value_type second = m_stack.top();
                m_stack.pop();

                value_type first = m_stack.top();
                m_stack.pop();

                if (first > second)
                    ip = m_memory[ip + 1];
                else
                    ip = ip + 2;
            }
            break;

            case Command::Jae:
            {
                value_type second = m_stack.top();
                m_stack.pop();

                value_type first = m_stack.top();
                m_stack.pop();

                if (first >= second)
                    ip = m_memory[ip + 1];
                else
                    ip = ip + 2;
            }
            break;

            case Command::Jb:
            {
                value_type second = m_stack.top();
                m_stack.pop();

                value_type first = m_stack.top();
                m_stack.pop();

                if (first < second)
                    ip = m_memory[ip + 1];
                else
                    ip = ip + 2;
            }
            break;

            case Command::Jbe:
            {
                value_type second = m_stack.top();
                m_stack.pop();

                value_type first = m_stack.top();
                m_stack.pop();

                if (first <= second)
                    ip = m_memory[ip + 1];
                else
                    ip = ip + 2;
            }
            break;

            case Command::Je:
            {
                value_type second = m_stack.top();
                m_stack.pop();

                value_type first = m_stack.top();
                m_stack.pop();

                if (first == second)
                    ip = m_memory[ip + 1];
                else
                    ip = ip + 2;
            }
            break;

            case Command::Jne:
            {
                value_type second = m_stack.top();
                m_stack.pop();

                value_type first = m_stack.top();
                m_stack.pop();

                if (first != second)
                    ip = m_memory[ip + 1];
                else
                    ip = ip + 2;
            }
            break;

            case Command::Call:
            {
                m_calls.push(ip + 2);
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
                end = true;
            }
            break;

            default:
            break;
        }

        string cmdStr = m_commandsInfo[cmd].name;
        DUMP_CPU(cmdStr);
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
        value_type buf;
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
        saveFile.write( (char*)&m_memory[0], sizeof(value_type) * m_memory.size() );

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
        value_type buf;
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
            std::size_t found = buf.find(":");
            if (found != std::string::npos)    // if label
                m_labels[buf] = m_memory.size();      // label is pointing to the current (next) command
            else
            {
                Command cmd = m_commandsByName[buf];
                // if we have enough memory
                if ((m_memory.size() + 1 + m_commandsInfo[cmd].argsCount) < m_memory.capacity())
                {
                   // if (m_commandsInfo[cmd].argsCount == 1)
                    //    loadFile >> buf;

                    if (cmd == Command::Push)
                    {
                        loadFile >> buf;
                        if (buf[0] == 'x') // arg = register
                        {
                            loadFile.seekg(-buf.length() + 1, std::ios_base::cur);
                            m_memory.push_back(static_cast<value_type>(Command::PushReg));

                            value_type bufRegN;
                            loadFile >> bufRegN;
                            m_memory.push_back(bufRegN);
                        }
                        else // push const
                        {
                            loadFile.seekg(-buf.length(), std::ios_base::cur);
                            m_memory.push_back(static_cast<value_type>(Command::PushConst));

                            value_type bufValue;
                            loadFile >> bufValue;
                            m_memory.push_back(bufValue);
                        }
                    }

                    else        // not push
                    {
                        //    Command cmd = m_commandsByName[buf];
                        m_memory.push_back(static_cast<value_type>(cmd));

                        // if cmd == jmp or smth
                        if (m_commandsInfo[cmd].argType == ArgType::Label)  // jmp, call, ja etc
                        {
                            string bufLabel;
                            loadFile >> bufLabel;

                            int bufIp = -1; // by default label not found
                            if (m_labels.count(bufLabel) > 0)     // if label was found
                                bufIp = m_labels[bufLabel];
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

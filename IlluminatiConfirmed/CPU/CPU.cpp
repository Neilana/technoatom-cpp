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
    m_commandsByName(), m_labels()
{
    DUMP_CPU("Creating CPU...");

    // initialize commands info
    initializeCommandsInfo();
}

std::ostream& CPU::dump(std::ostream &os) const
{
    // open dump file and write main info about the CPU
    os << "\nCPU: " << endl;
    os << "   (Stack size: " << m_stack.size() << ", stack capacity: " << m_stack.capacity() << ")\n";
    os << "   (Registers count: " << m_registres.size() << ")\n";
    os << "   (Memory size: " << m_memory.size() << ", memory capacity: " << m_memory.capacity() << ")\n";

    // registres
    os << "Registres: \n" ;
    int i = 0;
    for (auto it = m_registres.begin(); it != m_registres.end(); ++it, i++)
        os << "   x"<< i << " = " << *it << "\n";

    os << "\n";

    // write memory state into file
    os << "Memory state:  ";
    for (auto it : m_memory)
        os << it << " ";
    os << "\n";

    // write stack state into file
    string stackElements = "";
    stackElements = m_stack.writeElementsToString();
    os << "Stack state: \n" << stackElements << "\n";

    // known labels
    os << "Known labels: \n" ;
    for (auto it = m_labels.begin(); it != m_labels.end(); ++it)
        os << "   " << it->first << " (" << it->second << ")\n";
    os << "\n";
    return os;
}

void CPU::initializeCommandsInfo()
{
    initializeCommandsInfoPushPop();
    initializeCommandsInfoMath();
    initializeCommandsInfoJumps();
    initializeCommandsInfoFunctions();

    // names
    std::for_each(m_commandsInfo.begin(), m_commandsInfo.end(), [this](std::pair<Command, CommandInfo> info)
    {
        m_commandsByName[info.second.name] = info.first;
    });
}

void CPU::initializeCommandsInfoPushPop()
{
    // push/pop commands
    m_commandsInfo[Command::Push] = CommandInfo{static_cast<value_type>(Command::Push), 1, ArgType::Value, "push", ([this](Vector<value_type>::iterator& it) {
        //do nothing
    })};
    m_commandsInfo[Command::PushConst] = CommandInfo{static_cast<value_type>(Command::PushConst), 1, ArgType::Value, "pushConst", [this](Vector<value_type>::iterator& it) {
        m_stack.push(*(++it));
        ++it;
    }};
    m_commandsInfo[Command::PushReg] = CommandInfo{static_cast<value_type>(Command::PushReg), 1, ArgType::Value, "pushReg", [this](Vector<value_type>::iterator& it) {
        size_type regNumber = *(++it);
        m_stack.push(m_registres[regNumber]);
        ++it;
    }};
    m_commandsInfo[Command::Pop] = CommandInfo{static_cast<value_type>(Command::Pop), 0, ArgType::None, "pop", [this](Vector<value_type>::iterator& it) {
        it = it + 2;
        //do nothing
    }};
}

void CPU::initializeCommandsInfoMath()
{
    // math commands
    m_commandsInfo[Command::Add] = CommandInfo{static_cast<value_type>(Command::Add), 0, ArgType::None, "add", [this](Vector<value_type>::iterator& it) {
        value_type buf1 = m_stack.top();
        m_stack.pop();
        value_type buf2 = m_stack.top();
        m_stack.pop();

        m_stack.push(buf1 + buf2);

        ++it;
    }};
    m_commandsInfo[Command::Sub] = CommandInfo{static_cast<value_type>(Command::Sub), 0, ArgType::None, "sub", [this](Vector<value_type>::iterator& it) {
        value_type buf1 = m_stack.top();
        m_stack.pop();
        value_type buf2 = m_stack.top();
        m_stack.pop();

        m_stack.push(buf2 - buf1);

        ++it;
    }};
    m_commandsInfo[Command::Div] = CommandInfo{static_cast<value_type>(Command::Div), 0, ArgType::None, "div", [this](Vector<value_type>::iterator& it) {
        value_type buf1 = m_stack.top();
        m_stack.pop();

        value_type buf2 = m_stack.top();
        m_stack.pop();

        m_stack.push(buf2 / buf1);

        ++it;
    }};
    m_commandsInfo[Command::Mul] = CommandInfo{static_cast<value_type>(Command::Mul), 0, ArgType::None, "mul", [this](Vector<value_type>::iterator& it) {
        value_type buf1 = m_stack.top();
        m_stack.pop();

        value_type buf2 = m_stack.top();
        m_stack.pop();

        m_stack.push(buf1 * buf2);

        ++it;
    }};
}

void CPU::initializeCommandsInfoJumps()
{
    auto lambdaJamp = [this](Vector<value_type>::iterator& it, auto func) {
        value_type second = m_stack.top();
        m_stack.pop();

        value_type first = m_stack.top();
        m_stack.pop();

        if (func(first, second)/*first > second*/)
        {
            it =  m_memory.begin() + (*(++it));
        }
        else
        {
            ++it;
        }
    };
    // jump commands
    m_commandsInfo[Command::Jmp] = CommandInfo{static_cast<value_type>(Command::Jmp), 1, ArgType::Label, "jmp", [this](Vector<value_type>::iterator& it) {
        it =  m_memory.begin() + (*(++it));
    }};        // Argument::None, Value, Label ???
    m_commandsInfo[Command::Ja] = CommandInfo{static_cast<value_type>(Command::Ja), 1, ArgType::Label, "ja", [this, lambdaJamp](Vector<value_type>::iterator& it) {
        lambdaJamp(it, [](auto &&first, auto &&second)->bool { return first > second; });
    }};
    m_commandsInfo[Command::Jae] = CommandInfo{static_cast<value_type>(Command::Jae), 1, ArgType::Label, "jae", [this, lambdaJamp](Vector<value_type>::iterator& it) {
        lambdaJamp(it, [](auto &&first, auto &&second)->bool { return first >= second; });
    }};
    m_commandsInfo[Command::Jb] = CommandInfo{static_cast<value_type>(Command::Jb), 1, ArgType::Label, "jb", [this, lambdaJamp](Vector<value_type>::iterator& it) {
        lambdaJamp(it, [](auto &&first, auto &&second)->bool { return first < second; });
    }};
    m_commandsInfo[Command::Jbe] = CommandInfo{static_cast<value_type>(Command::Jbe), 1, ArgType::Label, "jbe", [this, lambdaJamp](Vector<value_type>::iterator& it) {
        lambdaJamp(it, [](auto &&first, auto &&second)->bool { return first <= second; });
    }};
    m_commandsInfo[Command::Je] = CommandInfo{static_cast<value_type>(Command::Je), 1, ArgType::Label, "je", [this, lambdaJamp](Vector<value_type>::iterator& it) {
        lambdaJamp(it, [](auto &&first, auto &&second)->bool { return first == second; });
    }};
    m_commandsInfo[Command::Jne] = CommandInfo{static_cast<value_type>(Command::Jne), 1, ArgType::Label, "jne", [this, lambdaJamp](Vector<value_type>::iterator& it) {
        lambdaJamp(it, [](auto &&first, auto &&second)->bool { return first != second; });
    }};
}

void CPU::initializeCommandsInfoFunctions()
{
    // functions
    m_commandsInfo[Command::Call] = CommandInfo{static_cast<value_type>(Command::Call), 1, ArgType::Label, "call", [this](Vector<value_type>::iterator& it) {
        m_calls.push((it - m_memory.begin()) + 2);
        it =  m_memory.begin() + (*(++it));
    }};

m_commandsInfo[Command::Ret] = CommandInfo{static_cast<value_type>(Command::Ret), 0, ArgType::None, "ret", [this](Vector<value_type>::iterator& it) {
        it = m_memory.begin() + m_calls.top();
        m_calls.pop();
    }};


//    m_commandsInfo[Command::End] = CommandInfo{static_cast<value_type>(Command::End), 0, ArgType::None, "end", runEnd};
        m_commandsInfo[Command::End] = CommandInfo{static_cast<value_type>(Command::End), 0, ArgType::None, "end", [this](Vector<value_type>::iterator& it) {
        //it = m_memory.end() - 1; //не придумал ничего лучше
        it = m_memory.end();
    }};
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

    int pass = 0;
    //for (auto it = m_memory.begin(); it != m_memory.end(); ++it)
    for (auto it = m_memory.begin(); it != m_memory.end(); /* nothing */)
    {
        if (pass++ == ITERATIONS_MAX || it == m_memory.end()) break;
        m_commandsInfo.at(static_cast<Command> (*it)).runLambda(it);
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

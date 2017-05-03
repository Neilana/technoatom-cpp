#include "cpu.h"

using namespace IlluminatiConfirmed;

const std::map<Command, CommandInfo> CPU::info = {
    {Command::Push, {static_cast<CPU::value_type>(Command::Push), 1, "push"}},
    {Command::PushReg, {static_cast<CPU::value_type>(Command::PushReg), 1, "pushReg"}},
    {Command::PushConst, {static_cast<CPU::value_type>(Command::PushConst), 1, "pushConst"}},
    {Command::Pop, {static_cast<CPU::value_type>(Command::Pop), 1, "pop"}},
    {Command::Add, {static_cast<CPU::value_type>(Command::Add), 0, "add"}},
    {Command::Sub, {static_cast<CPU::value_type>(Command::Sub), 0, "sub"}},
    {Command::Div, {static_cast<CPU::value_type>(Command::Div), 0, "div"}},
    {Command::Mul, {static_cast<CPU::value_type>(Command::Mul), 0, "mul"}},
    {Command::Jmp, {static_cast<CPU::value_type>(Command::Jmp), 1, "jmp"}},
    {Command::Ja, {static_cast<CPU::value_type>(Command::Ja), 1, "ja"}},
    {Command::Jae, {static_cast<CPU::value_type>(Command::Jae), 1, "jae"}},
    {Command::Jb, {static_cast<CPU::value_type>(Command::Jb), 1, "jb"}},
    {Command::Jbe, {static_cast<CPU::value_type>(Command::Jbe), 1, "jbe"}},
    {Command::Je, {static_cast<CPU::value_type>(Command::Je), 1, "je"}},
    {Command::Jne, {static_cast<CPU::value_type>(Command::Jne), 1, "jne"}},
    {Command::Call, {static_cast<CPU::value_type>(Command::Call), 1, "call"}},
    {Command::Ret, {static_cast<CPU::value_type>(Command::Ret), 0, "ret"}},
    {Command::End, {static_cast<CPU::value_type>(Command::End), 0, "end"}},
    {Command::Label, {static_cast<CPU::value_type>(Command::Label), 0, "label"}}
};

std::map<Command, CPU::CommandInfoCPU> CPU::makeInfo()
{
    auto lambdaJamp = [this](auto&& it, auto func) {
        if (m_stack.size() < 2) throw EXCEPTION("Stack is empty", nullptr);
        value_type second = m_stack.top();
        m_stack.pop();
        value_type first = m_stack.top();
        m_stack.pop();

        if (func(first, second))
        {
            it =  m_memory.begin() + (*(++it));
        }
        else
        {
            ++it;
            ++it;
        }
    };

    auto lambdaMath = [this](auto&& it, auto func) {
        value_type buf1 = m_stack.top();
        m_stack.pop();
        value_type buf2 = m_stack.top();
        m_stack.pop();
        m_stack.push(func(buf1, buf2));
        ++it;
    };

    std::map<Command, CPU::CommandInfoCPU> info = {
        {Command::Push, {[](auto &&itBuf){
                             (void)itBuf;
                         }}},
        {Command::PushConst, {[this](auto&& it) {
                                  m_stack.push(*(++it));
                                  ++it;
                              }}},
        {Command::PushReg, {[this](auto&& it) {
                                size_type regNumber = *(++it);
                                m_stack.push(m_registres[regNumber]);
                                ++it;
                            }}},
        {Command::Pop, {[this](auto &&itBuf){
                            m_registres[*(++itBuf)] = m_stack.top();
                            m_stack.pop();
                            ++itBuf;
                        }}},
        {Command::Add, {[this, lambdaMath](auto&& it) {
                            lambdaMath(it, ([](auto && buf1, auto &&buf2) -> auto { return buf1 + buf2; }));
                        }}},
        {Command::Sub, {[this, lambdaMath](auto&& it) {
                            lambdaMath(it, ([](auto && buf1, auto &&buf2) -> auto { return buf1 / buf2; }));
                        }}},
        {Command::Div, {[this, lambdaMath](auto&& it) {
                            lambdaMath(it, ([](auto && buf1, auto &&buf2) -> auto { return buf1 - buf2; }));
                        }}},
        {Command::Mul, {[this, lambdaMath](auto&& it) {
                            lambdaMath(it, ([](auto && buf1, auto &&buf2) -> auto { return buf1 * buf2; }));
                        }}},
        {Command::Jmp, {[this](auto &&it){
                            it = m_memory.begin() + *++it;
                        }}},
        {Command::Ja, {[this, lambdaJamp](auto &&it){
                           lambdaJamp(it, [](auto &&first, auto &&second)->bool { return first > second; });
                       }}},
        {Command::Jae, {[this, lambdaJamp](auto &&it){
                            lambdaJamp(it, [](auto &&first, auto &&second)->bool { return first >= second; });
                        }}},
        {Command::Jb, {[this, lambdaJamp](auto &&it){
                           lambdaJamp(it, [](auto &&first, auto &&second)->bool { return first < second; });
                       }}},
        {Command::Jbe, {[this, lambdaJamp](auto &&it){
                            lambdaJamp(it, [](auto &&first, auto &&second)->bool { return first <= second; });
                        }}},
        {Command::Je, {[this, lambdaJamp](auto &&it){
                           lambdaJamp(it, [](auto &&first, auto &&second)->bool { return first == second; });
                       }}},
        {Command::Jne, {[this, lambdaJamp](auto &&it){
                            lambdaJamp(it, [](auto &&first, auto &&second)->bool { return first != second; });
                        }}},
        {Command::Call, {[this, lambdaJamp](auto &&it){
                             m_calls.push((it - m_memory.begin()) + 2);
                             it =  m_memory.begin() + (*(++it));
                         }}},
        {Command::Ret, {[this, lambdaJamp](auto &&it){
                            it = m_memory.begin() + m_calls.top();
                            m_calls.pop();
                        }}},
        {Command::End, {[](auto &&itBuf){
                            ++itBuf;
                        }}},
        {Command::Label, {[](auto &&itBuf){
                              (void)itBuf;
                          }}}
    };
    return info;
}

void CPU::setStack(const std::stack<value_type> &stack)
{
    m_stack = stack;
}

void CPU::loadMemoryFromTextFile(const std::string &fileName)
{
    //DUMP_CPU("Loading memory from text file...");
    m_memory.clear();
    std::ifstream loadFile;
    loadFile.open(fileName);
    if (!loadFile.is_open())
        throw EXCEPTION("File for loading memory has not opened", nullptr);
    value_type buf;
    while (loadFile >> buf)
    {
        m_memory.push_back(buf);
    }
    loadFile.close();
}


void CPU::run()
{
    //DUMP_CPU("Start program...");
    int pass = 0;
    for (auto it = m_memory.begin(); it != m_memory.end(); /* nothing */)
    {
        if (pass++ == ITERATIONS_MAX)
            break;
        m_commandsInfoCPU.at(static_cast<Command>(*it)).run(it);
    }
    //DUMP_CPU("...program finished.");
}

void CPU::setRegisters(const std::array<value_type, REGISTERS_COUNT> &reg)
{
    for (unsigned int i = 0; i < REGISTERS_COUNT; ++i)
    {
        m_registres[i] = reg.at(i);
    }
}

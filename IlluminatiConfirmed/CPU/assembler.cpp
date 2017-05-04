#include "assembler.h"
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace IlluminatiConfirmed;

std::map<Command, Assembler::CommandInfoAssembler> Assembler::makeInfo()
{
    auto lambdaLabel = [this](auto &&itBuf) {
        auto temp_iter = m_labels.find(*++itBuf);
        m_memory.push_back((temp_iter != m_labels.end())?((*temp_iter).second):(0));
    };

    std::map<Command, Assembler::CommandInfoAssembler> info = {
        {Command::Push, {[this](auto &&itBuf){
                             m_commandsInfoAssembler.at(((*(itBuf + 1)).at(0) == 'x')?(Command::PushReg):(Command::PushConst)).parse(itBuf);
                         }}},
        {Command::PushConst, {[this](auto &itBuf) {
                                  m_memory.push_back((CPU::info.at(Command::PushConst).id));
                                  m_memory.push_back(std::stoi((*(++itBuf))));
                              }}},
        {Command::PushReg, {[this](auto &itBuf) {
                                m_memory.push_back((CPU::info.at(Command::PushReg).id));
                                auto temp = *++itBuf;
                                temp.erase(temp.begin());
                                m_memory.push_back(std::stoi((temp)));
                            }}},
        {Command::Pop, {[this](auto &&itBuf){
                            m_memory.push_back((CPU::info.at(Command::Pop).id));
                            std::string temp(*++itBuf);
                            temp.erase(0, 1);
                            m_memory.push_back(std::stoi(temp));
                        }}},
        {Command::Add, {[this](auto &&itBuf){
                            (void)itBuf;
                            m_memory.push_back((CPU::info.at(Command::Add).id));
                        }}},
        {Command::Sub, {[this](auto &&itBuf){
                            (void)itBuf;
                            m_memory.push_back((CPU::info.at(Command::Sub).id));
                        }}},
        {Command::Div, {[this](auto &&itBuf){
                            (void)itBuf;
                            m_memory.push_back((CPU::info.at(Command::Div).id));
                        }}},
        {Command::Mul, {[this](auto &&itBuf){
                            (void)itBuf;
                            m_memory.push_back((CPU::info.at(Command::Mul).id));
                        }}},
        {Command::Jmp, {[this, lambdaLabel](auto &&itBuf){
                            m_memory.push_back((CPU::info.at(Command::Jmp).id));
                            lambdaLabel(itBuf);
                        }}},
        {Command::Ja, {[this, lambdaLabel](auto &&itBuf){
                           m_memory.push_back((CPU::info.at(Command::Ja).id));
                           lambdaLabel(itBuf);
                       }}},
        {Command::Jae, {[this, lambdaLabel](auto &&itBuf){
                            m_memory.push_back((CPU::info.at(Command::Jae).id));
                            lambdaLabel(itBuf);
                        }}},
        {Command::Jb, {[this, lambdaLabel](auto &&itBuf){
                           m_memory.push_back((CPU::info.at(Command::Jb).id));
                           lambdaLabel(itBuf);
                       }}},
        {Command::Jbe, {[this, lambdaLabel](auto &&itBuf){
                            m_memory.push_back((CPU::info.at(Command::Jbe).id));
                            lambdaLabel(itBuf);
                        }}},
        {Command::Je, {[this, lambdaLabel](auto &&itBuf){
                           m_memory.push_back((CPU::info.at(Command::Je).id));
                           lambdaLabel(itBuf);
                       }}},
        {Command::Jne, {[this, lambdaLabel](auto &&itBuf){
                            m_memory.push_back((CPU::info.at(Command::Jne).id));
                            lambdaLabel(itBuf);
                        }}},
        {Command::Call, {[this, lambdaLabel](auto &&itBuf){
                             m_memory.push_back((CPU::info.at(Command::Call).id));
                             lambdaLabel(itBuf);
                         }}},
        {Command::Ret, {[this](auto &&itBuf){
                            m_memory.push_back((CPU::info.at(Command::Ret).id));
                            (void)itBuf;
                        }}},
        {Command::End, {[this](auto &&itBuf){
                            m_memory.push_back((CPU::info.at(Command::End).id));
                            (void)itBuf;
                        }}},
        {Command::Label, {[this](auto &&itBuf){
                              m_labels.insert({*itBuf, m_memory.size()});
                          }}}
    };
    return info;
}

void Assembler::runAssemblerForFile(const std::string &input)
{
    //DUMP_CPU("Run assembler for text file...");
    std::ifstream fileInput;
    fileInput.open(input, std::ios_base::in|std::ios_base::app);
    if (!fileInput.is_open())
        throw EXCEPTION("File for reading has not opened", nullptr);
    std::vector<std::string> buffer;
    //int strCount = 0;
    std::string temp;
    while (fileInput >> temp)
        buffer.push_back(temp);
    fileInput.close();

    m_labels.clear();

    oneAsmPass(buffer);
    oneAsmPass(buffer);
}

void Assembler::oneAsmPass(std::vector<std::string> &buffer)
{
    static auto tokens = []() -> auto {
            std::map<std::string, Command> tokens;
            for(auto && it : CPU::info)
    {
            tokens.insert({ it.second.name, it.first });
}
            return tokens;
}();
    m_memory.clear();
    for (auto itBuf = buffer.begin(); itBuf != buffer.end(); ++itBuf)
    {
        Command cmd = ((*itBuf).back() == ':')?(Command::Label):(tokens.at(*itBuf));
        //throw EXCEPTION((std::string("Unknown cmd: ") + (*itBuf)), nullptr);
        // if we have enough memory
        if ((m_memory.size() + 1 + CPU::info.at(cmd).argsCount) < m_memory.capacity())
        {
            //if (cmd != Command::Label) //The only command that doesn't need to be typed
            //    m_memory.push_back((CPU::info.at(cmd).id));
            m_commandsInfoAssembler.at(cmd).parse(itBuf);
        } else EXCEPTION("Memory is over", nullptr);
    }
}

void Assembler::saveMemoryToTextFile(const string &fileName)
{
    std::ofstream saveFile(fileName);
    if (!saveFile.is_open()) throw EXCEPTION("File for saving has not opened", nullptr);
    for (auto &it : m_memory)
        saveFile << it << " ";
    saveFile.close();
}



//std::ifstream& operator >>(std::ifstream &st, std::vector<std::string> &vec)
//{
//    std::string temp;
//    st >> temp;
//    vec.push_back(temp);
//    return st;
//}

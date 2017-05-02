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
        {Command::Push, {[](auto &&itBuf){
                            (void)itBuf;
                        }}},
        {Command::PushConst, {[this](auto &itBuf) {
                                  m_memory.push_back(std::stoi((*(++itBuf))));
                              }}},
        {Command::PushReg, {[this](auto &itBuf) {
                                auto temp = *++itBuf;
                                temp.erase(temp.begin());
                                m_memory.push_back(std::stoi((temp)));
                            }}},
        {Command::Pop, {[this](auto &&itBuf){
                            std::string temp(*++itBuf);
                            temp.erase(0, 1);
                            m_memory.push_back(std::stoi(temp));
                        }}},
        {Command::Add, {[](auto &&itBuf){
                            (void)itBuf;
                        }}},
        {Command::Sub, {[](auto &&itBuf){
                            (void)itBuf;
                        }}},
        {Command::Div, {[](auto &&itBuf){
                            (void)itBuf;
                        }}},
        {Command::Mul, {[](auto &&itBuf){
                            (void)itBuf;
                        }}},
        {Command::Jmp, {[lambdaLabel](auto &&itBuf){
                            lambdaLabel(itBuf);
                        }}},
        {Command::Ja, {[lambdaLabel](auto &&itBuf){
                            lambdaLabel(itBuf);
                        }}},
        {Command::Jae, {[lambdaLabel](auto &&itBuf){
                            lambdaLabel(itBuf);
                        }}},
        {Command::Jb, {[lambdaLabel](auto &&itBuf){
                            lambdaLabel(itBuf);
                        }}},
        {Command::Jbe, {[lambdaLabel](auto &&itBuf){
                            lambdaLabel(itBuf);
                        }}},
        {Command::Je, {[lambdaLabel](auto &&itBuf){
                            lambdaLabel(itBuf);
                        }}},
        {Command::Jne, {[lambdaLabel](auto &&itBuf){
                            lambdaLabel(itBuf);
                        }}},
        {Command::Call, {[lambdaLabel](auto &&itBuf){
                            lambdaLabel(itBuf);
                        }}},
        {Command::Ret, {[lambdaLabel](auto &&itBuf){
                            (void)itBuf;
                        }}},
        {Command::End, {[](auto &&itBuf){
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
    m_memory.clear();
    for (auto itBuf = buffer.begin(); itBuf != buffer.end(); ++itBuf)
    {
        Command cmd = [](auto &itBuf)-> Command {
                for(auto it = CPU::info.begin(); it != CPU::info.end(); ++it)
        {
            if ((*it).second.name == *itBuf)
            {
                if ((*it).first == Command::Push)
                {
                    if ((*(itBuf + 1)).at(0) == 'x')
                        return Command::PushReg;
                    else
                        return Command::PushConst;
                } else
                    return (*it).first;
                break;
            }
        }
        if ((*itBuf).back() == ':')
            return Command::Label;
        else
            throw EXCEPTION((std::string("Unknown cmd: ") + (*itBuf)), nullptr);
    }(itBuf);
    // if we have enough memory
    if ((m_memory.size() + 1 + CPU::info.at(cmd).argsCount) < m_memory.capacity())
    {
        if (cmd != Command::Label) //The only command that doesn't need to be typed
            m_memory.push_back((CPU::info.at(cmd).id));
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

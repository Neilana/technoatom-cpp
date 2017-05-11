#include "disassembler.h"

using namespace IlluminatiConfirmed;

std::map<Command, Dissasembler::CommandInfoDissassembler>
Dissasembler::makeInfo() {
  auto lambdaLabel = [this](auto &&itBuf) {
    m_labels.insert({*++itBuf, true});
    m_stringList.back().first +=
        std::string(" m") + std::to_string(*(itBuf)) + std::string(":");
  };

  std::map<Command, Dissasembler::CommandInfoDissassembler> info = {
      {Command::Push, {[](auto &&itBuf) { (void)itBuf; }}},
      {Command::PushConst, {[this](auto &itBuf) {
         m_stringList.back().first +=
             std::string(" ") + std::to_string(*(++itBuf));
         // m_stringList.push_back(std::to_string(*(++itBuf)));
       }}},
      {Command::PushReg, {[this](auto &itBuf) {
         m_stringList.back().first +=
             std::string(" x") + std::to_string(*(++itBuf));
         // m_stringList.push_back(std::string("x") +
         // std::to_string(*(++itBuf)));
       }}},
      {Command::Pop, {[this](auto &&itBuf) {
         m_stringList.back().first +=
             std::string(" x") + std::to_string(*(++itBuf));
       }}},
      {Command::Add, {[](auto &&itBuf) { (void)itBuf; }}},
      {Command::Sub, {[](auto &&itBuf) { (void)itBuf; }}},
      {Command::Div, {[](auto &&itBuf) { (void)itBuf; }}},
      {Command::Mul, {[](auto &&itBuf) { (void)itBuf; }}},
      {Command::Jmp, {[lambdaLabel](auto &&itBuf) { lambdaLabel(itBuf); }}},
      {Command::Ja, {[lambdaLabel](auto &&itBuf) { lambdaLabel(itBuf); }}},
      {Command::Jae, {[lambdaLabel](auto &&itBuf) { lambdaLabel(itBuf); }}},
      {Command::Jb, {[lambdaLabel](auto &&itBuf) { lambdaLabel(itBuf); }}},
      {Command::Jbe, {[lambdaLabel](auto &&itBuf) { lambdaLabel(itBuf); }}},
      {Command::Je, {[lambdaLabel](auto &&itBuf) { lambdaLabel(itBuf); }}},
      {Command::Jne, {[lambdaLabel](auto &&itBuf) { lambdaLabel(itBuf); }}},
      {Command::Call, {[lambdaLabel](auto &&itBuf) { lambdaLabel(itBuf); }}},
      {Command::Ret, {[](auto &&itBuf) { (void)itBuf; }}},
      {Command::End, {[](auto &&itBuf) { (void)itBuf; }}},
      {Command::Label, {[](auto &&itBuf) { (void)itBuf; }}}};
  return info;
}

void Dissasembler::runDisassemblerForTxtFile(const std::string &input,
                                             const std::string &output) {
  // DUMP_CPU("Run assembler for text file...");
  std::ifstream fileInput;
  fileInput.open(input, std::ios_base::in | std::ios_base::app);
  if (!fileInput.is_open())
    throw EXCEPTION("File for reading has not opened", nullptr);

  m_memory.clear();

  CPU::value_type temp;
  while (fileInput >> temp) {
    m_memory.push_back(temp);
  }
  fileInput.close();

  runDisassemblerForMemory(m_memory, output);
}

void Dissasembler::runDisassemblerForMemory(
    const std::vector<CPU::value_type> &memory, const std::string &output) {
  if (m_memory != memory) m_memory = memory;
  m_stringList.clear();
  m_labels.clear();
  argCount = 0;

  for (auto it = m_memory.begin(); it != m_memory.end(); ++it) {
    Command cmd = static_cast<Command>(*it);
    argCount += 1;  // CPU::info.at(cmd).argsCount;
    m_stringList.push_back(
        {CPU::info.at(cmd).name, CPU::info.at(cmd).argsCount});
    m_commandsInfoDisassembler.at(cmd).parse(it);
  }

  auto itList = m_stringList.begin();
  int argCount = 0;

  std::for_each(
      m_labels.begin(), m_labels.end(), [this, &itList, &argCount](auto &it) {
        for (;;) {
          if (argCount == it.first) {
            m_stringList.insert(
                itList,
                {std::string("m") + std::to_string(it.first) + std::string(":"),
                 CPU::info.at(Command::Label).argsCount});
            break;
          } else if (itList != m_stringList.end()) {
            argCount += 1 + (*itList).second;
            ++itList;
          } else
            throw EXCEPTION(
                std::string("Not found label #") + std::to_string(it.first),
                nullptr);
        }
      });
  saveStringListToFile(output);
}

void Dissasembler::saveStringListToFile(const std::string &output) {
  std::ofstream fileOutput;
  fileOutput.open(output);
  if (!fileOutput.is_open())
    throw EXCEPTION("File for reading has not opened", nullptr);

  std::for_each(
      m_stringList.begin(), m_stringList.end(),
      [&fileOutput](const auto &buf) { fileOutput << buf.first << std::endl; });
}

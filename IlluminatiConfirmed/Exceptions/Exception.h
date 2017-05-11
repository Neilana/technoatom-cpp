#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <utility>

#define EXCEPTION(message, ptr_on_Exception_or_nullptr)                   \
  IlluminatiConfirmed::Exception(__LINE__, __FILE__, __PRETTY_FUNCTION__, \
                                 message, ptr_on_Exception_or_nullptr);

namespace IlluminatiConfirmed {
class Exception {
  /*!
  * \brief The ExceptionData struct Struct of data of exceptions
  */
  struct ExceptionData {
    ExceptionData() : line(0), file(""), func(""), message("") {}
    ExceptionData(int l, std::string&& fu, std::string&& fi, std::string&& m)
        : line(l),
          file(std::move(fi)),
          func(std::move(fu)),
          message(std::move(m)) {}
    int line;
    std::string file;
    std::string func;
    std::string message;
  };

 public:
  /*!
  * \brief Exception Forms a std::string with information about the error.
  * \param code Error code
  * \param mess Message
  * \param line Line of code where it have happened
  * \param file File of line where it have happened
  * \param func Function of file where it have happened
  */
  Exception(int line, std::string&& file, std::string&& func,
            std::string&& message, const Exception* other = nullptr)
      : m_exceptionStorage(0) {
    if (other != nullptr) {
      m_exceptionStorage = other->m_exceptionStorage;
    }
    m_exceptionStorage.push_back(ExceptionData(
        line, std::move(file), std::move(func), std::move(message)));
  }

  /*!
   * \brief Exception Overloaded for lvalue message - std::string
   */
  Exception(int line, std::string&& file, std::string&& func,
            const std::string& message, const Exception* other = nullptr)
      : m_exceptionStorage(0) {
    if (other != nullptr) {
      m_exceptionStorage = other->m_exceptionStorage;
    }
    m_exceptionStorage.push_back(ExceptionData(
        line, std::move(file), std::move(func), std::string(message)));
  }

  /*!
  * \brief what Returns the explanatory std::string.
  * \return std::string
  */
  const std::string what() const {
    auto space = [](int j) {
      std::string sp;
      while (j-- > 0) sp += "  ";
      return sp;
    };
    std::stringstream os;
    int j = 0;
    for (auto it : m_exceptionStorage) {
      os << std::noskipws << space(j) << "On line: " << it.line << ".\n"
         << space(j) << "In file: " << it.file << ".\n"
         << space(j) << "In func: " << it.func << ".\n"
         << space(j) << "Message: " << it.message << "\n";
      ++j;
    }
    return os.str();
  }

 private:
  /*!
  * \brief m_exceptionStorage Data of a exception keep here
  */
  std::vector<ExceptionData> m_exceptionStorage;
};
}

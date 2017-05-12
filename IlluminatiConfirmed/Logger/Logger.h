#pragma once
#include <direct.h>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include "../Exceptions/Exception.h"

#define INIT_LOG(mode, puth, className) \
  IlluminatiConfirmed::Logger logger =  \
      ManagerLoggers::Instance(mode, puth).getLogger(className);
#define LOGGER(className) \
  ManagerLoggers::Instance().getLogger(className) << __PRETTY_FUNCTION__ << "\n"

namespace IlluminatiConfirmed {
enum ModeSave { oneStream, multiStream };

/*!
 * \brief The TypeLog enum Unrealized feature. Has not thought out how to use
 * and whether it is necessary at all.
 */
enum TypeLog { DEBUG, INFO, WARN, ERROR };

class Logger {
 public:
  /*!
   * \brief Logger Default constructor
   */
  Logger() : file(nullptr) {}

  /*!
   * \brief Logger The object stores the descriptor with the file during
   * the execution of the program, which closes when it finishes.
   * \param name
   */
  Logger(const std::string &name /*, TypeLog level*/) {
    file = std::shared_ptr<std::ofstream>(new std::ofstream,
                                          [](std::ofstream *ptr) {
                                            ptr->close();
                                            delete ptr;
                                          });
    file->open(name, std::ofstream::out | std::ofstream::app);
    if (!file->is_open())
      std::cout << "\nError: log file " << name
                << " hasn't created\n";  //а куда еще выводить)
  }

  /*!
   * \brief Logger Overload
   * \param rhs
   */
  Logger(const Logger &rhs) : file(rhs.file) {}

  template <typename T>
  /*!
   * \brief operator << Writes to an open file
   * \param input
   * \return
   */
  Logger &operator<<(T input) {
    // m_buffer << input;
    *file << input;
    return *this;
  }

 private:
  std::shared_ptr<std::ofstream> file;
  TypeLog m_level;
  // std::ostringstream m_buffer;
};

class ManagerLoggers {
 public:
  /*!
   * \brief Instance Provides access to a singleton
   * \param mode Determines the recording mode: either for each class its own
   * file, or all is written in one log
   * \param puth Path to the storage location of the created log, must be a
   * slash at the end.
   * \return
   */
  static ManagerLoggers &Instance(
      ModeSave mode = multiStream,
      /*TypeLog type = DEBUG,*/ std::string puth = "") {
    static ManagerLoggers m(mode, /* type,*/ puth);
    return m;
  }

  /*!
   * \brief getLogger Creates a single instance of the log file.
   * \param name Name of class
   * \return
   */
  Logger &getLogger(
      const std::string &name = "multilog" /*, TypeLog level = DEBUG*/) {
    if (m_loggers.find(name) != m_loggers.end()) {
      return m_loggers.at((m_modeSave == oneStream) ? ("multilog") : (name));
    } else {
      time_t nowTime = time(0);
      struct tm nowInfo = *localtime(&nowTime);
      char nowStr1[40];
      strftime(nowStr1, 40, "%I_%M%p", &nowInfo);
      std::string nowStr2(nowStr1);
      std::string path(m_puth);
      path += nowStr2 + std::string("_");
      switch (m_modeSave)  // shit cod detected
      {
        case oneStream:
          path += std::string("multilog.log");

          m_loggers["multilog"] = Logger(path /*, level*/);
          return m_loggers.at("multilog");
        case multiStream:
          path += name + std::string(".log");

          m_loggers[name] = Logger(path /*, level*/);
          return m_loggers.at(name);
      }
      throw EXCEPTION("Something is wrong", nullptr);
    }
  }

 private:
  /*!
   * \brief ManagerLoggers Singleton
   * \param mode
   * \param puth
   */
  ManagerLoggers(ModeSave mode = multiStream,
                 /*TypeLog type = DEBUG,*/ const std::string &puth = "")
      : m_modeSave(mode), /*m_typeLog(type),*/ m_puth(puth) {}
  ModeSave m_modeSave;
  // TypeLog m_typeLog;
  std::string m_puth;
  std::map<std::string, Logger> m_loggers;
};
}

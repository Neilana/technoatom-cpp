#pragma once

#include <QDebug>
//#include <QDir>
//#include <QFile>
//#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace IlluminatiConfirmed {
class GameDatabase {
 private:
  QSqlDatabase m_db;
  GameDatabase();

 public:
  static GameDatabase& getInstance() {
    static GameDatabase instance;
    return instance;
  };
};
}

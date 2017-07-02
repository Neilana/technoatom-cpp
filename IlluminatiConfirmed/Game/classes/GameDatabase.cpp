
#include "GameDatabase.h"

#include <QDebug>
//#include <QDir>
//#include <QFile>
//#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

using IlluminatiConfirmed::GameDatabase;

GameDatabase::GameDatabase() {
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName("../Game/resources/database/GameDB.db3");
  m_db.open();

  //  QSqlQuery query;
  //  query.exec("SELECT * FROM CharactersImages");
  //  while (query.next()) {
  //    qDebug() << query.value(1).toString();
  //  }
}

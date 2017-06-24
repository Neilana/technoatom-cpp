#ifndef BIGWHILE_H
#define BIGWHILE_H

#include <QCoreApplication>
#include <QObject>
#include <QtConcurrent>

#include <exception>
#include <iostream>
#include <vector>

#include "../Exceptions/Exception.h"
#include "Game.h"
#include "constants.h"

#include "ScreenChoseCharacters.h"
#include "ScreenGame.h"
#include "ScreenMenuChoseMap.h"
#include "ScreenMenuLoad.h"
#include "ScreenMenuMain.h"
#include "ScreenMenuSave.h"
#include "screens/Screen.h"

class BigWhile : public QObject {
  Q_OBJECT
 public:
  explicit BigWhile(QObject *parent = nullptr);

 public slots:
  void process();
 signals:
  void finished();

 private:
  std::map<ScreenName, std::shared_ptr<IlluminatiConfirmed::Screen>>
      m_screenNameToScreen;
  sf::RenderWindow m_window;
  IlluminatiConfirmed::Game *m_game;
  ScreenName m_screenName;
};

#endif  // BIGWHILE_H

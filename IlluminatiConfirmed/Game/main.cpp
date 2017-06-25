#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include <QtConcurrent>

#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"

#include <SFML/Graphics.hpp>
#include "gtest/gtest.h"

#include <exception>
#include <iostream>
#include <vector>

#include "../Exceptions/Exception.h"
#include "Game.h"
#include "Level.h"

#include "Factories.h"
#include "ScreenChoseCharacters.h"
#include "ScreenGame.h"
#include "ScreenMenuChoseMap.h"
#include "ScreenMenuLoad.h"
#include "ScreenMenuMain.h"
#include "ScreenMenuSave.h"
#include "screens/Screen.h"
//#include "constants.h"

#include "GameDatabase.h"

#include "BigWhile.h"

using namespace sf;
using namespace std;

using namespace IlluminatiConfirmed;

// int main(int argc, char *argv[]) {
//     ::testing::InitGoogleTest(&argc, argv);
//      // запускаем только определённый тест (чтобы проще смотреть дампы)
//      //::testing::GTEST_FLAG(filter) = "VectorTest3*";

//      return RUN_ALL_TESTS();
// }

int main(int argc, char* argv[]) {
  IlluminatiConfirmed::experimental::FactoryObjects::Instance();

  QCoreApplication a(argc, argv);
  auto main_thread = QCoreApplication::instance()->thread();

  // QThread* thread = new QThread;
  BigWhile* big_while = new BigWhile();
  big_while->moveToThread(main_thread);
  QObject::connect(main_thread, SIGNAL(started()), big_while, SLOT(process()));
  QObject::connect(big_while, SIGNAL(finished()), main_thread, SLOT(quit()));
  QObject::connect(big_while, SIGNAL(finished()), big_while,
                   SLOT(deleteLater()));
  QObject::connect(main_thread, SIGNAL(finished()), main_thread,
                   SLOT(deleteLater()));

  QTimer timer;
  timer.setInterval(2);  // Задаем интервал таймера
  QObject::connect(
      &timer, SIGNAL(timeout()), big_while,
      SLOT(process()));  // Подключаем сигнал таймера к нашему слоту
  timer.start();
  // main_thread->start();

  return a.exec();
}

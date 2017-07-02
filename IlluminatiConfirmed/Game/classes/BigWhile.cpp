#include "BigWhile.h"
#include <QCoreApplication>
#include <QObject>
#include <QtConcurrent>

#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"

#include <SFML/Graphics.hpp>
#include "gtest/gtest.h"

#include <exception>
#include <iostream>
#include <memory>
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

using namespace IlluminatiConfirmed;
using namespace sf;

BigWhile::BigWhile(QObject *parent) : QObject(parent) {
  try {
    // GameDatabase db = GameDatabase::getInstance();

    // menu = 0
    auto screen0 = std::static_pointer_cast<IlluminatiConfirmed::Screen>(
        std::make_shared<ScreenMenuMain>());
    m_screenNameToScreen.insert({ScreenName::MainMenu, std::move(screen0)});

    // new game = 1
    auto screen1 = std::static_pointer_cast<IlluminatiConfirmed::Screen>(
        std::make_shared<ScreenChoseCharacters>());
    m_screenNameToScreen.insert(
        {ScreenName::ChoseCharacters, std::move(screen1)});

    // game = 1
    auto screen2 = std::static_pointer_cast<IlluminatiConfirmed::Screen>(
        std::make_shared<ScreenGame>());
    m_screenNameToScreen.insert({ScreenName::Game, std::move(screen2)});

    // load
    auto screen3 = std::static_pointer_cast<IlluminatiConfirmed::Screen>(
        std::make_shared<ScreenMenuLoad>());
    m_screenNameToScreen.insert({ScreenName::Load, std::move(screen3)});

    // save
    auto screen4 = std::static_pointer_cast<IlluminatiConfirmed::Screen>(
        std::make_shared<ScreenMenuSave>());
    m_screenNameToScreen.insert({ScreenName::Save, std::move(screen4)});

    // chose
    auto screen5 = std::static_pointer_cast<IlluminatiConfirmed::Screen>(
        std::make_shared<ScreenMenuChoseMap>());
    m_screenNameToScreen.insert({ScreenName::ChoseMap, std::move(screen5)});

    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Level.h test");
     m_window.setFramerateLimit(60);

    // std::stringstream sstream;
    sf::Text fpsCounter;
    sf::Font mainFont;
    if (!mainFont.loadFromFile(FONT_FILE))  // Set path
      // to your
      // font
      throw EXCEPTION("I can't open file with font.", nullptr);
    fpsCounter.setFont(mainFont);
    fpsCounter.setColor(sf::Color::White);

    m_game = new Game(m_window);

    // while (screenName != ScreenName::Exit) {
    m_screenName = ScreenName::MainMenu;
  } catch (IlluminatiConfirmed::Exception &e) {
    std::cout << e.what();
  }
}

void BigWhile::process() {
  try {
    if (m_window.isOpen()) {
      m_screenName =
          m_screenNameToScreen.at(m_screenName)->run(*m_game, m_window);
    } else
      emit finished();
  } catch (IlluminatiConfirmed::Exception &e) {
    std::cout << e.what();
  }
}

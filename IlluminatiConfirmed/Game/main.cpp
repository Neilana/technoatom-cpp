#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"

#include "gtest/gtest.h"
#include <SFML/Graphics.hpp>

#include <exception>
#include <iostream>
#include <vector>

#include "../Exceptions/Exception.h"
#include "Game.h"
#include "Level.h"

#include "Factories.h"
#include "ScreenChoseCharacters.h"
#include "ScreenGame.h"
#include "ScreenMenuLoad.h"
#include "ScreenMenuMain.h"
#include "ScreenMenuSave.h"
#include "screens/Screen.h"
//#include "constants.h"

#include "GameDatabase.h"

using namespace sf;
using namespace std;

using namespace IlluminatiConfirmed;

// int main(int argc, char *argv[]) {
//     ::testing::InitGoogleTest(&argc, argv);
//      // запускаем только определённый тест (чтобы проще смотреть дампы)
//      //::testing::GTEST_FLAG(filter) = "VectorTest3*";

//      return RUN_ALL_TESTS();
// }

int main() {
  try {
    GameDatabase db = GameDatabase::getInstance();

    std::map<ScreenName, Screen *> screenNameToScreen;

    // menu = 0
    ScreenMenuMain screen0;
    screenNameToScreen[ScreenName::MainMenu] = &screen0;

    // new game = 1
    ScreenChoseCharacters screen1;
    screenNameToScreen[ScreenName::ChoseCharacters] = &screen1;

    // game = 1
    ScreenGame screen2;
    screenNameToScreen[ScreenName::Game] = &screen2;

    // load
    ScreenMenuLoad screen3;
    screenNameToScreen[ScreenName::Load] = &screen3;

    // save
    ScreenMenuSave screen4;
    screenNameToScreen[ScreenName::Save] = &screen4;

    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Level.h test");
    window.setFramerateLimit(60);

    // std::stringstream sstream;
    sf::Text fpsCounter;
    sf::Font mainFont;
    if (!mainFont.loadFromFile(FONT_FILE)) // Set path
                                           // to your
                                           // font
      throw EXCEPTION("I can't open file with font.", nullptr);
    fpsCounter.setFont(mainFont);
    fpsCounter.setColor(sf::Color::White);

    // experimental::FactoryObjects::create_factory();
    Game game(window);
    // game.initNewGame(MAP_FILE_1);

    Clock clock;

    // while (screenName != ScreenName::Exit) {
    ScreenName screenName = ScreenName::MainMenu;
    while (window.isOpen()) {
      screenName = screenNameToScreen[screenName]->run(game, window);
    }
  } catch (IlluminatiConfirmed::Exception &e) {
    std::cout << e.what();
  }

  return 0;
}

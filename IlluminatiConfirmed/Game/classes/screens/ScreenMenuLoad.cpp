
#include "ScreenMenuLoad.h"
#include "constants.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
using IlluminatiConfirmed::ScreenMenuLoad;

ScreenMenuLoad::ScreenMenuLoad() {
  m_title.setString("Load Game");

  initBackground();
  initTitle();
}

ScreenName ScreenMenuLoad::run(Game &game, sf::RenderWindow &window) {
  sf::Event Event;
  //  bool running = true;
  ScreenName screen = ScreenName::Load;

  window.clear();

  // Drawing
  window.draw(m_backgroundSprite);
  window.draw(m_title);

  window.display();
  game.loadGame("1.txt");
  while (window.isOpen()) {
    while (window.pollEvent(Event)) {
      if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        return ScreenName::MainMenu;
      }
    }
  }

  return screen;
}

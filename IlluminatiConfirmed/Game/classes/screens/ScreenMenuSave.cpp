
#include "ScreenMenuSave.h"
#include "constants.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
using IlluminatiConfirmed::ScreenMenuSave;

ScreenMenuSave::ScreenMenuSave() {
  m_title.setString("Save Game");

  initBackground();
  initTitle();
}

ScreenName ScreenMenuSave::run(Game &game, sf::RenderWindow &window) {
  ScreenName screen = ScreenName::Save;

  window.clear();
  // Drawing
  window.draw(m_backgroundSprite);
  window.draw(m_title);
  window.display();

  game.saveGame("1.txt");
  sf::Event Event;
  while (window.isOpen()) {
    while (window.pollEvent(Event)) {
      if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        return ScreenName::MainMenu;
      }
    }
  }

  return screen;
}

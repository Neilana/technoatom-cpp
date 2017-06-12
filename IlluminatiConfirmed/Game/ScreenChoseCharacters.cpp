#include <SFML/Graphics.hpp>

#include "ScreenChoseCharacters.h"

using namespace sf;
using namespace std;

using IlluminatiConfirmed::ScreenChoseCharacters;

ScreenChoseCharacters::ScreenChoseCharacters() {
  if (!m_backgroundTexture.loadFromFile(
          "../Game/sprites/backgrounds/menu3_1.png")) {
    // std::cout << "Error loading presentation.gif" << std::endl;
    // return (-1);
  }
  m_backgroundSprite.setTexture(m_backgroundTexture);
  // sprite.setColor(sf::Color(255, 255, 255, alpha));
  if (!m_font.loadFromFile("../Game/res/Franchise-Bold-hinted.ttf")) {
    // std::cerr << "Error loading verdanab.ttf" << std::endl;
    // return (-1);
  }
  // 0

  float titleX = WINDOW_WIDTH / 2.0 - 100;
  float titleY = 25;
  float fontSize = 45;

  m_title.setFont(m_font);
  m_title.setCharacterSize(fontSize);
  m_title.setString("Chose Characters");
  m_title.setPosition(titleX, titleY);
  m_title.setColor(sf::Color::White);
}

ScreenName ScreenChoseCharacters::run(Game &game, sf::RenderWindow &window) {
  bool running = true;
  sf::Event event;
  window.clear();

  while (running) {
    while (window.pollEvent(event)) {
      if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        return ScreenName::MainMenu;
      }

      if (Keyboard::isKeyPressed(Keyboard::Return)) {
        return ScreenName::Game;
      }
      window.draw(m_backgroundSprite);
      window.draw(m_title);
      window.display();
    }
  }
}

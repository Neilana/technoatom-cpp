#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"
#include <SFML/Graphics.hpp>

#include <exception>
#include <iostream>
#include <strstream>
#include <vector>

#include "../Exceptions/Exception.h"
#include "Screen.h"
#include "ScreenGame.h"
#include "ScreenMenuMain.h"

#include "Game.h"
#include "Level.h"

using namespace sf;
using namespace std;

using namespace IlluminatiConfirmed;

ScreenGame::ScreenGame() {}

ScreenName ScreenGame::run(Game &game, sf::RenderWindow &window) {
  if (!game.isRunning())
    return ScreenName::MainMenu;

  Clock clock;
  bool running = true;
  auto currentHero = game.selectNextHero();

  while (game.isRunning() && window.isOpen()) {
    auto timeSf = clock.restart();
    auto time = timeSf.asMicroseconds();
    time = time / 800;

    sf::Text fpsCounter;
    sf::Font mainFont;
    if (!mainFont.loadFromFile(FONT_FILE))
      throw EXCEPTION("I can't open file with font.", nullptr);
    fpsCounter.setFont(mainFont);
    fpsCounter.setColor(sf::Color::White);

    sf::Event event;
    sf::Mouse::getPosition();

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Tab) {
          currentHero = game.selectNextHero();
        }
        // если написать ниже - будет трэш, будет оооч много создаваться сразу
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          currentHero->attack();
        }
      }
    }

    b2Vec2 velocity = {0.f, 0.f};
    if (Keyboard::isKeyPressed(Keyboard::A) ||
        Keyboard::isKeyPressed(Keyboard::Left)) {
      velocity += b2Vec2({-1.f, 0.f});
    }
    if (Keyboard::isKeyPressed(Keyboard::D) ||
        Keyboard::isKeyPressed(Keyboard::Right)) {
      // currentHero->move(Direction::Right, time);
      velocity += b2Vec2({+1.f, 0.f});
    }
    if (Keyboard::isKeyPressed(Keyboard::W) ||
        Keyboard::isKeyPressed(Keyboard::Up)) {
      // currentHero->move(Direction::Up, time);
      velocity += b2Vec2({0.f, -1.f});
    }
    if (Keyboard::isKeyPressed(Keyboard::S) ||
        Keyboard::isKeyPressed(Keyboard::Down)) {
      // currentHero->move(Direction::Down, time);
      velocity += b2Vec2({0.f, +1.f});
    }
    if (velocity.Length() > 0.0) {
      currentHero->move(velocity, time);
    }

    game.updatePhysics(time);
    window.clear();
    game.draw(window);

    static bool press = true;
    if (Keyboard::isKeyPressed(Keyboard::F1)) {
      static int timeout;
      timeout += 1;
      if (timeout == 30) {
        press = !press;
        timeout = 0;
      }
    }
    if (press) {
      std::strstream sstream;
      sstream << "FPS: " << int(1.f / timeSf.asSeconds());
      fpsCounter.setString(sstream.str());
      window.draw(fpsCounter);
      game.getWorld().DrawDebugData();
    }

    window.display();
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      return ScreenName::MainMenu;
    }
  }
  return ScreenName::Game;
}

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"

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
  if (!game.isRunning()) return ScreenName::MainMenu;

  Clock clock;
  bool running = true;
  auto currentHero1 = game.selectNextHero();
  auto currentHero2 = game.selectNextHero();

  while (game.isRunning() && window.isOpen()) {
    if (currentHero1->isDead() || currentHero2->isDead())
      return ScreenName::MainMenu;
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
      if (event.type == sf::Event::Closed) window.close();

      if (event.type == sf::Event::KeyPressed) {
        //        if (event.key.code == sf::Keyboard::Tab) {
        //          currentHero = game.selectNextHero();
        //        }
        if (event.key.code == sf::Keyboard::Space) {
          currentHero1->attack();
        }
        if (event.key.code == sf::Keyboard::Numpad0) {
          currentHero2->attack();
        }

        if (event.key.code == sf::Keyboard::RControl) {
          game.setNewWeapon(currentHero2);
        }

        if (event.key.code == sf::Keyboard::LControl) {
          game.setNewWeapon(currentHero1);
        }
      }
      //      if (event.type == sf::Event::MouseButtonPressed) {
      //        if (event.mouseButton.button == sf::Mouse::Left) {
      //          currentHero->attack();
      //        }
      //      }
    }

    b2Vec2 velocity1 = {0.f, 0.f};
    if (Keyboard::isKeyPressed(Keyboard::A)) {
      velocity1 += b2Vec2({-1.f, 0.f});
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
      // currentHero->move(Direction::Right, time);
      velocity1 += b2Vec2({+1.f, 0.f});
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
      // currentHero->move(Direction::Up, time);
      velocity1 += b2Vec2({0.f, -1.f});
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
      // currentHero->move(Direction::Down, time);
      velocity1 += b2Vec2({0.f, +1.f});
    }
    if (velocity1.Length() > 0.0) {
      currentHero1->move(velocity1, time);
    }

    b2Vec2 velocity2 = {0.f, 0.f};
    if (Keyboard::isKeyPressed(Keyboard::F)) {
      velocity2 += b2Vec2({-1.f, 0.f});
    }
    if (Keyboard::isKeyPressed(Keyboard::H)) {
      velocity2 += b2Vec2({+1.f, 0.f});
    }
    if (Keyboard::isKeyPressed(Keyboard::T)) {
      velocity2 += b2Vec2({0.f, -1.f});
    }
    if (Keyboard::isKeyPressed(Keyboard::G)) {
      velocity2 += b2Vec2({0.f, +1.f});
    }
    if (velocity2.Length() > 0.0) {
      currentHero2->move(velocity2, time);
    }

    static float angle1 = 0;
    if (Keyboard::isKeyPressed(Keyboard::Numpad4)) {
      angle1 += 2.5f;
    }
    if (Keyboard::isKeyPressed(Keyboard::Numpad6)) {
      angle1 -= 2.5f;
    }
    currentHero2->setAngleOfWeapon(angle1);
    static float angle2 = 0;
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
      angle2 += 2.5f;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
      angle2 -= 2.5f;
    }
    currentHero1->setAngleOfWeapon(angle2);

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

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"

#include <exception>
#include <iostream>
#include <vector>

#include "../Exceptions/Exception.h"
#include "Screen.h"
#include "ScreenGame.h"
#include "ScreenMenu.h"

#include "ScreenGame.h"

#include "Character.h"
#include "Game.h"
#include "Level.h"

using namespace sf;
using namespace std;

using IlluminatiConfirmed::Character;
using IlluminatiConfirmed::Game;
using IlluminatiConfirmed::Screen;
using IlluminatiConfirmed::ScreenGame;

using IlluminatiConfirmed::ScreenGame;

ScreenGame::ScreenGame() {}

ScreenName ScreenGame::run(Game &game, sf::RenderWindow &window) {
  Clock clock;
  bool running = true;
  auto currentHero = game.selectNextHero();

  while (running) {
    auto timeSf = clock.restart();
    auto time = timeSf.asMicroseconds();
    time = time / 800;

    sf::Event event;
    sf::Mouse::getPosition();

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Tab) {
          currentHero = game.selectNextHero();
        }
        // если написать ниже - будет трэш, будет оооч много создаваться сразу
        if (event.key.code == sf::Keyboard::Space) {
          game.sendBullet(currentHero.get());
          // currentHero->attack();
        }
      }
    }

    if (Keyboard::isKeyPressed(Keyboard::Left)) {
      currentHero->move(Direction::Left, time);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
      currentHero->move(Direction::Right, time);
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
      currentHero->move(Direction::Up, time);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
      currentHero->move(Direction::Down, time);
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      return ScreenName::MainMenu;
    }
    game.updatePhysics();
    game.draw(window);
  }
  return ScreenName::Game;
}

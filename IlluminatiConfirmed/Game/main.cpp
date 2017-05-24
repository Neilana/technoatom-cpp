#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"

#include <exception>
#include <iostream>
#include <vector>

#include "../Exceptions/Exception.h"
#include "Character.h"
#include "Game.h"
#include "Level.h"
//#include "constants.h"

using namespace sf;
using namespace std;

int main() {
  try {
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Level.h test");

    b2World world(b2Vec2(0.0f, 0.0f));
    world.Dump();

    Game game(&world);
    game.initNewGame("../Game/maps/map25x25_1.tmx");

    auto currentHero = game.selectNextHero();

    Clock clock;
    world.Dump();
    while (window.isOpen()) {
      float time = clock.getElapsedTime().asMicroseconds();
      clock.restart();
      time = time / 800;

      sf::Event event;

      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::KeyPressed) {
          if (event.key.code == sf::Keyboard::Tab) {
            currentHero = game.selectNextHero();
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
      world.Step(1 / 60.f, 8, 3);

      for (auto &&it : game.m_heroes) it->updatePhysics();
      window.clear();
      game.updatePhysics();
      game.draw(window);

      window.display();
    }
  } catch (IlluminatiConfirmed::Exception &e) {
    std::cout << e.what();
  }

  return 0;
}

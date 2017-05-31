#include "Box2D.h"
#include <SFML/Graphics.hpp>

#include <exception>
#include <iostream>
#include <vector>

#include "../Exceptions/Exception.h"
#include "Character.h"
#include "Game.h"
#include "Level.h"
#include "SFMLDebugDraw.h"
//#include "constants.h"

using namespace sf;
using namespace std;

int main() {
  try {
    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Level.h test");
    window.setFramerateLimit(60);

    b2World world(b2Vec2(0.0f, 0.0f));
    world.Dump();
    SFMLDebugDraw debugDraw(window);
    world.SetDebugDraw(&debugDraw);
    debugDraw.SetFlags(b2Draw::e_shapeBit + b2Draw::e_aabbBit +
                       b2Draw::e_centerOfMassBit + b2Draw::e_pairBit);
    std::stringstream sstream;
    sf::Text fpsCounter;
    sf::Font mainFont;
    if (!mainFont.loadFromFile(
            "../Game/res/Franchise-Bold-hinted.ttf")) // Set path to your font
      throw EXCEPTION("I can't open file with font.", nullptr);
    fpsCounter.setFont(mainFont);
    fpsCounter.setColor(sf::Color::White);

    Game game(&world);
    game.initNewGame("../Game/maps/map25x25_1.tmx");

    auto currentHero = game.selectNextHero();

    Clock clock;
    world.Dump();
    while (window.isOpen()) {
      auto timeSf = clock.restart();
      auto time = timeSf.asMicroseconds();
      time = time / 800;

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

      world.Step(1 / 60.f, 8, 3);

      window.clear();
      game.updatePhysics(window);
      game.draw(window);
      world.DrawDebugData();

      sstream.precision(0);
      sstream << std::fixed << "FPS: " << 1.f / timeSf.asSeconds();
      fpsCounter.setString(sstream.str());
      window.draw(fpsCounter);
      sstream.str("");
      window.display();
    }
  } catch (IlluminatiConfirmed::Exception &e) {
    std::cout << e.what();
  }

  return 0;
}

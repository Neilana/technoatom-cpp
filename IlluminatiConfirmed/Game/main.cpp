#include <SFML/Graphics.hpp>
#include <exception>
#include <iostream>
#include "../Exceptions/Exception.h"
#include "level.h"

int main() {
  try {
    Level level;
    level.LoadFromFile("../Game/Map/map25x25_1.tmx");
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 800), "Level.h test");

    while (window.isOpen()) {
      sf::Event event;

      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
      }

      window.clear();
      level.Draw(window);
      window.display();
    }

  } catch (std::exception &e) {
    std::cout << e.what();
  } catch (IlluminatiConfirmed::Exception &e) {
    std::cout << e.what();
  }

  return 0;
}

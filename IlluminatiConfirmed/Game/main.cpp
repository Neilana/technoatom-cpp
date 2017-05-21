#include <SFML/Graphics.hpp>

#include <exception>
#include <iostream>
#include <vector>

#include "../Exceptions/Exception.h"
#include "Level.h"
#include "Character.h"
#include "constants.h"

using namespace sf;

int main() {
    try {
        Level level;
        level.loadMapFromFile("../Game/Map/map25x25_1.tmx");
        sf::RenderWindow window;
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Level.h test");

        // ПОЛЕ ДЛЯ ЭКСПЕРИМЕНТОВВВВВ!!!!!!!!!!!!!11111111111111111111
        Character hero1("../Game/Sprites/demon.png", 4, 64, 64);
        //Character hero1("../Game/Sprites/panda.png", 3, 32, 32);
        //Character hero1("../Game/Sprites/spider.png", 5, 64, 64);

        Clock clock;

        while (window.isOpen())
        {

            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;

            sf::Event event;

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                hero1.move(Direction::Left, time);
            }
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                hero1.move(Direction::Right, time);
            }
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                hero1.move(Direction::Up, time);\
            }
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                hero1.move(Direction::Down, time);
            }

            window.clear();

            level.Draw(window);
            hero1.draw(window);

            window.display();
        }

    } catch (IlluminatiConfirmed::Exception &e2) {
        std::cout << e2.what();
    } catch (IlluminatiConfirmed::Exception &e) {
        std::cout << e.what();
    }

    return 0;
}

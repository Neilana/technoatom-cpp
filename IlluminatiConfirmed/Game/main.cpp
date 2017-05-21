#include <SFML/Graphics.hpp>

#include <exception>
#include <iostream>
#include <vector>

#include "../Exceptions/Exception.h"
#include "Level.h"
#include "Character.h"
#include "constants.h"

using namespace sf;
using namespace std;

int main() {
    try {
        Level level;
        level.loadMapFromFile("../Game/maps/map25x25_1.tmx");
        sf::RenderWindow window;
        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Level.h test");

        vector<Character> heroes;
        int currentHero = 0;

        // ПОЛЕ ДЛЯ ЭКСПЕРИМЕНТОВВВВВ!!!!!!!!!!!!!11111111111111111111
        Character hero1("../Game/sprites/demon.png", 4, 64, 64);
        heroes.push_back(hero1);

        Character hero2("../Game/sprites/panda.png", 3, 32, 32);
        hero2.setCoordinates(100,100);
        heroes.push_back(hero2);

        Character hero3("../Game/sprites/spider.png", 10, 64, 64);
        hero3.setCoordinates(300,300);
        heroes.push_back(hero3);

        Clock clock;

        while (window.isOpen())
        {

            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;

            sf::Event event;

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Tab)
                    {
                        currentHero++, currentHero %= heroes.size();
                    }
                }
            }

            //if (Keyboard::isKeyPressed(Keyboard::Tab))
              //  currentHero++, currentHero %= heroes.size();

            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                heroes[currentHero].move(Direction::Left, time);
            }
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                heroes[currentHero].move(Direction::Right, time);
            }
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                heroes[currentHero].move(Direction::Up, time);\
            }
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                heroes[currentHero].move(Direction::Down, time);
            }

            window.clear();

            level.Draw(window);

            for (auto it = heroes.begin(); it != heroes.end(); it++)
                it->draw(window);
                //hero1.draw(window);

            window.display();
        }

    } catch (IlluminatiConfirmed::Exception &e2) {
        std::cout << e2.what();
    } catch (IlluminatiConfirmed::Exception &e) {
        std::cout << e.what();
    }

    return 0;
}

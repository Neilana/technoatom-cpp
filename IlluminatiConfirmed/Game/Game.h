#pragma once

#include "Box2D/Box2D.h"

#include <vector>
#include <string>

#include "Level.h"
#include "Character.h"
#include "constants.h"

class Game
{
private:
    Level m_level;
    int m_currentHeroId;

    // physics Box2D
    std::vector<Object> walls; //level?
    b2World *world;
    b2Body* playerBody;

public:
    std::vector<Character> m_heroes;

    Game();
    void initNewGame(const std::string &mapFile);
    void initCharacters();
    void initPhysics();

    void draw(sf::RenderWindow &window);

    Character* selectNextHero() { m_currentHeroId++; m_currentHeroId %= m_heroes.size(); return &m_heroes[m_currentHeroId]; }
    //void moveActiveHero(Direction dir, float time) { m_heroes[m_currentHero].move(dir); }

    //void update(time, key);
    void updatePhysics();
};



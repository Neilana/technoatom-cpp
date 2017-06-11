#pragma once

#include "Box2D/Box2D.h"

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "Bullet.h"
#include "Character.h"
#include "Level.h"
#include "constants.h"

using IlluminatiConfirmed::Character;

namespace IlluminatiConfirmed {
class Game {
private:
  Level m_level;
  int m_currentHeroId;
  b2World *m_world;

  // physics Box2D
  // std::vector<Object> walls; // level?
  std::unique_ptr<b2World> world;
  // std::list<Bullet*> bullets;
  std::list<std::shared_ptr<Bullet>> bullets;

  b2Body *playerBody;

  void buildBarriers(std::vector<Object> &walls);

public:
  std::vector<std::shared_ptr<Character>> m_heroes;

  Game(b2World *world);
  void initNewGame(const std::string &mapFile);
  void initCharacters();
  void initPhysics();
  // void LoadMap(std::vector<Object> &&vec, sf::Vector2i tileSize);

  void draw(sf::RenderWindow &window);

  std::shared_ptr<Character> selectNextHero() {
    m_currentHeroId++;
    m_currentHeroId %= m_heroes.size();
    return m_heroes[m_currentHeroId];
  }
  // void moveActiveHero(Direction dir, float time) {
  // m_heroes[m_currentHero].move(dir); }

  // void update(time, key);
  void updatePhysics(sf::RenderWindow &window);

  void sendBullet(Character *hero);
};
}

#pragma once

#include "Box2D/Box2D.h"

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "Bullet.h"
#include "Character.h"
#include "Level.h"
#include "charactersouthpark.h"
#include "constants.h"

using IlluminatiConfirmed::Character;

namespace IlluminatiConfirmed {
class Game {
 public:
  Level m_level;
  int m_currentHeroId;
  // b2World *m_world;
  b2World m_world;
  inline b2World &getWorld() { return m_world; }

  // physics Box2D
  // std::unique_ptr<b2World> m_world;
  std::list<std::shared_ptr<Bullet>> m_bullets;
  std::vector<std::shared_ptr<BaseCharacter>> m_heroes;

  b2Body *playerBody;

  void buildBarriers(std::vector<Object> &walls);

 public:
  Game(sf::RenderWindow &window);
  void initNewGame(const std::string &mapFile);
  void initCharacters();
  void initPhysics();
  // void LoadMap(std::vector<Object> &&vec, sf::Vector2i tileSize);

  void draw(sf::RenderWindow &window);

  std::shared_ptr<BaseCharacter> selectNextHero() {
    m_currentHeroId++;
    m_currentHeroId %= m_heroes.size();
    return m_heroes[m_currentHeroId];
  }
  // void moveActiveHero(Direction dir, float time) {
  // m_heroes[m_currentHero].move(dir); }

  // void update(time, key);
  void updatePhysics();

  void sendBullet(Character *hero);
};
}

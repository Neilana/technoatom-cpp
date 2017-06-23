#pragma once

#include "Box2D/Box2D.h"

#include <list>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "Base.h"
#include "Bullet.h"
#include "Character.h"
#include "Ground.h"
#include "Level.h"
#include "Weapons.h"
#include "constants.h"

// using IlluminatiConfirmed::Character;

namespace IlluminatiConfirmed {
class Game {
public:
  //<<<<<<< HEAD
  sf::Texture m_texture;

  // b2World *m_world;

  bool m_running;
  // physics Box2D
  // std::unique_ptr<b2World> m_world;
  // std::list<std::shared_ptr<Bullet>> m_bullets;

  std::vector<experimental::Building> m_vec_map;

  void buildBarriers(std::vector<Object> &walls);

public:
  Game(sf::RenderWindow &window);
  void initNewGame(std::set<int> ids, sf::RenderWindow &window);
  void initCharacters(std::set<int> ids);
  // void initNewGame(const std::string &map_puth, const std::string &file);
  void initObjects(std::set<int> ids);

  void initPhysics();
  void draw(sf::RenderWindow &window);

  bool isRunning() { return m_running; }
  // std::shared_ptr<BaseCharacter> selectNextHero() {

  void updatePhysics(float time);
  void saveGame(const std::string &fileName);
  void loadGame(const std::string &fileName);
  void setMapFileName(const std::string &fileName);
  inline b2World &getWorld() { return *m_world; }
  std::shared_ptr<experimental::BaseCharacter> selectNextHero() {
    m_currentHeroId++;
    m_currentHeroId %= m_heroes.size();
    return m_heroes[m_currentHeroId];
  }

private:
  std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
  std::shared_ptr<b2World> m_world;
  std::shared_ptr<Ground> m_ground;
  std::string m_mapFileName;
  std::vector<std::shared_ptr<experimental::BaseInterface>> m_vector_of_objs;
  std::vector<std::shared_ptr<experimental::BaseCharacter>> m_heroes;
  std::vector<std::shared_ptr<experimental::Bullet>> m_bullets;
  experimental::ListnerWeapon listner_of_bullets;

  std::shared_ptr<sf::Texture> p_texture;
  std::shared_ptr<sf::Texture> p_texture_bullet;
  int m_currentHeroId;
  int a;
};
}

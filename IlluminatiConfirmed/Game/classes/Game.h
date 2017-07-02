#pragma once

#include "Box2D/Box2D.h"

#include <list>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include <QObject>
#include <QtCore>

#include "Base.h"
#include "Bullet.h"
#include "Character.h"
#include "Ground.h"
#include "HUD.h"
#include "Level.h"
#include "MyContactListener.h"
#include "Weapons.h"
#include "constants.h"

namespace IlluminatiConfirmed {
class Game {
 public:
  sf::Texture m_texture;
  bool m_running;

  std::vector<experimental::Building> m_vec_map;

  void buildBarriers(std::vector<Object> &walls);

 public:
  Game(sf::RenderWindow &window);
  void initNewGame(std::set<int> ids, sf::RenderWindow &window);
  void initCharacters(std::set<int> ids);
  void initObjects(std::set<int> ids);

  void initPhysics();
  void draw(sf::RenderWindow &window);

  bool isRunning() { return m_running; }

  void updatePhysics(float time);
  void saveGame(const std::string &fileName);
  void loadGame(const std::string &fileName);
  void setMapFileName(const std::string &fileName);
  inline b2World &getWorld() { return *m_world; }
  std::shared_ptr<experimental::BaseCharacter> selectNextHero() {
    m_HUDs[m_currentHeroId].get()->unselect();
    m_currentHeroId++;
    m_currentHeroId %= m_heroes.size();
    m_HUDs[m_currentHeroId].get()->select();
    return m_heroes[m_currentHeroId];
  }

  void setNewWeapon(const std::shared_ptr<experimental::BaseCharacter> &hero);

 private:
  std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
  std::shared_ptr<b2World> m_world;
  std::shared_ptr<Ground> m_ground;
  std::string m_mapFileName;
  std::vector<std::shared_ptr<experimental::BaseInterface>> m_vector_of_objs;
  std::vector<std::shared_ptr<experimental::BaseCharacter>> m_heroes;

  //  std::vector<std::shared_ptr<experimental::Bullet>> m_bullets;
  std::vector<std::shared_ptr<HUD>> m_HUDs;
  std::vector<std::shared_ptr<experimental::BulletInterface>> m_bullets;

  experimental::ListnerWeapon listner_of_bullets;
  std::unique_ptr<MyContactListener> b2_listner_collision;

  std::shared_ptr<sf::Texture> p_texture;
  std::shared_ptr<sf::Texture> p_texture_bullet;
  int m_currentHeroId;
  int a;
};
}

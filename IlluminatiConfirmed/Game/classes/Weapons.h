#pragma once

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

#include "Bullet.h"
#include "Event/Event.h"
#include "Factories.h"

namespace IlluminatiConfirmed {
namespace experimental {

struct WeaponInfo {
  TypeBullet bullet_type;
  sf::Rect<int> rect_with_weapon;
  sf::Rect<int> rect_with_weapon_fire;
  int number_of_cartridge;  // damage в пульке
  float scale;
};

class SpriteInterface {
  virtual void draw(sf::RenderWindow *) = 0;
};

struct BulletSetsInfo {
  BulletSets sets;
  TypeBullet type;
};

class Weapon {
 public:
  Weapon(sf::Texture *texture, const WeaponInfo &info);

  void setPositionRotation(const sf::Vector2f &pos, float rotation);

  void attack();

  void draw(sf::RenderWindow &window);

  Event<BulletSetsInfo> event_create_bullet;

 private:
  sf::Sprite m_sprite;
  int m_number_of_cartridge;
  sf::Rect<int> m_rect_with_weapon;
  sf::Rect<int> m_rect_with_weapon_fire;
  int m_time;
  TypeBullet m_type_bullet;
};

class ListnerWeapon {
 public:
  ListnerWeapon();
  ListnerWeapon(
      b2World *world,
      std::vector<std::shared_ptr<experimental::Bullet>> *bullets,
      std::vector<std::shared_ptr<experimental::BaseInterface>> *objs);

  void addWeapon(Weapon *class_);

  void pushBullet(BulletSetsInfo &&bullet_sets);
  std::vector<
      std::pair<SyncValue<BulletSetsInfo>, EventListener<BulletSetsInfo>>>
      m_syncValues_and_eventListener;

 private:
  b2World *m_world;
  std::vector<std::shared_ptr<experimental::Bullet>> *m_bullets;
  std::vector<std::shared_ptr<experimental::BaseInterface>> *m_objs;
};
}
}

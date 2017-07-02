#pragma once

#include <QObject>

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

#include "Bullet.h"

namespace IlluminatiConfirmed {
namespace experimental {

struct WeaponInfo {
  TypeBullet bullet_type;
  sf::Rect<int> rect_weapon;
  int count_of_rect;
  int number_of_cartridge;  // damage в пульке
  float scale;
};

class SpriteInterface {
  virtual void draw(sf::RenderWindow *) = 0;
};

struct BulletSetsInfo {
  BulletSets sets;
  TypeBullet type;
  BaseCharacter *whose;
};

enum WeaponType { BAZOOKA, AK };

class Weapon : public QObject {
  Q_OBJECT
 public:
  Weapon(sf::Texture *texture, const WeaponInfo &info);

  void setPositionRotation(const sf::Vector2f &pos, float rotation);
  void attack(BaseCharacter *who);
  void draw(sf::RenderWindow &window);

  sf::Sprite m_sprite;
  int m_number_of_cartridge;

  virtual ~Weapon() {}

 signals:
  void create_bullet(BulletSetsInfo sets);

 private:
  struct TimeAnimation {
    int time = 0;
    int count = 0;
    int getStartTime() const { return start_time; }
    void setStartTime(int t) { start_time = t; }

   private:
    int start_time = 0;
  };

  void initTimeAnimation();

  std::vector<sf::Rect<int>> m_rects_weapon;
  TimeAnimation m_animation;
  TypeBullet m_type_bullet;
  BaseCharacter *m_whose;
};

class ListnerWeapon : public QObject {
  Q_OBJECT
 public:
  ListnerWeapon();
  void setPointers(
      b2World *world,
      std::vector<std::shared_ptr<experimental::BulletInterface>> *bullets,
      std::vector<std::shared_ptr<experimental::BaseInterface>> *objs);

 public slots:
  void pushBullet(BulletSetsInfo bullet_sets);

 private:
  b2World *m_world;
  std::vector<std::shared_ptr<experimental::BulletInterface>> *m_bullets;
  std::vector<std::shared_ptr<experimental::BaseInterface>> *m_objs;
};
}
}

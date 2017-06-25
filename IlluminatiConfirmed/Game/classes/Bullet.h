#pragma once

#include <vector>

#include <QSound>
#include <QString>

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

#include "Base.h"
#include "constants.h"
#include "Character.h"

namespace IlluminatiConfirmed {
namespace experimental {

struct BulletInfo {
  std::vector<sf::Rect<int>> vec_of_rects_with_bullet;
  BaseCharacter *whose;
  float scale;
  int damage;
  float velocity;
  int width;
  int height;
};

struct BulletSets {
  b2Vec2 position;
  b2Vec2 dir;
};

struct SoundPack {
  std::shared_ptr<QSound> hitting_building;
  std::shared_ptr<QSound> flying;
};

enum class TypeBullet { ROCKET, little_bullet };

class Bullet : public BaseInterface {
 public:
  Bullet(b2World *world, sf::Texture *texture, SoundPack &&pack,
         BulletInfo &&info);
  void setTransform(BulletSets &&sets);
  virtual void draw(sf::RenderWindow &window) override;
  virtual void move(b2Vec2 velocity, float deltaTime) override;
  virtual void contact(BaseInterface *B) override;
  virtual void endContact(BaseInterface *B) override;
  virtual void playHit();
  BaseCharacter *whose() const;

  virtual ~Bullet() { LOG() << "destroy bullet " << std::endl; }

 private:
  BulletInfo m_info;
  SoundPack m_sound_pack;

  sf::Sprite m_sprite;
};

// class Bullet : public BaseInterface {
// public:
//  Bullet(b2World *world, sf::Texture *texture, BulletInfo &&info);
//  void setTransform(BulletSets &&sets);

//  virtual void draw(sf::RenderWindow &window);

//  virtual void move(b2Vec2 velocity, float deltaTime);

//  virtual void contact(b2Fixture *B);
//  virtual void endContact(b2Fixture *B);
//  virtual ~Bullet() {}

// private:
//  BulletInfo m_info;
//  b2Body *m_b2_center;
//  b2Fixture *m_b2_center_fixture;
//  b2MotorJoint *m_b2_joint;
//  float m_angle;

//  sf::Sprite m_sprite;
//};
}
}

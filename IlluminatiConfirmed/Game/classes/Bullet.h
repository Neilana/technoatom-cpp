#pragma once

#include <SFML/Audio.hpp>
#include <vector>

#include <QSound>
#include <QString>

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

#include "Base.h"
#include "Character.h"
#include "constants.h"

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

template <class PlaySound>
struct SoundPackTBullet {
  std::shared_ptr<PlaySound> hitting_building;
  std::shared_ptr<PlaySound> flying;
};

template <>
struct SoundPackTBullet<sf::Sound> {
  SoundPackTBullet(std::shared_ptr<sf::SoundBuffer> &&hit,
                   std::shared_ptr<sf::SoundBuffer> &&fly)
      : hitting_building(std::make_shared<sf::Sound>(*(hit.get()))),
        flying(std::make_shared<sf::Sound>(*(fly.get()))) {}
  std::shared_ptr<sf::Sound> hitting_building;
  std::shared_ptr<sf::Sound> flying;
};

template <>
struct SoundPackTBullet<QSound> {
  SoundPackTBullet(std::shared_ptr<QSound> &&hit, std::shared_ptr<QSound> &&fly)
      : hitting_building(hit), flying(fly) {}
  std::shared_ptr<QSound> hitting_building;
  std::shared_ptr<QSound> flying;
};

enum class TypeBullet { ROCKET, little_bullet };

class BulletInterface : public BaseInterface {
 public:
  using SoundPack = SoundPackTBullet<IlluminatiPlaySound>;
  BulletInterface(b2World *world, sf::Texture *texture, SoundPack pack,
                  BulletInfo info);
  virtual void setTransform(BulletSets &&sets);
  virtual void draw(sf::RenderWindow &window) override;
  virtual void move(b2Vec2 velocity, float deltaTime) override;
  virtual void contact(BaseInterface *B) override;
  virtual void endContact(BaseInterface *B) override;
  virtual void playHit();
  BaseCharacter *whose() const;

  virtual ~BulletInterface() { LOG() << "destroy bullet " << std::endl; }

 protected:
  BulletInfo m_info;
  SoundPack m_sound_pack;
  sf::Sprite m_sprite;
  TypeBullet m_type_bullet;
};

class LittleBullet : public BulletInterface {
 public:
  LittleBullet(b2World *world, sf::Texture *texture, SoundPack pack,
               BulletInfo info);
  ~LittleBullet();
};

class Rocket : public BulletInterface {
 public:
  Rocket(b2World *world, sf::Texture *texture, SoundPack pack,
         BulletInfo info);
  virtual void move(b2Vec2 velocity, float deltaTime) override;

  virtual void draw(sf::RenderWindow &window) override;
  virtual void contact(BaseInterface *B) override;
  virtual void endContact(BaseInterface *B) override;
  virtual void playHit() override;
  virtual void setTransform(BulletSets &&sets) override;

  virtual ~Rocket();

 private:
  b2Body *m_b2_center;
  b2Fixture *m_b2_center_fixture;
  b2MotorJoint *m_b2_joint;
  float m_time;
  int dir = 1;
  float m_angle = 1;
  int dir_angle = -1;

  sf::Sprite m_sprite;
};
}
}

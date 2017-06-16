#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../Logger/Logger.h"
#include "Box2D/Box2D.h"
#include "constants.h"

#define DEBUG_ON
#if defined(DEBUG_ON)
#define LOG() std::cout
#else
#define LOG() LOGGER("level")
#endif

namespace IlluminatiConfirmed {

enum class Type { CHARACTER_SOUTH_PARK, ALINAS_BOYS };

struct CharacterSpriteInfo {
  std::string puth_to_texture;
  int width;
  int height;
  int size;
  int count_of_frames;
  int x_position;
  int y_position;
};

class BaseCharacter {
 public:
  BaseCharacter(Type type, b2World& world,
                const CharacterSpriteInfo& sprite_data);
  Type getType() const;

  virtual void draw(sf::RenderWindow& window) = 0;
  virtual void move(float deltaTime);
  virtual void contact(b2Fixture* B) = 0;
  virtual void endContact(b2Fixture* B) = 0;
  virtual ~BaseCharacter();

  Type m_type;

  std::vector<sf::Rect<int>> front_rects;
  std::vector<sf::Rect<int>> back_rects;
  std::vector<sf::Rect<int>> left_rects;
  std::vector<sf::Rect<int>> right_rects;

  b2Body* m_b2_base;
  b2Fixture* m_b2_base_fixture;
  b2Body* m_b2_body;
  b2Fixture* m_b2_body_fixture;

  sf::Texture texture;
  sf::Sprite m_sprite;
};

class CharacterSouthPark : public BaseCharacter {
 public:
  CharacterSouthPark(b2World& world, const CharacterSpriteInfo& sprite_data);
  void move(float deltaTime) override;
  void draw(sf::RenderWindow& window) override;
  void contact(b2Fixture* B) override;
  void endContact(b2Fixture* B) override;
  ~CharacterSouthPark();

  b2MotorJoint* m_b2_joint;
  b2PrismaticJoint* m_b2_joint_prism;
};

class CharacterAlinasBoys : public BaseCharacter {
 public:
  CharacterAlinasBoys(b2World& world, const CharacterSpriteInfo& sprite_data);
  void move(float deltaTime) override;
  void draw(sf::RenderWindow& window) override;
  void contact(b2Fixture* B) override;
  void endContact(b2Fixture* B) override;
  ~CharacterAlinasBoys();
};

class Kolobashka : public CharacterAlinasBoys {
 public:
  Kolobashka(b2World& world, const CharacterSpriteInfo& sprite_data)
      : CharacterAlinasBoys(world, sprite_data) {}
  void move(float deltaTime) override { CharacterAlinasBoys::move(deltaTime); }
  void draw(sf::RenderWindow& window) override {
    static int rad;
    rad += 1;
    m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));
    m_sprite.setRotation(rad);
    window.draw(m_sprite);
  }
  void contact(b2Fixture* B) override {
    LOG() << "I'am AlinasBoys Kolobashka and I've begun the colliding with.. hz"
          << std::endl;
  }
  void endContact(b2Fixture* B) override {
    LOG() << "I'am AlinasBoys Kolobashka and I've dune the colliding with.. hz"
          << std::endl;
  }
  ~Kolobashka() {}
};

class MyContactListener : public b2ContactListener {
 public:
  void BeginContact(b2Contact* contact) override;

  void EndContact(b2Contact* contact) override;

  void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

  void PostSolve(b2Contact* contact, const b2ContactImpulse* Impulse) override;
};
}

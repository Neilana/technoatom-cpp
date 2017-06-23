#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
//#include "Weapons.h"
#include "../../Logger/Logger.h"
#include "Base.h"
#include "Box2D/Box2D.h"
#include "constants.h"

#define DEBUG_ON
#if defined(DEBUG_ON)
#define LOG() std::cout
#else
#define LOG() LOGGER("level")
#endif

namespace IlluminatiConfirmed {
namespace experimental {

class Weapon;

struct CharacterSpriteInfo {
  int width;
  int height;
  int size;
  int count_of_frames;
  int x_position;
  int y_position;
};

class BaseCharacter : public BaseInterface {
 public:
  enum TypeBaseCharacter { CHARACTER_SOUTH_PARK, ALINAS_BOYS };

  //передавать лямбду, которая будет дергаться, когда персу необходимо будет
  //стрелять
  BaseCharacter(b2World *world, const sf::Texture *texture,
                const CharacterSpriteInfo &sprite_data);

  virtual void draw(sf::RenderWindow &window) override;
  virtual void move(b2Vec2 velocity, float deltaTime) override;
  virtual void contact(b2Fixture *B) override;
  virtual void endContact(b2Fixture *B) override;

  void setWeapon(Weapon *weapon);
  void moveWeapon(const sf::Vector2f &pos, float rot);

  virtual void attack();

  virtual ~BaseCharacter();

  virtual void updatePhysics(float deltaTime);

 protected:
  int m_frames;
  Direction m_direction;
  //  std::vector<sf::Rect<int>> front_rects;
  //  std::vector<sf::Rect<int>> back_rects;
  //  std::vector<sf::Rect<int>> left_rects;
  //  std::vector<sf::Rect<int>> right_rects;
  std::map<Direction, std::vector<sf::Rect<int>>>
      m_directionRects;  // ыыыыыыы....

  b2Body *m_b2_body;
  b2Fixture *m_b2_body_fixture;

  b2Body *m_b2_weapon;
  b2Fixture *m_2b_weapon_fixture;

  sf::Sprite m_sprite;

  TypeBaseCharacter m_type_character;

 private:
  Weapon *m_weapon;
  float m_height;
};

class CharacterSouthPark : public BaseCharacter {
 public:
  CharacterSouthPark(b2World *world, const sf::Texture *texture,
                     const CharacterSpriteInfo &sprite_data);
  void move(b2Vec2 velocity, float deltaTime) override;
  void draw(sf::RenderWindow &window) override;
  void contact(b2Fixture *B) override;
  void endContact(b2Fixture *B) override;
  ~CharacterSouthPark();

  b2MotorJoint *m_b2_joint;
  b2PrismaticJoint *m_b2_joint_prism;

  void updatePhysics(float deltaTime);
};

class CharacterAlinasBoys : public BaseCharacter {
 public:
  CharacterAlinasBoys(b2World *world, const sf::Texture *texture,
                      const CharacterSpriteInfo &sprite_data);

  void move(b2Vec2 velocity, float deltaTime) override;
  void draw(sf::RenderWindow &window) override;
  void contact(b2Fixture *B) override;
  void endContact(b2Fixture *B) override;
  ~CharacterAlinasBoys();
};
}
}

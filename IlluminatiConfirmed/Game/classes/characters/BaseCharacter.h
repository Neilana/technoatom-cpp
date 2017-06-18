#pragma once
#include "../../Logger/Logger.h"
#include "Box2D/Box2D.h"
#include "Bullet.h"
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

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
  BaseCharacter(Type type, b2World &world,
                const CharacterSpriteInfo &sprite_data,
                const std::string &bullets);
  Type getType() const;

  virtual void draw(sf::RenderWindow &window) = 0;
  virtual void move(b2Vec2 velocity, float deltaTime);
  virtual void contact(b2Fixture *B) = 0;
  virtual void endContact(b2Fixture *B) = 0;
  virtual ~BaseCharacter() {}

  std::shared_ptr<Bullet> attack(b2World &world);

  Type m_type;
  int m_frames;
  std::string m_spriteBullets;
  Direction m_direction;
  //  std::vector<sf::Rect<int>> front_rects;
  //  std::vector<sf::Rect<int>> back_rects;
  //  std::vector<sf::Rect<int>> left_rects;
  //  std::vector<sf::Rect<int>> right_rects;
  std::map<Direction, std::vector<sf::Rect<int>>>
      m_directionRects; // ыыыыыыы....
  b2Body *m_b2_base;
  b2Fixture *m_b2_base_fixture;
  b2Body *m_b2_body;
  b2Fixture *m_b2_body_fixture;

  sf::Texture texture;
  sf::Sprite m_sprite;

  std::string m_bulletsFile;

  virtual void updatePhysics(float deltaTime) {
    //    m_body->SetTransform(
    //        m_body->GetPosition(),
    //        RadBetweenVectors(m_body->GetPosition(),
    // SfVector2toB2Vec2(sf::Mouse::getPosition(window))));

    // sprite.setPosition(FromBox2DtoPixel(m_body->GetPosition().x),
    //                   FromBox2DtoPixel(m_body->GetPosition().y));
    m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));
    // sprite.setRotation(m_body->GetAngle() * 180 / 3.14159265);
  }
};
}

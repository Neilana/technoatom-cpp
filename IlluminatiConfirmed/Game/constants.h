#pragma once
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "math.h"

#include <iostream>

#define UNUSE(var) \
  do {             \
    (void)var;     \
  } while (0);

#define DEBUG_ON
#if defined(DEBUG_ON)
#define LOG() std::cout
#else
#define LOG() LOGGER("level")
#endif

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;

const float SCALE = 32.0;

enum class Direction { Up, Down, Left, Right, Nothing };
enum class ScreenName { MainMenu, ChoseCharacters, ChoseMap, Game, Load, Save };

const std::string MAP_DIRECTORY = "../Game/resources/maps/";
const std::string DEFAULT_MAP_FILE = "map1.tmx";
const int MAP_SPRITE_SIZE = 150;

const std::string LAYER_GROUND = "Layer_Ground";
const std::string LAYER_BUILDINGS = "Layer_Buildings";
const std::string OBJECT_SPRITE = "Buildings_sprite";
const std::string OBJECT_BODY = "Buildings_body";

const std::string CHARACTERS_SPRITES_DIRECTORY =
    "../Game/resources/sprites/characters/";
const std::string BULLETS_SPRITES_DIRECTORY =
    "../Game/resources/sprites/bullets/";

const std::string FONT_FILE =
    "../Game/resources/fonts/Franchise-Bold-hinted.ttf";
const std::string MENU_BACKGROUND_FILE =
    "../Game/resources/sprites/backgrounds/menu3_1.png";

const int DEFAULT_SPRITE_SIZE_X = 64;
const int DEFAULT_SPRITE_SIZE_Y = 64;
const int TEAM_MEMBERS_COUNT = 2;

template <typename T>
b2Vec2 SfVector2toB2Vec2(const sf::Vector2<T> &vector) {
  return b2Vec2(vector.x / SCALE, vector.y / SCALE);
}

template <typename T>
sf::Vector2<T> B2Vec2toSfVector2(const b2Vec2 &vector) {
  return sf::Vector2<T>(vector.x * SCALE, vector.y * SCALE);
}

template <typename T>
sf::Vector2<T> operator/(const sf::Vector2<T> &lhs, const sf::Vector2<T> &rhs) {
  return sf::Vector2<T>(lhs.x / rhs.x, lhs.y / rhs.y);
}

template <typename T>
sf::Vector2<T> operator*(const sf::Vector2<T> &lhs, const sf::Vector2<T> &rhs) {
  return sf::Vector2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
}

template <typename T>
sf::Vector2<T> operator+(const sf::Vector2<T> &lhs, const sf::Vector2<T> &rhs) {
  return sf::Vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename V1, typename V2>
float RadBetweenVectors(const V1 &v1, const V2 &v2) {
  return static_cast<float>(atan2(v2.y - v1.y, v2.x - v1.x));
}

// template <typename LHS, typename RHS>
// float RadBetweenVectors(const LHS &lhs, const RHS &rhs) {
//  auto dot = lhs.x * rhs.x + lhs.y * lhs.y;
//  auto mod_lhs = sqrtf(lhs.x * lhs.x + lhs.y * lhs.y);
//  auto mod_rhs = sqrtf(rhs.x * rhs.x + rhs.y * rhs.y);
//  return dot / (mod_lhs * mod_rhs);
//}

inline float SfPointtoB2Point(float point) { return point / SCALE; }

inline b2Vec2 getShapePosition(const b2Shape *shape) {
  if (shape->m_type == b2Shape::e_circle) {
    return static_cast<const b2CircleShape *>(shape)->m_p;
  } else if (shape->m_type == b2Shape::e_polygon) {
    return static_cast<const b2PolygonShape *>(shape)->m_centroid;
  }
  return b2Vec2_zero;
}

inline b2Vec2 getFixtureWorldPosition(const b2Fixture *fixture) {
  return fixture->GetBody()->GetPosition() +
         getShapePosition(fixture->GetShape());
}

inline Direction findDirectonByVelocity(b2Vec2 &vector) {
  // Direction dir = Direction::Up;
  if (vector.y > 0.0) return Direction::Down;
  if (vector.y < 0.0) return Direction::Up;

  if (vector.x > 0.0) return Direction::Right;
  if (vector.x < 0.0) return Direction::Left;
  return Direction::Down;
}

template <typename type>
std::ostream &operator<<(std::ostream &stream, const sf::Vector2<type> &vec) {
  stream << vec.x << " : " << vec.y;
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const b2Vec2 &vec);

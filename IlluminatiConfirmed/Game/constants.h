#pragma once
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "math.h"

#include <string>

#define UNUSE(var)                                                             \
  do {                                                                         \
    (void)var;                                                                 \
  } while (0);

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;

const float SCALE = 32.0;

enum class Direction { Up, Down, Left, Right, Nothing };
enum class ScreenName { MainMenu, ChoseCharacters, Game, Load, Save };

const std::string MAP_FILE_1 = "../Game/resources/maps/map25x25_1.tmx";
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

template <typename T> b2Vec2 SfVector2toB2Vec2(const sf::Vector2<T> &vector) {
  return b2Vec2(vector.x / SCALE, vector.y / SCALE);
}

template <typename T> sf::Vector2<T> B2Vec2toSfVector2(const b2Vec2 &vector) {
  return sf::Vector2<T>(vector.x * SCALE, vector.y * SCALE);
}

template <typename V1, typename V2>
float RadBetweenVectors(const V1 &v1, const V2 &v2) {
  return static_cast<float>(atan2(v2.y - v1.y, v2.x - v1.x));
}

inline float SfPointtoB2Point(float point) { return point / SCALE; }

inline Direction findDirectonByVelocity(b2Vec2 &vector) {
  // Direction dir = Direction::Up;
  if (vector.y > 0.0)
    return Direction::Down;
  if (vector.y < 0.0)
    return Direction::Up;

  if (vector.x > 0.0)
    return Direction::Right;
  if (vector.x < 0.0)
    return Direction::Left;
}

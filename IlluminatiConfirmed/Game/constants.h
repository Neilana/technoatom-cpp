#pragma once
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "math.h"

#include <string>

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;

const float SCALE = 32.0;

enum class Direction { Up, Down, Left, Right };
enum class ScreenName { MainMenu, ChoseCharacters, Game };
// enum class MenuOptions { NewGame, Continue, Save, Load, Exit }

const std::string MAP_FILE_1 = "../Game/maps/map25x25_1.tmx";

template <typename T>
b2Vec2 SfVector2toB2Vec2(const sf::Vector2<T> &vector) {
  return b2Vec2(vector.x / SCALE, vector.y / SCALE);
}

template <typename T>
sf::Vector2<T> B2Vec2toSfVector2(const b2Vec2 &vector) {
  return sf::Vector2<T>(vector.x * SCALE, vector.y * SCALE);
}

template <typename V1, typename V2>
float RadBetweenVectors(const V1 &v1, const V2 &v2) {
  return static_cast<float>(atan2(v2.y - v1.y, v2.x - v1.x));
}

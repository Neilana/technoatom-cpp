#pragma once
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;

const int SCALE = 32;

template <typename T>
b2Vec2 SfVector2toB2Vec2(sf::Vector2<T> vector) {
  return b2Vec2(vector.x / SCALE, vector.y / SCALE);
}

template <typename T>
sf::Vector2<T> B2Vec2toSfVector2(b2Vec2 vector) {
  return sf::Vector2<T>(vector.x * SCALE, vector.y * SCALE);
}

enum class Direction { Up, Down, Left, Right };

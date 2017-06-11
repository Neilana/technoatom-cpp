#pragma once

#include <vector>
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

#include "constants.h"

namespace IlluminatiConfirmed {

class Bullet {
 private:
  // Character *m_owner;

  sf::Texture m_texture;
  sf::Sprite m_sprite;

  float m_speed;
  float m_damage;

  b2Body *m_body;

 public:
  Bullet(b2World *world, sf::Vector2f const pos, Direction direction,
         float damage, const std::string &spriteFile);
  ~Bullet() { m_body->GetWorld()->DestroyBody(m_body); }
  void draw(sf::RenderWindow &window) { window.draw(m_sprite); }
  void updatePhysics(const sf::RenderWindow &window) {
    m_sprite.setPosition(B2Vec2toSfVector2<float>(m_body->GetPosition()));
  }
  bool hasStopped() { return m_body->GetLinearVelocity().Length() == 0; }
};
}

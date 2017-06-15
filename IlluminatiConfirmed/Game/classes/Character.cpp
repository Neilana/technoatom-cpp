#include "Character.h"
#include "Bullet.h"

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using IlluminatiConfirmed::Character;
using IlluminatiConfirmed::Bullet;

void Character::move(Direction key, float deltaTime) {
  currentFrame += 0.005 * deltaTime;
  if (currentFrame > m_frames) currentFrame -= m_frames;
  m_direction = key;
  switch (key) {
    case Direction::Right: {  //в процессе выбора физики движения)
      m_body->SetLinearVelocity(b2Vec2(10.0f, 0.0f));
      sprite.setTextureRect(rightRects[int(currentFrame)]);
      break;
    }
    case Direction::Left: {  //в процессе выбора физики движения)
      m_body->SetLinearVelocity(b2Vec2(-10.0f, 0.0f));
      sprite.setTextureRect(leftRects[int(currentFrame)]);
      break;
    }
    case Direction::Up: {  //в процессе выбора физики движения)
      m_body->SetLinearVelocity(b2Vec2(0.0f, -10.0f));
      sprite.setTextureRect(backRects[int(currentFrame)]);
      break;
    }

    case Direction::Down: {  //в процессе выбора физики движения)
      m_body->SetLinearVelocity(b2Vec2(0.0f, 10.0f));
      sprite.setTextureRect(frontRects[int(currentFrame)]);
      break;
    }
  }
}

std::shared_ptr<Bullet> Character::attack(b2World &world) {
  float damage = 10.0;
  std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(
      world, sprite.getPosition(), m_direction, damage, m_spriteBullets);
  return bullet;
}

// void Character::draw(sf::RenderWindow& window) { window.draw(sprite); }

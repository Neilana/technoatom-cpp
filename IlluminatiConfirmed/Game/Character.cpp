#include "Character.h"
#include "Bullet.h"

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

// Character::Character(const std::string& file, int f, int width, int height) {
//  x = 0;
//  y = 0;
//  vx = 0;
//  vy = 0;
//  speed = 0.1;
//  currentFrame = 0;
//  frames = f;

//  texture.loadFromFile(file);

//  tileWidth = width;
//  tileHeight = height;

//  sprite.setTexture(texture);
//  sprite.setTextureRect(sf::Rect<int>(0, 0, width, height));
//  sprite.setPosition(x, y);

//  for (int column = 0; column < frames; column++) {
//    int row = 0;
//    frontRects.push_back(Rect<int>(column * tileWidth, tileHeight * row++,
//                                   tileWidth, tileHeight));
//    backRects.push_back(Rect<int>(column * tileWidth, tileHeight * row++,
//                                  tileWidth, tileHeight));
//    rightRects.push_back(Rect<int>(column * tileWidth, tileHeight * row++,
//                                   tileWidth, tileHeight));
//    leftRects.push_back(Rect<int>(column * tileWidth, tileHeight * row++,
//                                  tileWidth, tileHeight));
//  }
//}

// void Character::move(Direction dir, float deltaTime) {
//  currentFrame += 0.005 * deltaTime;
//  if (currentFrame > frames) currentFrame -= frames;
//  //   float oldSpeed = speed;

//  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
//    //     oldSpeed = speed;
//    // speed *= 1.5;
//    deltaTime *= 1.6;
//  }

//  switch (dir) {
//    case Direction::Up: {
//      vx = 0;
//      vy = -speed;
//      sprite.setTextureRect(backRects[int(currentFrame)]);
//    } break;

//    case Direction::Down: {
//      vx = 0;
//      vy = speed;
//      sprite.setTextureRect(frontRects[int(currentFrame)]);
//    } break;

//    case Direction::Right: {
//      vx = speed;
//      vy = 0;
//      sprite.setTextureRect(rightRects[int(currentFrame)]);
//    } break;

//    case Direction::Left: {
//      vx = -speed;
//      vy = 0;
//      sprite.setTextureRect(leftRects[int(currentFrame)]);
//    } break;
//  }

//  if ((x + vx * deltaTime > 0) &&
//      (x + vx * deltaTime < WINDOW_WIDTH - tileWidth))
//    x += vx * deltaTime;
//  if ((y + vy * deltaTime > 0) &&
//      (y + vy * deltaTime < WINDOW_HEIGHT - tileHeight))
//    y += vy * deltaTime;

//  //    speed = oldSpeed;
//  sprite.setPosition(x, y);
//}

// void move(Direction key) {
// BEGIN
//    switch (key) {
//    case Direction::Right: { //в процессе выбора физики движения)
//      //        float force = m_body->GetMass() *
//      //                      (m_max_speed - m_body->GetLinearVelocity().x) /
//      //                      (1 / 60.0);  // f = mv/t
//      //        m_body->ApplyForce(b2Vec2(force, 0), m_body->GetWorldCenter(),
//      //        true);
//      b2Vec2 f = m_body->GetWorldVector(b2Vec2(m_max_force, 0.f));
//      b2Vec2 p = m_body->GetWorldPoint(b2Vec2(2.f, 0.f));
//      m_body->ApplyForce(f, p, true);
//      m_body->ApplyForce(f, p, true);

//      // m_body->ApplyTorque(-5.f, true);
//      break;
//    }
//    case Direction::Left: {
//      //        float force = m_body->GetMass() *
//      //                      (m_max_speed - m_body->GetLinearVelocity().x) /
//      //                      (1 / 60.0);  // f = mv/t
//      //        m_body->ApplyForce(b2Vec2(-force, 0),
//      //        m_body->GetWorldCenter(), true);
//      b2Vec2 f = m_body->GetWorldVector(b2Vec2(-m_max_force, 0.f));
//      b2Vec2 p = m_body->GetWorldPoint(b2Vec2(2.f, 0.f));
//      m_body->ApplyForce(f, p, true);
//      // m_body->ApplyTorque(+5.f, true);
//      break;
//    }
//    case Direction::Up: {
//      //        float force = m_body->GetMass() *
//      //                      (m_max_speed - m_body->GetLinearVelocity().x) /
//      //                      (1 / 60.0);  // f = mv/t
//      //        m_body->ApplyForce(b2Vec2(0, force), m_body->GetWorldCenter(),
//      //        true);
//      b2Vec2 f = m_body->GetWorldVector(b2Vec2(0.0f, -m_max_force));
//      b2Vec2 p = m_body->GetWorldPoint(b2Vec2(0.0f, 2.f));
//      m_body->ApplyForce(f, p, true);
//      break;
//    }
//    case Direction::Down: {
//      //        float force = m_body->GetMass() *
//      //                      (m_max_speed - m_body->GetLinearVelocity().x) /
//      //                      (1 / 60.0);  // f = mv/t
//      //        m_body->ApplyForce(b2Vec2(0, -force),
//      //        m_body->GetWorldCenter(), true);
//      b2Vec2 f = m_body->GetWorldVector(b2Vec2(0.0f, m_max_force));
//      b2Vec2 p = m_body->GetWorldPoint(b2Vec2(0.0f, 2.f));
//      m_body->ApplyForce(f, p, true);
//      break;
//    }
//    }

// END

void Character::move(Direction key, float deltaTime) {
  currentFrame += 0.005 * deltaTime;
  if (currentFrame > m_frames)
    currentFrame -= m_frames;
  m_direction = key;
  switch (key) {
  case Direction::Right: { //в процессе выбора физики движения)
    m_body->SetLinearVelocity(b2Vec2(10.0f, 0.0f));
    sprite.setTextureRect(rightRects[int(currentFrame)]);
    break;
  }
  case Direction::Left: { //в процессе выбора физики движения)
    m_body->SetLinearVelocity(b2Vec2(-10.0f, 0.0f));
    sprite.setTextureRect(leftRects[int(currentFrame)]);
    break;
  }
  case Direction::Up: { //в процессе выбора физики движения)
    m_body->SetLinearVelocity(b2Vec2(0.0f, -10.0f));
    sprite.setTextureRect(backRects[int(currentFrame)]);
    break;
  }

  case Direction::Down: { //в процессе выбора физики движения)
    m_body->SetLinearVelocity(b2Vec2(0.0f, 10.0f));
    sprite.setTextureRect(frontRects[int(currentFrame)]);
    break;
  }
  }
}

std::shared_ptr<Bullet> Character::attack(b2World *world) {
  float damage = 10.0;
  std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(
      world, sprite.getPosition(), m_direction, damage, m_spriteBullets);
  return bullet;
}

// void Character::draw(sf::RenderWindow& window) { window.draw(sprite); }

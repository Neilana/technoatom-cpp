#pragma once

#include <vector>
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "constants.h"

class Character {
 private:
  float currentFrame;
  int m_frames;

  sf::Texture texture;
  sf::Sprite sprite;

  std::vector<sf::Rect<int>> frontRects;
  std::vector<sf::Rect<int>> backRects;
  std::vector<sf::Rect<int>> leftRects;
  std::vector<sf::Rect<int>> rightRects;

  float m_max_speed = 10.f;
  float m_max_force = 13.f;  //нет времени думать какая разница :D

 public:
  int tileWidth, tileHeight;
  b2Body* m_body;
  // Character();
  Character(const std::string& file, b2World* world, int frames, int width,
            int height) {
    b2BodyDef body_def;

    body_def.type = b2_dynamicBody;
    body_def.fixedRotation = true;  //пока что

    body_def.position.Set(0, 5.0f);
    m_body = world->CreateBody(&body_def);

    b2CircleShape circle_shape;
    circle_shape.m_radius = 2.f;
    b2FixtureDef fixture;
    fixture.shape = &circle_shape;
    fixture.density = 0.1f;
    fixture.friction = 0.3f;
    fixture.restitution = 0.1f;

    m_body->CreateFixture(&fixture);
    m_body->SetLinearDamping(0.3f);
    m_body->SetAngularDamping(0.3f);

    currentFrame = 0;
    m_frames = frames;

    texture.loadFromFile(file);

    tileWidth = width;
    tileHeight = height;

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::Rect<int>(0, 0, width, height));
    sprite.setPosition(B2Vec2toSfVector2<float>(m_body->GetPosition()));
    sprite.setOrigin(16.f, 16.f);
    sprite.setScale(1.5f, 1.5f);

    for (int column = 0; column < m_frames; column++) {
      int row = 0;
      frontRects.push_back(sf::Rect<int>(column * tileWidth, tileHeight * row++,
                                         tileWidth, tileHeight));
      backRects.push_back(sf::Rect<int>(column * tileWidth, tileHeight * row++,
                                        tileWidth, tileHeight));
      rightRects.push_back(sf::Rect<int>(column * tileWidth, tileHeight * row++,
                                         tileWidth, tileHeight));
      leftRects.push_back(sf::Rect<int>(column * tileWidth, tileHeight * row++,
                                        tileWidth, tileHeight));
    }
  }

  void move(Direction key) {
    switch (key) {
      case Direction::Right: {  //в процессе выбора физики движения)
        //        float force = m_body->GetMass() *
        //                      (m_max_speed - m_body->GetLinearVelocity().x) /
        //                      (1 / 60.0);  // f = mv/t
        //        m_body->ApplyForce(b2Vec2(force, 0), m_body->GetWorldCenter(),
        //        true);
        b2Vec2 f = m_body->GetWorldVector(b2Vec2(m_max_force, 0.f));
        b2Vec2 p = m_body->GetWorldPoint(b2Vec2(2.f, 0.f));
        m_body->ApplyForce(f, p, true);
        m_body->ApplyForce(f, p, true);
        // m_body->ApplyTorque(-5.f, true);
        break;
      }
      case Direction::Left: {
        //        float force = m_body->GetMass() *
        //                      (m_max_speed - m_body->GetLinearVelocity().x) /
        //                      (1 / 60.0);  // f = mv/t
        //        m_body->ApplyForce(b2Vec2(-force, 0),
        //        m_body->GetWorldCenter(), true);
        b2Vec2 f = m_body->GetWorldVector(b2Vec2(-m_max_force, 0.f));
        b2Vec2 p = m_body->GetWorldPoint(b2Vec2(2.f, 0.f));
        m_body->ApplyForce(f, p, true);
        // m_body->ApplyTorque(+5.f, true);
        break;
      }
      case Direction::Up: {
        //        float force = m_body->GetMass() *
        //                      (m_max_speed - m_body->GetLinearVelocity().x) /
        //                      (1 / 60.0);  // f = mv/t
        //        m_body->ApplyForce(b2Vec2(0, force), m_body->GetWorldCenter(),
        //        true);
        b2Vec2 f = m_body->GetWorldVector(b2Vec2(0.0f, -m_max_force));
        b2Vec2 p = m_body->GetWorldPoint(b2Vec2(0.0f, 2.f));
        m_body->ApplyForce(f, p, true);
        break;
      }
      case Direction::Down: {
        //        float force = m_body->GetMass() *
        //                      (m_max_speed - m_body->GetLinearVelocity().x) /
        //                      (1 / 60.0);  // f = mv/t
        //        m_body->ApplyForce(b2Vec2(0, -force),
        //        m_body->GetWorldCenter(), true);
        b2Vec2 f = m_body->GetWorldVector(b2Vec2(0.0f, m_max_force));
        b2Vec2 p = m_body->GetWorldPoint(b2Vec2(0.0f, 2.f));
        m_body->ApplyForce(f, p, true);
        break;
      }
    }

    //        currentFrame += 0.005 * deltaTime;
    //        if (currentFrame > frames) currentFrame -= frames;
    //        //   float oldSpeed = speed;

    //        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
    //          //     oldSpeed = speed;
    //          // speed *= 1.5;
    //          deltaTime *= 1.6;

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

    //  if ((x + vx * deltaTime > 0) &&
    //      (x + vx * deltaTime < WINDOW_WIDTH - tileWidth))
    //    x += vx * deltaTime;
    //  if ((y + vy * deltaTime > 0) &&
    //      (y + vy * deltaTime < WINDOW_HEIGHT - tileHeight))
    //    y += vy * deltaTime;

    //  //    speed = oldSpeed;
    //  sprite.setPosition(x, y);
    //}
  }

  void updatePhysics(const sf::RenderWindow& window) {
    m_body->SetTransform(
        m_body->GetPosition(),
        RadBetweenVectors(m_body->GetPosition(),
                          SfVector2toB2Vec2(sf::Mouse::getPosition(window))));

    // sprite.setPosition(FromBox2DtoPixel(m_body->GetPosition().x),
    //                   FromBox2DtoPixel(m_body->GetPosition().y));
    sprite.setPosition(B2Vec2toSfVector2<float>(m_body->GetPosition()));
    sprite.setRotation(m_body->GetAngle() * 180 / 3.14159265);
  }

  void draw(sf::RenderWindow& window) {
    { window.draw(sprite); }
  }
  template <typename T>
  void setCoordinates(sf::Vector2<T> vec) {
    m_body->SetTransform(SfVector2toB2Vec2(vec), m_body->GetAngle());
    sprite.setPosition(static_cast<sf::Vector2f>(vec));
  }
};

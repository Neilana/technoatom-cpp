#pragma once

#include <vector>
#include "Box2D/Box2D.h"
#include "Bullet.h"
#include "SFML/Graphics.hpp"
#include "constants.h"

namespace IlluminatiConfirmed {

class Character {
 private:
  float currentFrame;
  int m_frames;

  sf::Texture texture;
  sf::Sprite sprite;

  std::string m_spriteBullets;

  std::vector<sf::Rect<int>> frontRects;
  std::vector<sf::Rect<int>> backRects;
  std::vector<sf::Rect<int>> leftRects;
  std::vector<sf::Rect<int>> rightRects;

  float m_max_speed = 10.f;
  float m_max_force = 13.f;  //нет времени думать какая разница :D

  Direction m_direction;

 public:
  int tileWidth, tileHeight;
  b2Body *m_body;
  // Character();
  void move(Direction key, float deltaTime);
  // void move(Direction key);
  std::shared_ptr<Bullet> attack(b2World *world);
  sf::Vector2f getSFMLPosition() { return sprite.getPosition(); }

  Character(const std::string &file, b2World *world, int frames, int width,
            int height, const std::string &bulletsFile)
      : m_frames(frames),
        m_direction(Direction::Down),
        m_spriteBullets(bulletsFile) {
    b2BodyDef body_def;

    body_def.type = b2_dynamicBody;
    body_def.fixedRotation = true;  //пока что

    body_def.position.Set(0, 0);
    m_body = world->CreateBody(&body_def);

    b2CircleShape circle_shape;
    // circle_shape.m_radius = 2.f;
    circle_shape.m_radius = (std::max(width / 2.0, height / 2.0) / SCALE);
    b2FixtureDef fixture;
    fixture.shape = &circle_shape;

    // ??? что-то из этого помгло им перестать летать
    fixture.density = 0.0;
    fixture.friction = 0.0;
    fixture.restitution = 0.0;

    m_body->CreateFixture(&fixture);
    m_body->SetLinearDamping(100.3f);
    m_body->SetAngularDamping(100.3f);

    currentFrame = 0;
    m_frames = frames;

    texture.loadFromFile(file);

    tileWidth = width;
    tileHeight = height;

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::Rect<int>(0, 0, width, height));
    sprite.setPosition(B2Vec2toSfVector2<float>(m_body->GetPosition()));
    sprite.setOrigin(width / 2.0, height / 2.0);
    // sprite.setOrigin(16.f, 16.f);
    // sprite.setScale(1.5f, 1.5f);

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

  void updatePhysics(const sf::RenderWindow &window) {
    //    m_body->SetTransform(
    //        m_body->GetPosition(),
    //        RadBetweenVectors(m_body->GetPosition(),
    //                          SfVector2toB2Vec2(sf::Mouse::getPosition(window))));

    // sprite.setPosition(FromBox2DtoPixel(m_body->GetPosition().x),
    //                   FromBox2DtoPixel(m_body->GetPosition().y));
    sprite.setPosition(B2Vec2toSfVector2<float>(m_body->GetPosition()));
    // sprite.setRotation(m_body->GetAngle() * 180 / 3.14159265);
  }

  void draw(sf::RenderWindow &window) {
    { window.draw(sprite); }
  }
  template <typename T>
  void setCoordinates(sf::Vector2<T> vec) {
    m_body->SetTransform(SfVector2toB2Vec2(vec), m_body->GetAngle());
    sprite.setPosition(static_cast<sf::Vector2f>(vec));
  }
};
}

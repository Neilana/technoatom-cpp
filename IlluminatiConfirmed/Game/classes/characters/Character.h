#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
//#include "Weapons.h"
#include "../../Logger/Logger.h"
#include "Base.h"
#include "Box2D/Box2D.h"
#include "constants.h"

#define DEBUG_ON
#if defined(DEBUG_ON)
#define LOG() std::cout
#else
#define LOG() LOGGER("level")
#endif

namespace IlluminatiConfirmed {
namespace experimental {

class Weapon;

struct CharacterSpriteInfo {
  int width;
  int height;
  int size;
  int count_of_frames;
  int x_position;
  int y_position;
};

class BaseCharacter : public BaseInterface {
 public:
  enum TypeBaseCharacter { CHARACTER_SOUTH_PARK, ALINAS_BOYS };

  //передавать лямбду, которая будет дергаться, когда персу необходимо будет
  //стрелять
  BaseCharacter(b2World *world, const sf::Texture *texture,
                const CharacterSpriteInfo &sprite_data)
      : BaseInterface(BaseInterface::CHARACTER), m_weapon(nullptr) {
    LOG() << "Create Character \n";
    {
      b2BodyDef bd;
      bd.fixedRotation = true;
      bd.type = b2_dynamicBody;
      bd.position.Set(SfPointtoB2Point(sprite_data.x_position),
                      SfPointtoB2Point(sprite_data.y_position));
      bd.linearDamping = 1000.f;
      m_b2_base = world->CreateBody(&bd);

      b2PolygonShape polygon;
      polygon.SetAsBox(0.5f, 0.1f);

      b2FixtureDef fixture;
      fixture.friction = 1.f;
      fixture.density = 50.f;
      fixture.restitution = 0;
      fixture.isSensor = false;

      fixture.shape = &polygon;
      m_b2_base_fixture = m_b2_base->CreateFixture(&fixture);
      m_b2_base_fixture->SetUserData(this);
    }
    {
      b2BodyDef bd;
      bd.type = b2_dynamicBody;
      bd.position.Set(SfPointtoB2Point(sprite_data.x_position),
                      SfPointtoB2Point(sprite_data.y_position));
      bd.linearDamping = 0.f;
      bd.fixedRotation = true;
      m_b2_body = world->CreateBody(&bd);

      b2PolygonShape polygon;
      // polygon.SetAsBox(.5f, 1.f, {0.f, -1.f}, 0);

      polygon.SetAsBox(SfPointtoB2Point(sprite_data.size / 2.0),
                       SfPointtoB2Point(sprite_data.size / 2.0),
                       {0, -SfPointtoB2Point(sprite_data.size / 2.0)}, 0);

      b2FixtureDef fixture;
      fixture.friction = 0.f;
      fixture.density = 0.005f;
      fixture.isSensor = true;

      fixture.shape = &polygon;

      m_b2_body_fixture = m_b2_body->CreateFixture(&fixture);
      m_b2_body_fixture->SetUserData(this);
    }
    //  front_rects.reserve(sprite_data.count_of_frames);
    //  back_rects.reserve(sprite_data.count_of_frames);
    //  left_rects.reserve(sprite_data.count_of_frames);
    //  right_rects.reserve(sprite_data.count_of_frames);

    m_frames = sprite_data.count_of_frames;
    m_direction = Direction::Down;

    m_sprite.setTexture(*texture);
    m_sprite.scale(float(sprite_data.size / sprite_data.width),
                   float(sprite_data.size / sprite_data.height));
    m_sprite.setTextureRect({0, 0, sprite_data.height, sprite_data.width});
    m_sprite.setOrigin(m_sprite.getTextureRect().width / 2.f,
                       m_sprite.getTextureRect().height);

    std::vector<sf::Rect<int>> front_rects;
    std::vector<sf::Rect<int>> back_rects;
    std::vector<sf::Rect<int>> left_rects;
    std::vector<sf::Rect<int>> right_rects;

    for (int column = 0; column < sprite_data.count_of_frames; column++) {
      int row = 0;
      front_rects.push_back({column * sprite_data.width,
                             sprite_data.height * row++, sprite_data.width,
                             sprite_data.height});
      back_rects.push_back({column * sprite_data.width,
                            sprite_data.height * row++, sprite_data.width,
                            sprite_data.height});
      right_rects.push_back({column * sprite_data.width,
                             sprite_data.height * row++, sprite_data.width,
                             sprite_data.height});
      left_rects.push_back({column * sprite_data.width,
                            sprite_data.height * row++, sprite_data.width,
                            sprite_data.height});
    }

    m_directionRects[Direction::Down] = front_rects;
    m_directionRects[Direction::Up] = back_rects;
    m_directionRects[Direction::Right] = right_rects;
    m_directionRects[Direction::Left] = left_rects;

    assert(!(front_rects.size() == back_rects.size() == right_rects.size() ==
             left_rects.size()));
  }

  virtual void draw(sf::RenderWindow &window) override;
  virtual void move(b2Vec2 velocity, float deltaTime) override {
    static float currentFrame;
    currentFrame += 0.005 * deltaTime;

    if (int(currentFrame) > m_frames - 1) currentFrame = 0;

    m_direction = findDirectonByVelocity(velocity);
    m_sprite.setTextureRect(
        m_directionRects[m_direction].at((int)currentFrame));

    velocity.Normalize();
    velocity *= 100.f;
    m_b2_base->SetLinearVelocity(velocity);

    //для движения по диагонали перс должен поворачиваться
  }
  virtual void contact(b2Fixture *B) override {}
  virtual void endContact(b2Fixture *B) override {}

  void setWeapon(Weapon *weapon);

  virtual void attack();

  virtual ~BaseCharacter() {
    if (m_weapon) delete m_weapon;
    m_b2_body->GetWorld()->DestroyBody(m_b2_body);
  }

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

 protected:
  int m_frames;
  Direction m_direction;
  //  std::vector<sf::Rect<int>> front_rects;
  //  std::vector<sf::Rect<int>> back_rects;
  //  std::vector<sf::Rect<int>> left_rects;
  //  std::vector<sf::Rect<int>> right_rects;
  std::map<Direction, std::vector<sf::Rect<int>>>
      m_directionRects;  // ыыыыыыы....

  b2Body *m_b2_body;
  b2Fixture *m_b2_body_fixture;

  b2Body *m_b2_weapon;
  b2Fixture *m_2b_weapon_fixture;

  sf::Sprite m_sprite;

  TypeBaseCharacter m_type_character;

 private:
  Weapon *m_weapon;
};

class CharacterSouthPark : public BaseCharacter {
 public:
  CharacterSouthPark(b2World *world, const sf::Texture *texture,
                     const CharacterSpriteInfo &sprite_data);
  void move(b2Vec2 velocity, float deltaTime) override;
  void draw(sf::RenderWindow &window) override;
  void contact(b2Fixture *B) override;
  void endContact(b2Fixture *B) override;
  ~CharacterSouthPark();

  b2MotorJoint *m_b2_joint;
  b2PrismaticJoint *m_b2_joint_prism;

  void updatePhysics(float deltaTime);
};

class CharacterAlinasBoys : public BaseCharacter {
 public:
  CharacterAlinasBoys(b2World *world, const sf::Texture *texture,
                      const CharacterSpriteInfo &sprite_data);

  void move(b2Vec2 velocity, float deltaTime) override;
  void draw(sf::RenderWindow &window) override;
  void contact(b2Fixture *B) override;
  void endContact(b2Fixture *B) override;
  ~CharacterAlinasBoys();
};
}
}

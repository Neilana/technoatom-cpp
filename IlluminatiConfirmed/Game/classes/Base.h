#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Box2D/Box2D.h"

#include "Level.h"
#include "constants.h"

namespace IlluminatiConfirmed {
namespace experimental {
// enum class Type { CHARACTER_SOUTH_PARK, ALINAS_BOYS, BUILDING };

class BaseInterface {
 public:
  enum TypeBase { MAPS_STUFF, CHARACTER, BULLET };

  BaseInterface(TypeBase type)
      : m_b2_base(nullptr),
        m_b2_base_fixture(nullptr),
        m_type_base(type),
        is_dead(false) {
    LOG() << "Create base " << int(m_type_base) << std::endl;
  }
  virtual void draw(sf::RenderWindow &window) = 0;
  virtual void move(b2Vec2 velocity, float deltaTime) = 0;
  virtual void contact(b2Fixture *B) = 0;
  virtual void endContact(b2Fixture *B) = 0;
  virtual bool isDead() { return is_dead; }

  float getY() {
    return getFixtureWorldPosition(m_b2_base->GetFixtureList()).y;
  }

  virtual ~BaseInterface() {
    LOG() << "Destroy base " << int(m_type_base) << std::endl;
  }

 protected:
  b2Body *m_b2_base;
  b2Fixture *m_b2_base_fixture;
  bool is_dead;
  TypeBase m_type_base;
};

class BaseMapsStuff : public BaseInterface {
 public:
  enum TypeMap { BUILDING };  //мб какие то коины или жизни или оружее
  BaseMapsStuff(TypeMap type) : BaseInterface(MAPS_STUFF), m_type_map(type) {
    LOG() << "Create BaseMapsStuff " << int(m_type_base) << std::endl;
  }
  virtual void move(b2Vec2 velocity, float deltaTime) override = 0;
  virtual void draw(sf::RenderWindow &window) override = 0;
  virtual void contact(b2Fixture *B) override = 0;
  virtual void endContact(b2Fixture *B) override = 0;
  virtual ~BaseMapsStuff() {
    LOG() << "Destroy BaseMapsStuff " << int(m_type_map) << std::endl;
  }
  TypeMap m_type_map;
};

class Building : public BaseMapsStuff {
 public:
  Building(b2World *world, const sf::Texture *texture, Big_Object &&big_obj)
      : BaseMapsStuff(BUILDING) {
    {
      b2BodyDef bd;
      bd.type = b2_staticBody;
      bd.position.Set(SfPointtoB2Point(big_obj.body.m_rect.left +
                                       big_obj.body.m_rect.width / 2),
                      SfPointtoB2Point(big_obj.body.m_rect.top +
                                       big_obj.body.m_rect.height / 2));
      m_b2_base = world->CreateBody(&bd);

      b2PolygonShape polygon;
      polygon.SetAsBox(SfPointtoB2Point(big_obj.body.m_rect.width / 2),
                       SfPointtoB2Point(big_obj.body.m_rect.height / 2));

      b2FixtureDef fixture;
      fixture.friction = 1.f;
      fixture.density = 50.f;
      fixture.restitution = 0;
      fixture.isSensor = false;
      fixture.shape = &polygon;

      m_b2_base_fixture = m_b2_base->CreateFixture(&fixture);
      m_b2_base_fixture->SetUserData(this);
      LOG() << "Create building " << std::endl;
    }

    for (auto &&it : big_obj.rects_for_draw_sprites) {
      sf::Sprite little_sprite = sf::Sprite(*texture, it.first);
      little_sprite.setPosition(it.second.x, it.second.y);

      m_vec_sprite.push_back(std::move(little_sprite));
    }
  }
  virtual void move(b2Vec2 velocity, float deltaTime) override {
    // nothing
  }
  virtual void draw(sf::RenderWindow &window) override {
    for (auto &&it : m_vec_sprite) window.draw(it);
  }
  virtual void contact(b2Fixture *B) override {
    //к примеру добавить дому хпшку и, когда она закончится, включать анимацию
    //взрыва перед смертью
  }
  virtual void endContact(b2Fixture *B) override {}

  ~Building() {
    LOG() << "Destroy building " << std::endl;
      /*m_b2_base->GetWorld()->DestroyBody(m_b2_base);*/ }

     private:
      std::vector<sf::Sprite> m_vec_sprite;
};

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
      : BaseInterface(BaseInterface::CHARACTER) {
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
    m_sprite.scale((float)sprite_data.size / sprite_data.width,
                   (float)sprite_data.size / sprite_data.height);
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

  virtual void draw(sf::RenderWindow &window) override {
    window.draw(m_sprite);
  }
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
  virtual ~BaseCharacter() {
    m_b2_base->GetWorld()->DestroyBody(m_b2_base);
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

  sf::Sprite m_sprite;

  TypeBaseCharacter m_type_character;
};

class CharacterSouthPark : public BaseCharacter {
 public:
  CharacterSouthPark(b2World *world, const sf::Texture *texture,
                     const CharacterSpriteInfo &sprite_data)
      : BaseCharacter(world, texture, sprite_data) {
    {
      m_type_character = TypeBaseCharacter::CHARACTER_SOUTH_PARK;
      b2PrismaticJointDef jd;
      jd.bodyA = m_b2_base;
      jd.bodyB = m_b2_body;
      jd.enableLimit = true;
      jd.localAnchorA.SetZero();
      jd.localAnchorB.SetZero();
      jd.localAxisA.Set(0.0f, -1.0f);
      jd.lowerTranslation = 0.f;
      jd.upperTranslation = 0.6f;
      // jd.enableMotor = true;
      jd.collideConnected = false;
      // jd.maxMotorForce = +10.f;
      // jd.motorSpeed = -100.f;

      m_b2_joint_prism =
          static_cast<b2PrismaticJoint *>(world->CreateJoint(&jd));
      /*
      b2MotorJointDef mjd;
      mjd.Initialize(m_body, m_body_2);
      mjd.maxForce = 2.8f;
      mjd.maxTorque = 0.0f;
      mjd.linearOffset = { 0, 0 };
      mjd.collideConnected = true;
      */
      b2MotorJointDef mjd;
      mjd.Initialize(m_b2_body, m_b2_base);
      mjd.maxForce = 1000.0f;
      mjd.maxTorque = 0.0f;
      m_b2_joint = static_cast<b2MotorJoint *>(world->CreateJoint(&mjd));

      // m_joint = (b2MotorJoint*)world->CreateJoint(&mjd);
    }
    m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));
  }
  void move(b2Vec2 velocity, float deltaTime) override {
    BaseCharacter::move(velocity, deltaTime);

    static float m_time;
    static int dir = 1;

    m_time += static_cast<float>(deltaTime / 150 * dir);  //скорость прыжков
    if ((m_time > m_b2_joint_prism->GetLowerLimit()) ||
        (m_b2_base->GetLinearVelocity().LengthSquared() > 0)) {
      if (m_time >= m_b2_joint_prism->GetUpperLimit()) {
        m_time = m_b2_joint_prism->GetUpperLimit();
        dir = -1;
      } else if (m_time <= m_b2_joint_prism->GetLowerLimit()) {
        m_time = m_b2_joint_prism->GetLowerLimit();
        dir = 1;
      }
    } else
      m_time = m_b2_joint_prism->GetLowerLimit();
    m_b2_joint->SetLinearOffset({0, m_time});

    // g_debugDraw.DrawPoint(linearOffset, 4.0f, b2Color(0.9f, 0.9f, 0.9f));
  }
  void draw(sf::RenderWindow &window) override {
      m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));BaseCharacter::draw(window); }
  void contact(b2Fixture *B) override {
    LOG() << "I'am SouthParkBoys and I've begun the colliding with.. hz"
          << std::endl;
    UNUSE(B);
    //чекать с чем объект сталкивается
  }
  void endContact(b2Fixture *B) override {
    LOG() << "I'am SouthParkBoys and I've dune the colliding with.. hz"
          << std::endl;
    UNUSE(B);
  }
  ~CharacterSouthPark() { LOG() <<"YOUUURRR HAVE KILLED KYLLLEEE!!/n"; }

  b2MotorJoint *m_b2_joint;
  b2PrismaticJoint *m_b2_joint_prism;

  void updatePhysics(float deltaTime) {
    m_b2_base->SetLinearVelocity({0.0, 0.0});
    static float m_time;
    static int dir = 1;

    m_time += static_cast<float>(deltaTime / 150 * dir);  //скорость прыжков
    if ((m_time > m_b2_joint_prism->GetLowerLimit()) ||
        (m_b2_base->GetLinearVelocity().LengthSquared() > 0)) {
      if (m_time >= m_b2_joint_prism->GetUpperLimit()) {
        m_time = m_b2_joint_prism->GetUpperLimit();
        dir = -1;
      } else if (m_time <= m_b2_joint_prism->GetLowerLimit()) {
        m_time = m_b2_joint_prism->GetLowerLimit();
        dir = 1;
      }
    } else
      m_time = m_b2_joint_prism->GetLowerLimit();
    m_b2_joint->SetLinearOffset({0, m_time});
  }
};

class CharacterAlinasBoys : public BaseCharacter {
 public:
  CharacterAlinasBoys(b2World *world, const sf::Texture *texture,
                      const CharacterSpriteInfo &sprite_data)
      : BaseCharacter(world, texture,
                      sprite_data) {
    {
      m_type_character =  TypeBaseCharacter::ALINAS_BOYS;
      b2PrismaticJointDef jd;
      jd.bodyA = m_b2_base;
      jd.bodyB = m_b2_body;
      jd.enableLimit = true;
      jd.localAnchorA.SetZero();
      jd.localAnchorB.SetZero();
      jd.localAxisA.Set(0.0f, -1.0f);
      jd.lowerTranslation = 0.f;
      jd.upperTranslation = 0.f;
      jd.collideConnected = false;

      world->CreateJoint(&jd);
    }
    m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));
  }

  void move(b2Vec2 velocity, float deltaTime) override {
    BaseCharacter::move(velocity, deltaTime);
  }
  void draw(sf::RenderWindow &window) override { BaseCharacter::draw(window); }
  void contact(b2Fixture *B) override {
    LOG() << "I'am AlinasBoys and I've begun the colliding with.. hz"
          << std::endl;
  }
  void endContact(b2Fixture *B) override {
    LOG() << "I'am AlinasBoys and I've done the colliding with.. hz"
          << std::endl;
  }
  ~CharacterAlinasBoys() {}
};
}
}

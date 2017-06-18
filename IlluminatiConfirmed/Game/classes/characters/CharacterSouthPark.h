#pragma once

#include "../../Logger/Logger.h"
#include "Box2D/Box2D.h"
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "BaseCharacter.h"
using IlluminatiConfirmed::BaseCharacter;

namespace IlluminatiConfirmed {

class CharacterSouthPark : public BaseCharacter {
public:
  CharacterSouthPark(b2World &world, const CharacterSpriteInfo &sprite_data,
                     const std::string &bullets);
  void move(b2Vec2 velocity, float deltaTime) override;
  void draw(sf::RenderWindow &window) override;
  void contact(b2Fixture *B) override;
  void endContact(b2Fixture *B) override;
  ~CharacterSouthPark();

  b2MotorJoint *m_b2_joint;
  b2PrismaticJoint *m_b2_joint_prism;

  void updatePhysics(float deltaTime) {
    m_b2_base->SetLinearVelocity({0.0, 0.0});
    static float m_time;
    static int dir = 1;

    m_time += static_cast<float>(deltaTime / 150 * dir); //скорость прыжков
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
}

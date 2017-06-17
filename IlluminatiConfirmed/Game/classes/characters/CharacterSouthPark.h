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
  CharacterSouthPark(b2World &world, const CharacterSpriteInfo &sprite_data);
  void move(float deltaTime) override;
  void draw(sf::RenderWindow &window) override;
  void contact(b2Fixture *B) override;
  void endContact(b2Fixture *B) override;
  ~CharacterSouthPark();

  b2MotorJoint *m_b2_joint;
  b2PrismaticJoint *m_b2_joint_prism;
};
}

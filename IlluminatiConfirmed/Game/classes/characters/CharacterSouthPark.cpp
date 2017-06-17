#include "CharacterSouthPark.h"

using namespace IlluminatiConfirmed;

CharacterSouthPark::CharacterSouthPark(b2World &world,
                                       const CharacterSpriteInfo &sprite_data)
    : BaseCharacter(Type::CHARACTER_SOUTH_PARK, world, sprite_data) {
  {
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

    m_b2_joint_prism = static_cast<b2PrismaticJoint *>(world.CreateJoint(&jd));
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
    m_b2_joint = static_cast<b2MotorJoint *>(world.CreateJoint(&mjd));

    // m_joint = (b2MotorJoint*)world->CreateJoint(&mjd);
  }
  m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));
}
void CharacterSouthPark::draw(sf::RenderWindow &window) {
  BaseCharacter::draw(window);
}
void CharacterSouthPark::move(float deltaTime) {
  BaseCharacter::move(deltaTime);

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

  // g_debugDraw.DrawPoint(linearOffset, 4.0f, b2Color(0.9f, 0.9f, 0.9f));
}
void CharacterSouthPark::contact(b2Fixture *B) {
  LOG() << "I'am SouthParkBoys and I've begun the colliding with.. hz"
        << std::endl;
  UNUSE(B);
  //чекать с чем объект сталкивается
}
void CharacterSouthPark::endContact(b2Fixture *B) {
  LOG() << "I'am SouthParkBoys and I've dune the colliding with.. hz"
        << std::endl;
  UNUSE(B);
}
CharacterSouthPark::~CharacterSouthPark() {}

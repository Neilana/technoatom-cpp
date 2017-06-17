#include "CharacterAlinasBoys.h"

using namespace IlluminatiConfirmed;

CharacterAlinasBoys::CharacterAlinasBoys(b2World &world,
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
    jd.upperTranslation = 0.f;
    jd.collideConnected = false;

    world.CreateJoint(&jd);
  }
  m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));
}
void CharacterAlinasBoys::move(b2Vec2 velocity, float deltaTime) {
  BaseCharacter::move(velocity, deltaTime);
}
void CharacterAlinasBoys::draw(sf::RenderWindow &window) {
  BaseCharacter::draw(window);
}
void CharacterAlinasBoys::contact(b2Fixture *B) {
  LOG() << "I'am AlinasBoys and I've begun the colliding with.. hz"
        << std::endl;
}
void CharacterAlinasBoys::endContact(b2Fixture *B) {
  LOG() << "I'am AlinasBoys and I've done the colliding with.. hz" << std::endl;
}
CharacterAlinasBoys::~CharacterAlinasBoys() {}

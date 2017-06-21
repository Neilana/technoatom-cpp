#include "Character.h"
#include "Weapons.h"

void IlluminatiConfirmed::experimental::BaseCharacter::draw(sf::RenderWindow &window) {
    if (m_weapon)
        m_weapon->setPositionRotation(
                    B2Vec2toSfVector2<float>(getFixtureWorldPosition(m_b2_body_fixture)),
                    -20);
    window.draw(m_sprite);
    if (m_weapon) m_weapon->draw(window);
}

void IlluminatiConfirmed::experimental::BaseCharacter::setWeapon(IlluminatiConfirmed::experimental::Weapon *weapon) {
    if (m_weapon) delete m_weapon;
    m_weapon = weapon;
}

void IlluminatiConfirmed::experimental::BaseCharacter::attack() {
    if (m_weapon) m_weapon->attack();
}


IlluminatiConfirmed::experimental::CharacterSouthPark::CharacterSouthPark(b2World *world, const sf::Texture *texture, const IlluminatiConfirmed::experimental::CharacterSpriteInfo &sprite_data)
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

void IlluminatiConfirmed::experimental::CharacterSouthPark::move(b2Vec2 velocity, float deltaTime) {
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

void IlluminatiConfirmed::experimental::CharacterSouthPark::draw(sf::RenderWindow &window) {
    m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));
    BaseCharacter::draw(window);
}

void IlluminatiConfirmed::experimental::CharacterSouthPark::contact(b2Fixture *B) {
    LOG() << "I'am SouthParkBoys and I've begun the colliding with.. hz"
          << std::endl;
    UNUSE(B);
    //чекать с чем объект сталкивается
}

void IlluminatiConfirmed::experimental::CharacterSouthPark::endContact(b2Fixture *B) {
    LOG() << "I'am SouthParkBoys and I've dune the colliding with.. hz"
          << std::endl;
    UNUSE(B);
}

IlluminatiConfirmed::experimental::CharacterSouthPark::~CharacterSouthPark() { LOG() << "YOUUURRR HAVE KILLED KYLLLEEE!!/n"; }

void IlluminatiConfirmed::experimental::CharacterSouthPark::updatePhysics(float deltaTime) {
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

IlluminatiConfirmed::experimental::CharacterAlinasBoys::CharacterAlinasBoys(b2World *world, const sf::Texture *texture, const IlluminatiConfirmed::experimental::CharacterSpriteInfo &sprite_data)
    : BaseCharacter(world, texture, sprite_data) {
    {
        m_type_character = TypeBaseCharacter::ALINAS_BOYS;
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

void IlluminatiConfirmed::experimental::CharacterAlinasBoys::move(b2Vec2 velocity, float deltaTime) {
    BaseCharacter::move(velocity, deltaTime);
}

void IlluminatiConfirmed::experimental::CharacterAlinasBoys::draw(sf::RenderWindow &window) { BaseCharacter::draw(window); }

void IlluminatiConfirmed::experimental::CharacterAlinasBoys::contact(b2Fixture *B) {
    LOG() << "I'am AlinasBoys and I've begun the colliding with.. hz"
          << std::endl;
}

void IlluminatiConfirmed::experimental::CharacterAlinasBoys::endContact(b2Fixture *B) {
    LOG() << "I'am AlinasBoys and I've done the colliding with.. hz"
          << std::endl;
}

IlluminatiConfirmed::experimental::CharacterAlinasBoys::~CharacterAlinasBoys() {}

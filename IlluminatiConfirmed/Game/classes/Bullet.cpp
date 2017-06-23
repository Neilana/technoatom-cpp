#include "Bullet.h"

IlluminatiConfirmed::experimental::Bullet::Bullet(
    b2World *world, sf::Texture *texture,
    IlluminatiConfirmed::experimental::BulletInfo &&info)
    : BaseInterface(TypeBase::BULLET), m_info(std::move(info)) {
  static int count = 0;

  LOG() << "Create bullet #" << count++ << std::endl;
  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.bullet = true;
    // bd.position.Set(SfPointtoB2Point(sprite_data.x_position),
    //                SfPointtoB2Point(sprite_data.y_position));
    bd.linearDamping = 0.f;
    bd.fixedRotation = false;
    m_b2_base = world->CreateBody(&bd);

    b2PolygonShape polygon;
    // 0.7 - где то читал, что физические размеры должны быть чуть меньше
    // спрайта)
    polygon.SetAsBox(
        SfPointtoB2Point(m_info.scale *
                         m_info.vec_of_rects_with_bullet.at(0).width) /
            2.0f * 0.7f,
        SfPointtoB2Point(m_info.scale *
                         m_info.vec_of_rects_with_bullet.at(0).height) /
            2.0f * 0.7f);

    b2FixtureDef fixture;
    fixture.friction = 0.f;
    fixture.density = 0.005f;
    fixture.isSensor = true;

    fixture.shape = &polygon;

    m_b2_base_fixture = m_b2_base->CreateFixture(&fixture);
    m_b2_base_fixture->SetUserData(this);
  }

  m_sprite.setTexture(*texture);
  m_sprite.scale(m_info.scale, m_info.scale);
  m_sprite.setTextureRect(m_info.vec_of_rects_with_bullet.at(0));
  m_sprite.setOrigin(m_sprite.getTextureRect().width / 2.f,
                     m_sprite.getTextureRect().height / 2.f);
}

void IlluminatiConfirmed::experimental::Bullet::setTransform(
    IlluminatiConfirmed::experimental::BulletSets &&sets) {
  LOG() << "Dir1 " << sets.dir << std::endl;
  sets.dir.Normalize();
  LOG() << "Dir2 " << sets.dir << std::endl;
  // sets.dir.y *= -1.f;

  static auto getAngle = [](auto &&lhs, auto &&rhs) {
    auto dot = lhs.x * rhs.x + lhs.y * lhs.y;
    auto mod_lhs = sqrtf(lhs.x * lhs.x + lhs.y * lhs.y);
    auto mod_rhs = sqrtf(rhs.x * rhs.x + rhs.y * rhs.y);
    return dot / (mod_lhs * mod_rhs);
  };

  m_b2_base->SetTransform(sets.position, atanf(sets.dir.y / sets.dir.x));
  sets.dir *= m_info.velocity;
  LOG() << "Dir3 " << sets.dir << std::endl;
  m_b2_base->SetLinearVelocity(sets.dir);
  LOG() << "Dir4 " << sets.dir << std::endl;
}

void IlluminatiConfirmed::experimental::Bullet::draw(sf::RenderWindow &window) {
  m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_base->GetPosition()));
  m_sprite.setRotation(m_b2_base->GetTransform().q.GetAngle() / 3.14f * 180);
  static int count;

  //  LOG() << "Position of bullet #" << count++ << " : "
  //        << m_sprite.getPosition().x << " " << m_sprite.getPosition().y
  //        << std::endl;

  window.draw(m_sprite);
}

void IlluminatiConfirmed::experimental::Bullet::move(b2Vec2 velocity,
                                                     float deltaTime) {}

void IlluminatiConfirmed::experimental::Bullet::contact(b2Fixture *B) {}

void IlluminatiConfirmed::experimental::Bullet::endContact(b2Fixture *B) {}

// IlluminatiConfirmed::experimental::Bullet::Bullet(b2World *world, sf::Texture
// *texture, IlluminatiConfirmed::experimental::BulletInfo &&info)
//    : BaseInterface(TypeBase::BULLET), m_b2_center(nullptr) {
//    LOG() << "Create bullet \n";
//    {
//        b2BodyDef bd;
//        bd.fixedRotation = false;  //можно сделать центр не сталкивающимся с
//        чем
//        //либо, изменяющим траекторию,если это ракета
//        //самонаведения :)
//        bd.bullet = true;
//        bd.type = b2_dynamicBody;
//        bd.linearDamping = 0.f;
//        m_b2_center = world->CreateBody(&bd);

//        b2PolygonShape polygon;
//        polygon.SetAsBox(1.f, 2.f);

//        b2FixtureDef fixture;
//        fixture.friction = 1.f;
//        fixture.density = 5.f;
//        fixture.restitution = 0;
//        fixture.isSensor = false;

//        fixture.shape = &polygon;
//        m_b2_center_fixture = m_b2_center->CreateFixture(&fixture);
//        m_b2_center_fixture->SetUserData(this);
//    }
//    {
//        b2BodyDef bd;
//        bd.type = b2_dynamicBody;
//        bd.bullet = true;
//        // bd.position.Set(SfPointtoB2Point(sprite_data.x_position),
//        //                SfPointtoB2Point(sprite_data.y_position));
//        bd.linearDamping = 0.f;
//        bd.fixedRotation = false;
//        m_b2_base = world->CreateBody(&bd);

//        b2PolygonShape polygon;
//        // 0.7 - где то читал, что физические размеры должны быть чуть меньше
//        // спрайта)
//        polygon.SetAsBox(
//                    SfPointtoB2Point(info.scale *
//                                     info.vec_of_rects_with_bullet.at(0).width)
//                                     /
//                    2.0f * 0.7f,
//                    SfPointtoB2Point(info.scale *
//                                     info.vec_of_rects_with_bullet.at(0).height)
//                                     /
//                    2.0f * 0.7f);

//        b2FixtureDef fixture;
//        fixture.friction = 0.f;
//        fixture.density = 0.005f;
//        fixture.isSensor = false;

//        fixture.shape = &polygon;

//        m_b2_base_fixture = m_b2_base->CreateFixture(&fixture);
//        m_b2_base_fixture->SetUserData(this);
//    }
//    {
//        b2MotorJointDef mjd;
//        mjd.Initialize(m_b2_center, m_b2_base);
//        mjd.maxForce = 1000.0f;
//        mjd.maxTorque = 0.0f;
//        m_b2_joint = static_cast<b2MotorJoint *>(world->CreateJoint(&mjd));
//    }
//    m_sprite.setTexture(*texture);
//    m_sprite.scale(info.scale, info.scale);
//    m_sprite.setTextureRect(info.vec_of_rects_with_bullet.at(0));
//    m_sprite.setOrigin(m_sprite.getTextureRect().width / 2.f,
//                       m_sprite.getTextureRect().height / 2.f);
//}

// void
// IlluminatiConfirmed::experimental::Bullet::setTransform(IlluminatiConfirmed::experimental::BulletSets
// &&sets) {
//    m_b2_center->SetTransform(sets.position,
//                              RadBetweenVectors(sets.dir, b2Vec2(0, 1)));
//    m_b2_base->SetTransform(sets.position,
//                            RadBetweenVectors(sets.dir, b2Vec2(0, 1)));
//    sets.dir *= m_info.velocity;
//    m_b2_center->SetLinearVelocity(sets.dir);
//}

// void IlluminatiConfirmed::experimental::Bullet::draw(sf::RenderWindow
// &window) {
//    m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_base->GetPosition()));
//    m_sprite.setRotation(m_b2_base->GetTransform().q.GetAngle() / 3.14f *
//    180);
//    window.draw(m_sprite);
//}

// void IlluminatiConfirmed::experimental::Bullet::move(b2Vec2 velocity, float
// deltaTime) {
//    static float m_time;
//    static int dir = 1;
//    static float m_angle = -1;
//    static int dir_angle = 1;

//    m_time += float(deltaTime / 700 * dir);  //скорость прыжков
//    if (m_time > 1) {
//        m_time = 1;
//        dir = -1;

//    } else if (m_time < -1) {
//        m_time = -1;
//        dir = 1;
//    }

//    m_angle += float(deltaTime / 700 * dir_angle);  //скорость прыжков

//    if (m_angle > 1) {
//        m_angle = 1;
//        dir_angle = -1;

//    } else if (m_angle < -1) {
//        m_angle = -1;
//        dir_angle = 1;
//    }
//    static auto getAngle = [](auto &&lhs, auto &&rhs) {
//        auto dot = lhs.x * rhs.x + lhs.y * lhs.y;
//        auto mod_lhs = sqrtf(lhs.x * lhs.x + lhs.y * lhs.y);
//        auto mod_rhs = sqrtf(rhs.x * rhs.x + rhs.y * rhs.y);
//        return dot / (mod_lhs * mod_rhs);
//    };
//    //даже не спрашивай как я к этому пришел
//    m_b2_base->SetTransform(
//                m_b2_base->GetPosition(),
//                m_b2_center->GetTransform().q.GetAngle() +
//                float((m_angle > 0) ? (1.f) : (-1.f)) *
//                acosf(getAngle(b2Vec2(1.f, 0.f), b2Vec2(1.f, m_angle))));
//    m_b2_joint->SetLinearOffset({0, m_time});
//}

// void IlluminatiConfirmed::experimental::Bullet::contact(b2Fixture *B) {}

// void IlluminatiConfirmed::experimental::Bullet::endContact(b2Fixture *B) {}

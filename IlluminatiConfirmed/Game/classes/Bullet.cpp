#include "Bullet.h"

IlluminatiConfirmed::experimental::BulletInterface::BulletInterface(
    b2World *world, sf::Texture *texture, SoundPack pack, BulletInfo info)
    : BaseInterface(TypeBase::BULLET),
      m_info(std::move(info)),
      m_sound_pack(std::move(pack)) {}

void IlluminatiConfirmed::experimental::BulletInterface::setTransform(
    IlluminatiConfirmed::experimental::BulletSets &&sets) {
  sets.dir.Normalize();
  m_b2_base->SetTransform(sets.position, atanf(sets.dir.y / sets.dir.x));
  sets.dir *= m_info.velocity;
  m_b2_base->SetLinearVelocity(sets.dir);
}

void IlluminatiConfirmed::experimental::BulletInterface::draw(
    sf::RenderWindow &window) {
  m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_base->GetPosition()));
  m_sprite.setRotation(m_b2_base->GetTransform().q.GetAngle() / 3.14f * 180);

  window.draw(m_sprite);
}

void IlluminatiConfirmed::experimental::BulletInterface::move(b2Vec2 velocity,
                                                              float deltaTime) {
}

void IlluminatiConfirmed::experimental::BulletInterface::contact(
    BaseInterface *B) {
  if (B->getTypeBase() == TypeBase::MAPS_STUFF) {
    m_sound_pack.hitting_building->play();
    is_dead = true;
  } else if (B->getTypeBase() == TypeBase::CHARACTER)
    if (B != whose()) {
      is_dead = true;
      whose()->playKilled();
    }
}

void IlluminatiConfirmed::experimental::BulletInterface::endContact(
    BaseInterface *B) {}

void IlluminatiConfirmed::experimental::BulletInterface::playHit() {}

IlluminatiConfirmed::experimental::BaseCharacter *
IlluminatiConfirmed::experimental::BulletInterface::whose() const {
  return m_info.whose;
}

IlluminatiConfirmed::experimental::Rocket::Rocket(
    b2World *world, sf::Texture *texture, SoundPack pack,
    IlluminatiConfirmed::experimental::BulletInfo info)
    : BulletInterface(world, texture, std::move(pack), std::move(info)) {
  m_type_bullet = TypeBullet::ROCKET;

  {
    b2BodyDef bd;
    bd.fixedRotation = false;  //можно сделать центр не сталкивающимся с
    //либо, изменяющим траекторию,если это ракета
    //самонаведения :)
    bd.bullet = true;
    bd.type = b2_dynamicBody;
    bd.linearDamping = 0.f;
    m_b2_center = world->CreateBody(&bd);

    b2PolygonShape polygon;
    polygon.SetAsBox(0.5f, 0.1f);

    b2FixtureDef fixture;
    fixture.friction = 1.f;
    fixture.density = 5.f;
    fixture.restitution = 0;
    fixture.isSensor = true;

    fixture.shape = &polygon;
    m_b2_center_fixture = m_b2_center->CreateFixture(&fixture);
    m_b2_center_fixture->SetUserData(this);
  }
  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.bullet = true;
    bd.linearDamping = 0.f;
    bd.fixedRotation = false;
    m_b2_base = world->CreateBody(&bd);

    b2PolygonShape polygon;
    // 0.7 - где то читал, что физические размеры должны быть чуть меньше
    // спрайта
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
  {
    b2MotorJointDef mjd;
    mjd.Initialize(m_b2_center, m_b2_base);
    mjd.maxForce = 1000.0f;
    mjd.maxTorque = 0.0f;
    m_b2_joint = static_cast<b2MotorJoint *>(world->CreateJoint(&mjd));
  }
  m_sprite.setTexture(*texture);
  m_sprite.scale(m_info.scale, m_info.scale);
  m_sprite.setTextureRect(m_info.vec_of_rects_with_bullet.at(0));
  m_sprite.setOrigin(m_sprite.getTextureRect().width / 2.f,
                     m_sprite.getTextureRect().height / 2.f);
}

void IlluminatiConfirmed::experimental::Rocket::move(b2Vec2 velocity,
                                                     float deltaTime) {
  m_time += float(20.f / 1300.f * dir);
  if (m_time > 1) {
    m_time = 1;
    dir = -1;

  } else if (m_time < -1) {
    m_time = -1;
    dir = 1;
  }

  m_angle += float(20.f / 1300.f * dir_angle);

  if (m_angle > 1) {
    m_angle = 1;
    dir_angle = -1;

  } else if (m_angle < -1) {
    m_angle = -1;
    dir_angle = 1;
  }
  static auto getAngle = [](auto &&lhs, auto &&rhs) {
    auto dot = lhs.x * rhs.x + lhs.y * lhs.y;
    auto mod_lhs = sqrtf(lhs.x * lhs.x + lhs.y * lhs.y);
    auto mod_rhs = sqrtf(rhs.x * rhs.x + rhs.y * rhs.y);
    return dot / (mod_lhs * mod_rhs);
  };
  //даже не спрашивай как я к этому пришел

  auto s1 = m_b2_center->GetTransform().q.GetAngle();
  auto ang = getAngle(b2Vec2(1.f, 0.f), b2Vec2(1.f, 0.5f * m_angle));
  auto m1 = acosf(ang);
  auto m2 = float((m_angle > 0) ? (1.f) : (-1.f));
  auto s2 = m1 * m2;
  auto res = s1 + s2;
  auto poss = m_b2_base->GetPosition();
  m_b2_base->SetTransform(poss, res);
  m_b2_joint->SetLinearOffset({0, m_time});
}

void IlluminatiConfirmed::experimental::Rocket::draw(sf::RenderWindow &window) {
  m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_base->GetPosition()));
  m_sprite.setRotation(m_b2_base->GetTransform().q.GetAngle() / 3.14f * 180);
  window.draw(m_sprite);
}

void IlluminatiConfirmed::experimental::Rocket::contact(
    IlluminatiConfirmed::experimental::BaseInterface *B) {
  BulletInterface::contact(B);
}

void IlluminatiConfirmed::experimental::Rocket::endContact(
    IlluminatiConfirmed::experimental::BaseInterface *B) {}

void IlluminatiConfirmed::experimental::Rocket::playHit() {}

void IlluminatiConfirmed::experimental::Rocket::setTransform(
    IlluminatiConfirmed::experimental::BulletSets &&sets) {
  sets.dir.Normalize();
  auto angle = atanf(sets.dir.y / sets.dir.x);

  if (sets.dir.x < 0) angle -= b2_pi;
  m_b2_base->SetTransform(sets.position, angle);
  m_b2_center->SetTransform(sets.position, angle);
  sets.dir *= m_info.velocity;
  m_b2_base->SetLinearVelocity(sets.dir);
  m_b2_center->SetLinearVelocity(sets.dir);
}

IlluminatiConfirmed::experimental::Rocket::~Rocket() {
  m_b2_center->GetWorld()->DestroyBody(m_b2_center);
}

IlluminatiConfirmed::experimental::LittleBullet::LittleBullet(
    b2World *world, sf::Texture *texture,
    IlluminatiConfirmed::experimental::BulletInterface::SoundPack pack,
    IlluminatiConfirmed::experimental::BulletInfo info)
    : BulletInterface(world, texture, std::move(pack), std::move(info)) {
  m_type_bullet = TypeBullet::little_bullet;

  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.bullet = true;
    bd.linearDamping = 0.f;
    bd.fixedRotation = false;
    m_b2_base = world->CreateBody(&bd);
    m_b2_base->SetUserData(this);

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

IlluminatiConfirmed::experimental::LittleBullet::~LittleBullet() {}

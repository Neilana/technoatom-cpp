#include "charactersouthpark.h"

using namespace IlluminatiConfirmed;

BaseCharacter::BaseCharacter(Type type, b2World& world,
                             const CharacterSpriteInfo& sprite_data)
    : m_type(type) {
  {
    b2BodyDef bd;
    bd.fixedRotation = true;
    bd.type = b2_dynamicBody;
    bd.position.Set(SfPointtoB2Point(sprite_data.x_position),
                    SfPointtoB2Point(sprite_data.y_position));
    bd.linearDamping = 1000.f;
    m_b2_base = world.CreateBody(&bd);

    b2PolygonShape poligon;
    poligon.SetAsBox(0.5f, 0.1f);

    b2FixtureDef fixture;
    fixture.friction = 1.f;
    fixture.density = 50.f;
    fixture.restitution = 0;
    fixture.isSensor = false;

    fixture.shape = &poligon;
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
    m_b2_body = world.CreateBody(&bd);

    b2PolygonShape poligon;
    poligon.SetAsBox(.5f, 1.f, {0.f, -1.f}, 0);
    b2FixtureDef fixture;
    fixture.friction = 0.f;
    fixture.density = 0.005f;
    fixture.isSensor = true;

    fixture.shape = &poligon;

    m_b2_body_fixture = m_b2_body->CreateFixture(&fixture);
    m_b2_body_fixture->SetUserData(this);
  }

  if (!texture.loadFromFile(sprite_data.puth_to_texture)) {
    LOG() << "File " << sprite_data.puth_to_texture << " hasn't opened"
          << std::endl;
  }
  front_rects.reserve(sprite_data.count_of_frames);
  back_rects.reserve(sprite_data.count_of_frames);
  left_rects.reserve(sprite_data.count_of_frames);
  right_rects.reserve(sprite_data.count_of_frames);

  m_sprite.setTexture(texture);
  m_sprite.scale((float)sprite_data.size / sprite_data.width,
                 (float)sprite_data.size / sprite_data.height);
  m_sprite.setTextureRect({0, 0, sprite_data.height, sprite_data.width});
  m_sprite.setOrigin(m_sprite.getTextureRect().width / 2.f,
                     m_sprite.getTextureRect().height);

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
  assert(!(front_rects.size() == back_rects.size() == right_rects.size() ==
           left_rects.size()));
}

Type BaseCharacter::getType() const { return m_type; }
void BaseCharacter::move(float deltaTime) {
  static float currentFrame;
  currentFrame += 0.005 * deltaTime;
  if ((int)currentFrame > front_rects.size() - 1) currentFrame = 0;
  b2Vec2 velocity = {0.f, 0.f};
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    velocity += b2Vec2({-1.f, 0.f});
    m_sprite.setTextureRect(left_rects.at((int)currentFrame));
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    velocity += b2Vec2({+1.f, 0.f});
    m_sprite.setTextureRect(right_rects.at((int)currentFrame));
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    velocity += b2Vec2({0.f, -1.f});
    m_sprite.setTextureRect(back_rects.at((int)currentFrame));
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    velocity += b2Vec2({0.f, +1.f});
    m_sprite.setTextureRect(front_rects.at((int)currentFrame));
  }
  velocity.Normalize();
  velocity *= 100.f;
  m_b2_base->SetLinearVelocity(velocity);

  //для движения по диагонали перс должен поворачиваться
}

void BaseCharacter::draw(sf::RenderWindow& window) {
  m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));
  window.draw(m_sprite);
}

BaseCharacter::~BaseCharacter() {}

CharacterSouthPark::CharacterSouthPark(b2World& world,
                                       const CharacterSpriteInfo& sprite_data)
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

    m_b2_joint_prism = static_cast<b2PrismaticJoint*>(world.CreateJoint(&jd));
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
    m_b2_joint = static_cast<b2MotorJoint*>(world.CreateJoint(&mjd));

    // m_joint = (b2MotorJoint*)world->CreateJoint(&mjd);
  }
  m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));
}
void CharacterSouthPark::draw(sf::RenderWindow& window) {
  BaseCharacter::draw(window);
}
void CharacterSouthPark::move(float deltaTime) {
  BaseCharacter::move(deltaTime);

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
void CharacterSouthPark::contact(b2Fixture* B) {
  LOG() << "I'am SouthParkBoys and I've begun the colliding with.. hz"
        << std::endl;
  UNUSE(B);
  //чекать с чем объект сталкивается
}
void CharacterSouthPark::endContact(b2Fixture* B) {
  LOG() << "I'am SouthParkBoys and I've dune the colliding with.. hz"
        << std::endl;
  UNUSE(B);
}
CharacterSouthPark::~CharacterSouthPark() {}

CharacterAlinasBoys::CharacterAlinasBoys(b2World& world,
                                         const CharacterSpriteInfo& sprite_data)
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
void CharacterAlinasBoys::move(float deltaTime) {
  BaseCharacter::move(deltaTime);
}
void CharacterAlinasBoys::draw(sf::RenderWindow& window) {
  BaseCharacter::draw(window);
}
void CharacterAlinasBoys::contact(b2Fixture* B) {
  LOG() << "I'am AlinasBoys and I've begun the colliding with.. hz"
        << std::endl;
}
void CharacterAlinasBoys::endContact(b2Fixture* B) {
  LOG() << "I'am AlinasBoys and I've done the colliding with.. hz" << std::endl;
}
CharacterAlinasBoys::~CharacterAlinasBoys() {}

void MyContactListener::BeginContact(b2Contact* contact) {
  void* user_data_A = contact->GetFixtureA()->GetUserData();
  if (user_data_A)
    static_cast<BaseCharacter*>(user_data_A)->contact(contact->GetFixtureB());
  void* user_data_B = contact->GetFixtureA()->GetUserData();
  if (user_data_B)
    static_cast<BaseCharacter*>(user_data_B)->contact(contact->GetFixtureB());
  // if (Type::CHARACTER_SOUTH_PARK ==
  //    static_cast<BaseCharacter*>(user_data)->getType()) {
  //    static_cast<BaseCharacter*>(user_data)->getType()
  // };
}

void MyContactListener::EndContact(b2Contact* contact) {
  void* user_data_A = contact->GetFixtureA()->GetUserData();
  if (user_data_A)
    static_cast<BaseCharacter*>(user_data_A)
        ->endContact(contact->GetFixtureB());
  void* user_data_B = contact->GetFixtureA()->GetUserData();
  if (user_data_B)
    static_cast<BaseCharacter*>(user_data_B)
        ->endContact(contact->GetFixtureB());
}

void MyContactListener::PreSolve(b2Contact* contact,
                                 const b2Manifold* oldManifold) {
  //    const b2Manifold* manifold = contact->GetManifold();

  //    b2Fixture* fixtureA = contact->GetFixtureA();
  //    b2Fixture* fixtureB = contact->GetFixtureB();

  //    b2WorldManifold worldManifold;
  //    contact->GetWorldManifold(&worldManifold);

  //    b2Body* bodyA = fixtureA->GetBody();
  //    b2Body* bodyB = fixtureB->GetBody();
}

void MyContactListener::PostSolve(b2Contact* contact,
                                  const b2ContactImpulse* Impulse) {}

#include "Character.h"
#include "Weapons.h"

IlluminatiConfirmed::experimental::BaseCharacter::BaseCharacter(
    b2World *world, const sf::Texture *texture,
    const IlluminatiConfirmed::experimental::CharacterSpriteInfo &sprite_data)
    : BaseInterface(BaseInterface::CHARACTER), m_weapon(nullptr),
      m_height(sprite_data.height) {
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

void IlluminatiConfirmed::experimental::BaseCharacter::draw(
    sf::RenderWindow &window) {
  m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));
  window.draw(m_sprite);

  // !!!!!!!!!!!
  auto pos_of_weapon =
      B2Vec2toSfVector2<float>(getFixtureWorldPosition(m_b2_body_fixture));
  //мол на 20 пр ниже, чем центр фикстуры
  pos_of_weapon.y = pos_of_weapon.y + 0.3f * m_height;

  moveWeapon(pos_of_weapon,
             180 / b2_pi * RadBetweenVectors(pos_of_weapon,
                                             sf::Mouse::getPosition(window)));
  m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));

  if (m_direction == Direction::Up) {
    if (m_weapon)
      m_weapon->draw(window);

  } else {
    window.draw(m_sprite);
    if (m_weapon)
      m_weapon->draw(window);
  }
}

void IlluminatiConfirmed::experimental::BaseCharacter::move(b2Vec2 velocity,
                                                            float deltaTime) {
  static float currentFrame;
  currentFrame += 0.005 * deltaTime;

  //    m_body->SetTransform(
  //        m_body->GetPosition(),
  //        RadBetweenVectors(m_body->GetPosition(),
  // SfVector2toB2Vec2(sf::Mouse::getPosition(window))));

  // m_sprite.setPosition(FromBox2DtoPixel(m_body->GetPosition().x),
  //                    FromBox2DtoPixel(m_body->GetPosition().y));

  if (int(currentFrame) > m_frames - 1)
    currentFrame = 0;

  m_direction = findDirectonByVelocity(velocity);
  m_sprite.setTextureRect(m_directionRects[m_direction].at((int)currentFrame));

  velocity.Normalize();
  velocity *= 100.f;
  m_b2_base->SetLinearVelocity(velocity);

  //для движения по диагонали перс должен поворачиваться
}

void IlluminatiConfirmed::experimental::BaseCharacter::contact(b2Fixture *B) {}

void IlluminatiConfirmed::experimental::BaseCharacter::endContact(
    b2Fixture *B) {}

void IlluminatiConfirmed::experimental::BaseCharacter::setWeapon(
    IlluminatiConfirmed::experimental::Weapon *weapon) {
  if (m_weapon)
    delete m_weapon;
  m_weapon = weapon;
}

void IlluminatiConfirmed::experimental::BaseCharacter::moveWeapon(
    const sf::Vector2f &pos, float rot) {
  if (m_weapon)
    m_weapon->setPositionRotation(pos, rot);
}

void IlluminatiConfirmed::experimental::BaseCharacter::attack() {
  if (m_weapon)
    m_weapon->attack();
}

IlluminatiConfirmed::experimental::BaseCharacter::~BaseCharacter() {
  if (m_weapon)
    delete m_weapon;
  m_b2_body->GetWorld()->DestroyBody(m_b2_body);
}

void IlluminatiConfirmed::experimental::BaseCharacter::updatePhysics(
    float deltaTime) {
  m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));
  // sprite.setRotation(m_body->GetAngle() * 180 / 3.14159265);
}

IlluminatiConfirmed::experimental::CharacterSouthPark::CharacterSouthPark(
    b2World *world, const sf::Texture *texture,
    const IlluminatiConfirmed::experimental::CharacterSpriteInfo &sprite_data)
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

    m_b2_joint_prism = static_cast<b2PrismaticJoint *>(world->CreateJoint(&jd));
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

void IlluminatiConfirmed::experimental::CharacterSouthPark::move(
    b2Vec2 velocity, float deltaTime) {
  BaseCharacter::move(velocity, deltaTime);

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

void IlluminatiConfirmed::experimental::CharacterSouthPark::draw(
    sf::RenderWindow &window) {
  BaseCharacter::draw(window);
}

void IlluminatiConfirmed::experimental::CharacterSouthPark::contact(
    b2Fixture *B) {
  LOG() << "I'am SouthParkBoys and I've begun the colliding with.. hz"
        << std::endl;
  UNUSE(B);
  //чекать с чем объект сталкивается
}

void IlluminatiConfirmed::experimental::CharacterSouthPark::endContact(
    b2Fixture *B) {
  LOG() << "I'am SouthParkBoys and I've dune the colliding with.. hz"
        << std::endl;
  UNUSE(B);
}

IlluminatiConfirmed::experimental::CharacterSouthPark::~CharacterSouthPark() {
  LOG() << "YOUUURRR HAVE KILLED KYLLLEEE!!/n";
}

void IlluminatiConfirmed::experimental::CharacterSouthPark::updatePhysics(
    float deltaTime) {
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

IlluminatiConfirmed::experimental::CharacterAlinasBoys::CharacterAlinasBoys(
    b2World *world, const sf::Texture *texture,
    const IlluminatiConfirmed::experimental::CharacterSpriteInfo &sprite_data)
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

void IlluminatiConfirmed::experimental::CharacterAlinasBoys::move(
    b2Vec2 velocity, float deltaTime) {
  BaseCharacter::move(velocity, deltaTime);
}

void IlluminatiConfirmed::experimental::CharacterAlinasBoys::draw(
    sf::RenderWindow &window) {
  BaseCharacter::draw(window);
}

void IlluminatiConfirmed::experimental::CharacterAlinasBoys::contact(
    b2Fixture *B) {
  LOG() << "I'am AlinasBoys and I've begun the colliding with.. hz"
        << std::endl;
}

void IlluminatiConfirmed::experimental::CharacterAlinasBoys::endContact(
    b2Fixture *B) {
  LOG() << "I'am AlinasBoys and I've done the colliding with.. hz" << std::endl;
}

IlluminatiConfirmed::experimental::CharacterAlinasBoys::~CharacterAlinasBoys() {
}

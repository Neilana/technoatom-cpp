#include "BaseCharacter.h"

using namespace IlluminatiConfirmed;

BaseCharacter::BaseCharacter(Type type, b2World &world,
                             const CharacterSpriteInfo &sprite_data)
    : m_type(type) {
  {
    b2BodyDef bd;
    bd.fixedRotation = true;
    bd.type = b2_dynamicBody;
    bd.position.Set(SfPointtoB2Point(sprite_data.x_position),
                    SfPointtoB2Point(sprite_data.y_position));
    bd.linearDamping = 1000.f;
    m_b2_base = world.CreateBody(&bd);

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
    m_b2_body = world.CreateBody(&bd);

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
  if ((int)currentFrame > front_rects.size() - 1)
    currentFrame = 0;
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

void BaseCharacter::draw(sf::RenderWindow &window) {
  m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));
  window.draw(m_sprite);
}

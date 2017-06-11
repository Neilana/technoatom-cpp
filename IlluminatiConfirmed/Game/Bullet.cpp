#include "Bullet.h"

using IlluminatiConfirmed::Bullet;

Bullet::Bullet(b2World *world, sf::Vector2f const pos, Direction direction,
               float damage, const std::string &spriteFile)
    : m_damage(damage) {
  m_texture.loadFromFile(spriteFile);
  m_sprite.setTexture(m_texture);
  m_sprite.setPosition(pos);
  m_sprite.setOrigin(10, 10);

  b2BodyDef body_def;

  body_def.type = b2_dynamicBody;
  body_def.fixedRotation = true; //пока что

  b2CircleShape circle_shape;
  // circle_shape.m_radius = 2.f;
  circle_shape.m_radius = 0.05;
  circle_shape.m_radius = m_sprite.getTexture()->getSize().y / 64;
  b2FixtureDef fixture;
  fixture.shape = &circle_shape;

  fixture.density = 1.0;
  fixture.friction = 0.0;
  fixture.restitution = 0.0; // Restitution measures how 'bouncy' a fixture is

  // m_body->SetLinearDamping(100.3f);
  //  m_body->SetAngularDamping(100.3f);
  float x, y, vx, vy;
  switch (direction) {
  case Direction::Right: {
    // m_body->SetLinearVelocity(b2Vec2(100.0, 0.0));
    x = pos.x / SCALE + 1;
    y = pos.y / SCALE;
    vx = 2.0;
    vy = 0.0;
    break;
  }
  case Direction::Left: {
    //    m_body->SetLinearVelocity(b2Vec2(-100.0, 0.0));
    x = pos.x / SCALE - 1;
    y = pos.y / SCALE;
    vx = -2.0;
    vy = 0.0;
    break;
  }
  case Direction::Up: {
    //      m_body->SetLinearVelocity(b2Vec2(0.0, -100.0));
    x = pos.x / SCALE;
    y = pos.y / SCALE - 1;
    vx = 0.0;
    vy = -2.0;
    break;
  }

  case Direction::Down: {
    x = pos.x / SCALE;
    y = pos.y / SCALE + 1;
    vx = 0.0;
    vy = 2.0;
    break;
  }
  }

  body_def.position.Set(x, y);
  m_body = world->CreateBody(&body_def);
  m_body->CreateFixture(&fixture);
  m_body->SetLinearVelocity(b2Vec2(vx, vy));

  // !!! ыыы наверно, силу надо бы по-другому высчитывать
  m_body->ApplyForce(b2Vec2(vx, vy), m_body->GetWorldCenter(), true);
  // m_body->SetAngularVelocity( -90 * 0.01745 );
}

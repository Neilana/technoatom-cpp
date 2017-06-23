#include "Base.h"

using namespace IlluminatiConfirmed;
using namespace experimental;

BaseInterface::BaseInterface(BaseInterface::TypeBase type)
    : m_b2_base(nullptr),
      m_b2_base_fixture(nullptr),
      m_type_base(type),
      is_dead(false) {
  LOG() << "Create base " << int(m_type_base) << std::endl;
}

bool BaseInterface::isDead() { return is_dead; }

float BaseInterface::getY() {
  return getFixtureWorldPosition(m_b2_base->GetFixtureList()).y;
}

BaseInterface::~BaseInterface() {
  m_b2_base->GetWorld()->DestroyBody(m_b2_base);
  LOG() << "Destroy base " << int(m_type_base) << std::endl;
}

Building::Building(b2World *world, const sf::Texture *texture,
                   Big_Object &&big_obj)
    : BaseMapsStuff(BUILDING) {
  {
    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.position.Set(SfPointtoB2Point(big_obj.body.m_rect.left +
                                     big_obj.body.m_rect.width / 2),
                    SfPointtoB2Point(big_obj.body.m_rect.top +
                                     big_obj.body.m_rect.height / 2));
    m_b2_base = world->CreateBody(&bd);

    b2PolygonShape polygon;
    polygon.SetAsBox(SfPointtoB2Point(big_obj.body.m_rect.width / 2),
                     SfPointtoB2Point(big_obj.body.m_rect.height / 2));

    b2FixtureDef fixture;
    fixture.friction = 1.f;
    fixture.density = 50.f;
    fixture.restitution = 0;
    fixture.isSensor = false;
    fixture.shape = &polygon;

    m_b2_base_fixture = m_b2_base->CreateFixture(&fixture);
    m_b2_base_fixture->SetUserData(this);
    LOG() << "Create building " << std::endl;
  }

  for (auto &&it : big_obj.rects_for_draw_sprites) {
    sf::Sprite little_sprite = sf::Sprite(*texture, it.first);
    little_sprite.setPosition(it.second.x, it.second.y);

    m_vec_sprite.push_back(std::move(little_sprite));
  }
}

void Building::move(b2Vec2 velocity, float deltaTime) {
  // nothing
}

void Building::draw(sf::RenderWindow &window) {
  for (auto &&it : m_vec_sprite) window.draw(it);
}

void Building::contact(b2Fixture *B) {
  //к примеру добавить дому хпшку и, когда она закончится, включать анимацию
  //взрыва перед смертью
}

void Building::endContact(b2Fixture *B) {}

Building::~Building() {
  LOG() << "Destroy building " << std::endl;
    /*m_b2_base->GetWorld()->DestroyBody(m_b2_base);*/ }

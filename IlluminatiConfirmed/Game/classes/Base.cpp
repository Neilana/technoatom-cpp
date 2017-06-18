#include "Base.h"

using namespace IlluminatiConfirmed;

MapsStuff::MapsStuff(const sf::Texture &texture, Big_Object &&big_obj,
                     b2World &world) : BaseInterface() {
  {
    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.position.Set(SfPointtoB2Point(big_obj.body.m_rect.left +
                                     big_obj.body.m_rect.width / 2),
                    SfPointtoB2Point(big_obj.body.m_rect.top +
                                     big_obj.body.m_rect.height / 2));
    m_b2_base = world.CreateBody(&bd);

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
  }

  for (auto &&it : big_obj.rects_for_draw_sprites) {
    sf::Sprite little_sprite;  // = sf::Sprite(texture, it.first);

    little_sprite.setTexture(texture);
    little_sprite.setTextureRect(it.first);
    little_sprite.setPosition(it.second.x, it.second.y);
    m_vec_sprite.push_back(little_sprite);
  }
}

void MapsStuff::move() {
  // nothing
}

void MapsStuff::draw(sf::RenderWindow &window) {
    for (auto && it :m_vec_sprite)
        window.draw(it);
}

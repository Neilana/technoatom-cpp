#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Box2D/Box2D.h"

#include "Level.h"
#include "constants.h"

namespace IlluminatiConfirmed {
class BaseInterface {
 public:
  virtual void draw(sf::RenderWindow &window) = 0;
  virtual void move() = 0;
  float getY() {
    return getFixtureWorldPosition(m_b2_base->GetFixtureList()).y;
  }

  virtual ~BaseInterface() {}

 protected:
  b2Body *m_b2_base;
  b2Fixture *m_b2_base_fixture;
};

class MapsStuff : public BaseInterface {
 public:
  MapsStuff(const sf::Texture &texture, Big_Object &&big_obj, b2World &world);
  void move() override;
  void draw(sf::RenderWindow &window) override;

  std::vector<sf::Sprite> m_vec_sprite;

 protected:
  // b2Body *m_b2_impassable_part;
  // b2Body *m_b2_passable_part;
};
}

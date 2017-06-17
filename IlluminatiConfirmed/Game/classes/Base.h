#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Box2D/Box2D.h"

#include "constants.h"

namespace IlluminatiConfirmed {
class BaseInterface {
 public:
  virtual void draw() = 0;
  virtual void move() = 0;
  virtual float getY() = 0;

  virtual ~BaseInterface() {}
};

class MapsStuff : public BaseInterface {
  MapsStuff(const sf::Texture &texture,
            const std::vector<sf::Rect<int>> &vec_rect)
      : BaseInterface() {}
  void draw() override {}
  void move() override {
    // nothing
  }
  float getY() override {
    return getFixtureWorldPosition(m_b2_passable_part->GetFixtureList()).y;
  }

  std::vector<sf::Sprite> m_vec_sprite;

 protected:
  b2Body *m_b2_impassable_part;
  b2Body *m_b2_passable_part;
};
}

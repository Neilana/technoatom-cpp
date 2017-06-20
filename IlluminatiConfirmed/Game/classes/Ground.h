#pragma once

#include "Level.h"

namespace IlluminatiConfirmed {

class Ground {
 public:
  Ground() {}
  Ground(const sf::Texture *texture, const Layer &layer);
  void draw_ground(sf::RenderWindow &window);

 private:
  std::vector<sf::Sprite> m_sprites;
};
}

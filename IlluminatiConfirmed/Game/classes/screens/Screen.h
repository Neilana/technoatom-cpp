#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "constants.h"

namespace IlluminatiConfirmed {
class Screen {
protected:
  // virtual void loadTitle() {};
  // virtual void loadBackground();
  //  sf::Color m_inactiveColor;
  //  sf::Color m_activeColor;

public:
  Screen() {}
  virtual ScreenName run(IlluminatiConfirmed::Game &game,
                         sf::RenderWindow &window) = 0;
  virtual ~Screen() {}
};
}

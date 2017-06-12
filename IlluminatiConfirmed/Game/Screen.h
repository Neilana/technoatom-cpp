#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "constants.h"

namespace IlluminatiConfirmed {
class Screen {
 private:
  // virtual void loadTitle() {};
  // virtual void loadBackground();
 public:
  Screen(){};
  virtual ScreenName run(IlluminatiConfirmed::Game &game,
                         sf::RenderWindow &window) = 0;
  virtual ~Screen(){};
};
}

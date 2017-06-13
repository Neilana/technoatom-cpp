#pragma once

#include "Screen.h"
#include "constants.h"

namespace IlluminatiConfirmed {
class ScreenGame : public IlluminatiConfirmed::Screen {
 public:
  ScreenGame();

  ScreenName run(IlluminatiConfirmed::Game &game, sf::RenderWindow &window);
  ~ScreenGame(){};
};
}

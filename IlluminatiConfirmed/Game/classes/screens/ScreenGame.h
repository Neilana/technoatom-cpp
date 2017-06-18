#pragma once

#include "Screen.h"
#include "constants.h"

namespace IlluminatiConfirmed {
class ScreenGame : public Screen {
public:
  ScreenGame();

  ScreenName run(Game &game, sf::RenderWindow &window);
  ~ScreenGame() {}
};
}

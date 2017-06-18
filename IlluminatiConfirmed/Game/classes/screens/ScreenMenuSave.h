#pragma once

#include "ScreenMenu.h"
#include "constants.h"

namespace IlluminatiConfirmed {
class ScreenMenuSave : public IlluminatiConfirmed::ScreenMenu {
public:
  ScreenMenuSave();
  ScreenName run(IlluminatiConfirmed::Game &game, sf::RenderWindow &window);
};
}

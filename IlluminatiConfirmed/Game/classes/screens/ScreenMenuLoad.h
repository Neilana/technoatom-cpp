#pragma once

#include "ScreenMenu.h"
#include "constants.h"

namespace IlluminatiConfirmed {
class ScreenMenuLoad : public IlluminatiConfirmed::ScreenMenu {
public:
  ScreenMenuLoad();
  ScreenName run(IlluminatiConfirmed::Game &game, sf::RenderWindow &window);
};
}

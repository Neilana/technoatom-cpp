#pragma once

#include "Screen.h"
#include "ScreenMenu.h"
#include "constants.h"
#include <map>

namespace IlluminatiConfirmed {
class ScreenMenuMain : public IlluminatiConfirmed::ScreenMenu {
private:
  //  int alpha_max;
  //  int alpha_div;
  bool playing;

  enum class MenuOptions {
    NewGame, // -> chose chars screen
    Continue,
    Save,
    Load,
    Exit
  };

  std::vector<sf::Text> m_menuOptions;

  int m_selectedOption;
  sf::Color m_unavailibleColor;
  std::map<int, ScreenName> m_screenNameByOption;

  // void initTitle();
  // void initBackground();
  void initMenuOptions();

public:
  ScreenMenuMain();

  ScreenName run(IlluminatiConfirmed::Game &game, sf::RenderWindow &window);
  ~ScreenMenuMain(){};
};
}

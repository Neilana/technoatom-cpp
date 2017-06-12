#pragma once

#include <map>
#include "Screen.h"
#include "constants.h"

namespace IlluminatiConfirmed {
class ScreenMenu : public IlluminatiConfirmed::Screen {
 private:
  //  int alpha_max;
  //  int alpha_div;
  bool playing;

  enum class MenuOptions {
    NewGame,  // -> chose chars screen
    Continue,
    Save,
    Load,
    Exit
  };

  sf::Font m_font;
  // int m_fontSize;
  // float m_deltaY;

  sf::Texture m_backgroundTexture;
  sf::Sprite m_backgroundSprite;
  std::vector<sf::Text> m_menuOptions;
  sf::Text m_title;

  int m_selectedOption;
  std::map<int, ScreenName> m_screenNameByOption;

  void initTitle();
  void initBackground();
  void initMenuOptions();

 public:
  ScreenMenu();

  ScreenName run(IlluminatiConfirmed::Game &game, sf::RenderWindow &window);
  ~ScreenMenu(){};
};
}

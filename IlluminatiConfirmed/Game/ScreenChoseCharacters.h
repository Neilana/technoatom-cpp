#pragma once

#include "Screen.h"

namespace IlluminatiConfirmed {
class ScreenChoseCharacters : public IlluminatiConfirmed::Screen {
 private:
  sf::Texture m_backgroundTexture;
  sf::Sprite m_backgroundSprite;
  sf::Font m_font;
  sf::Text m_title;

 public:
  ScreenChoseCharacters();

  ScreenName run(IlluminatiConfirmed::Game &game, sf::RenderWindow &window);
  ~ScreenChoseCharacters(){};
};
}

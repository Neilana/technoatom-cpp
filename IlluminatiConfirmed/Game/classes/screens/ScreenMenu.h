#pragma once
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Screen.h"
#include "constants.h"

namespace IlluminatiConfirmed {
class ScreenMenu : public Screen {
protected:
  sf::Color m_inactiveColor;
  sf::Color m_activeColor;
  sf::Color m_unavailibleColor;
  sf::Font m_font;
  // int m_fontSize;
  // float m_deltaY;
  sf::Text m_title;
  sf::Texture m_backgroundTexture;
  sf::Sprite m_backgroundSprite;

  void initBackground();
  void initTitle();

public:
  ScreenMenu()
      : m_inactiveColor(sf::Color(118, 161, 113)),
        m_activeColor(sf::Color(180, 231, 106)),
        m_unavailibleColor(sf::Color(173, 193, 177)){};
};
}

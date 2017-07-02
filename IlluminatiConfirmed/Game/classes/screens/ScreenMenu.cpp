#include "ScreenMenu.h"

using IlluminatiConfirmed::ScreenMenu;

void ScreenMenu::initBackground() {
  if (!m_backgroundTexture.loadFromFile(MENU_BACKGROUND_FILE)) {
    // std::cout << "Error loading presentation.gif" << std::endl;
    // return (-1);
  }
  m_backgroundSprite.setTexture(m_backgroundTexture);
  // sprite.setColor(sf::Color(255, 255, 255, alpha));
  if (!m_font.loadFromFile(FONT_FILE)) {
    // std::cerr << "Error loading verdanab.ttf" << std::endl;
    // return (-1);
  }
}

void ScreenMenu::initTitle() {
  float fontSize = 45;

  m_title.setFont(m_font);
  m_title.setCharacterSize(fontSize);
  // m_title.setString("Chose Characters");
  // m_title.setPosition(titleX, titleY);
  m_title.setColor(m_inactiveColor);

  // center text
  sf::FloatRect textRect = m_title.getLocalBounds();
  m_title.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
  m_title.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, 40));
}

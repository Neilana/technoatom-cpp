#pragma once

#include "Screen.h"

namespace IlluminatiConfirmed {
class ScreenChoseCharacters : public Screen {
 private:
  struct AvailableCharacter {
    sf::RectangleShape m_sprite;
    sf::Texture m_texture;
    AvailableCharacter(const std::string &fileName, int width, int height,
                       int x, int y) {
      m_sprite.setSize(sf::Vector2f(width, height));
      m_texture.loadFromFile(fileName);
      m_sprite.setTexture(&m_texture);
      m_sprite.setTextureRect(sf::Rect<int>(0, 0, width, height));
      m_sprite.setPosition(x, y);

      m_sprite.setOutlineColor(sf::Color::Green);
      m_sprite.setOutlineThickness(3);
    }
  };
  sf::Texture m_backgroundTexture;
  sf::Sprite m_backgroundSprite;
  sf::Font m_font;
  sf::Text m_title;
  sf::Texture texture;
  std::vector<std::shared_ptr<AvailableCharacter>> m_characters;

  void initTitle();
  void initBackground();
  void initMenuOptions();

  void showCharacters();

 public:
  ScreenChoseCharacters();

  ScreenName run(IlluminatiConfirmed::Game &game, sf::RenderWindow &window);
  ~ScreenChoseCharacters(){};
};
}

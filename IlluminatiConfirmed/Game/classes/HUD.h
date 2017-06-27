#pragma once

//#include "Weapons.h"
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace IlluminatiConfirmed {
class HUD {
  sf::RectangleShape m_characterSprite;

  sf::RectangleShape m_healthSprite;
  sf::RectangleShape m_healthSpriteSmall;
  sf::Texture m_healthTexture;
  std::vector<sf::Rect<int>> m_healthRects;

  sf::Text m_cartridges;
  sf::Font m_font;

  sf::RectangleShape m_weaponSprite;

  int m_x;
  int m_y;

  int m_healthSpriteSections;

  void setHealthSpriteRects();

public:
  HUD(const std::string &characterFile, const std::string &healthFile,
      int charWidth, int charHeight, int charSize);
  void updateHealthSprite(int healthPercents);
  void draw(sf::RenderWindow &window);
  void select() { m_characterSprite.setOutlineColor(sf::Color::Green); }
  void unselect() { m_characterSprite.setOutlineColor(sf::Color::Transparent); }
  void setBigHudPosition(float x, float y) {
    m_characterSprite.setPosition(x, y);
    m_healthSprite.setPosition(x + DEFAULT_SPRITE_SIZE_X + 3, y);
    m_weaponSprite.setPosition(x + DEFAULT_SPRITE_SIZE_X + 6,
                               y + BAR_HEIGHT + 3);
    m_cartridges.setPosition(x + DEFAULT_SPRITE_SIZE_X + 2, y + BAR_HEIGHT + 3);
  }
  void setSmallHudPosition(float x, float y) {
    m_healthSpriteSmall.setPosition(x, y);
  }

  void updateCartidges(int a) { m_cartridges.setString("111"); }

  void setWeapon(const sf::Texture *texture, sf::Rect<int> rect_with_weapon,
                 float width, float height) {

    //    m_weaponSprite = texture;
    //  m_weaponSprite.setPosition(500, 500);
    m_weaponSprite.setTexture(texture);
    m_weaponSprite.setTextureRect(rect_with_weapon);
    m_weaponSprite.setSize(sf::Vector2f(width, height));
    m_cartridges.setString("QString::number(10)");
  };
  //  void setSmallHudSize (int size) {m_healthSpriteSmall.setSize(); }
};
}

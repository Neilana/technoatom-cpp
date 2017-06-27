#include "HUD.h"
#include "Factories.h"

using namespace IlluminatiConfirmed;
using namespace IlluminatiConfirmed::experimental;

HUD::HUD(const std::string &characterFile, const std::string &healthFile,

         int charWidth, int charHeight, int charSize) {

  float x = 0.0;
  float y = 0.0;
  auto p_texture = FactoryObjects::Instance().getTexture(
      CHARACTERS_SPRITES_DIRECTORY + characterFile);

  m_characterSprite.setTexture(p_texture.get());
  m_characterSprite.setPosition(x, y);
  m_characterSprite.setSize(
      sf::Vector2f(DEFAULT_SPRITE_SIZE_X, DEFAULT_SPRITE_SIZE_Y));
  m_characterSprite.setTextureRect(sf::Rect<int>(0, 0, charWidth, charHeight));
  m_characterSprite.setOutlineThickness(3);
  m_characterSprite.setOutlineColor(sf::Color::Transparent);
  setHealthSpriteRects();

  auto texture = experimental::FactoryObjects::Instance().getTexture(
      BARS_SPRITES_DIRECTORY + healthFile);

  m_healthSprite.setTexture(texture.get());
  m_healthSprite.setSize(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));
  m_healthSprite.setTextureRect(m_healthRects[m_healthSpriteSections - 1]);
  m_healthSprite.setPosition(x + DEFAULT_SPRITE_SIZE_X + 4, y);

  m_healthSpriteSmall = m_healthSprite;
  // m_healthSpriteSmall.setTexture(texture.get());
  // m_healthSpriteSmall.setTextureRect(m_healthRects[m_healthSpriteSections
  // -
  // 1]);
  m_healthSpriteSmall.setSize(
      sf::Vector2f(charSize, BAR_HEIGHT * SMALL_BAR_SCALE));

  if (!m_font.loadFromFile(FONT_FILE))
    throw EXCEPTION("I can't open file with font.", nullptr);
  float fontSize = 10;
  m_cartridges.setFont(m_font);
  m_cartridges.setCharacterSize(fontSize);
  m_cartridges.setColor(sf::Color::White);
  m_cartridges.setString("123");
  m_cartridges.setPosition({0.0, 0.0});

  // m_healthSpriteSmall.setPosition(500.0, 500.0);

  // m_weaponSprite.setSize(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));

  // m_weaponSprite.setTexture(p_texture.get());
  // m_weaponSprite.setSize(sf::Vector2f(0, 10));
}
void HUD::setHealthSpriteRects() {
  m_healthSpriteSections = 6; // см картинки с ячейками здоровья

  int x = 0;
  int y = 0;
  int width = BAR_WIDTH;
  int height = BAR_HEIGHT;

  for (int i = 0; i < m_healthSpriteSections; i++) {
    m_healthRects.push_back({x, y, width, height});
    y += height + 2;
  }
}

void HUD::updateHealthSprite(int healthPercents) {
  int rectN = 0;
  if (healthPercents >= 80 && healthPercents <= 100)
    rectN = 5;
  else if (healthPercents >= 60 && healthPercents <= 80)
    rectN = 4;
  else if (healthPercents >= 40 && healthPercents <= 60)
    rectN = 3;
  else if (healthPercents >= 20 && healthPercents <= 40)
    rectN = 2;
  else if (healthPercents > 0 && healthPercents <= 20)
    rectN = 1;
  m_healthSprite.setTextureRect(m_healthRects[rectN]);
  m_healthSpriteSmall.setTextureRect(m_healthRects[rectN]);
};

void HUD::draw(sf::RenderWindow &window) {
  window.draw(m_healthSprite);
  window.draw(m_healthSpriteSmall);
  window.draw(m_characterSprite);
  window.draw(m_weaponSprite);

  if (!m_font.loadFromFile(FONT_FILE))
    throw EXCEPTION("I can't open file with font.", nullptr);
  float fontSize = 100.0;
  m_cartridges.setCharacterSize(fontSize);
  m_cartridges.setFont(m_font);
  // m_cartridges.setString("qqqq");
  m_cartridges.setPosition({800.0, 500.0});

  window.draw(m_cartridges);
}

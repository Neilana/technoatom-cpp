#pragma once

#include "Screen.h"
#include "ScreenMenu.h"

namespace IlluminatiConfirmed {
class ScreenChoseCharacters : public ScreenMenu {
 private:
  struct AvailableCharacter {
    sf::RectangleShape m_sprite;
    sf::Texture m_texture;
    std::vector<sf::Rect<int>> frontRects;
    int m_frames;
    int currentFrame;
    std::string m_name;
    int m_id;

    AvailableCharacter(int id, const std::string &fileName,
                       const std::string &name, int width, int height, int x,
                       int y, int frames) {
      m_sprite.setSize(
          sf::Vector2f(DEFAULT_SPRITE_SIZE_X, DEFAULT_SPRITE_SIZE_Y));
      m_texture.loadFromFile(fileName);
      m_sprite.setTexture(&m_texture);
      m_sprite.setTextureRect(sf::Rect<int>(0, 0, width, height));
      m_sprite.setPosition(x, y);

      m_sprite.setOutlineColor(sf::Color::Transparent);
      m_sprite.setOutlineThickness(3);
      m_frames = frames;
      for (int column = 0; column < m_frames; column++) {
        int row = 0;
        frontRects.push_back({column * width, height * row++, width, height});
      }
      m_id = id;
      currentFrame = 0;
      m_name = name;
    }
  };
  std::vector<std::shared_ptr<AvailableCharacter>> m_characters;

  int m_selectedCharId;
  std::set<int> m_chosedCharsIds;

  void showCharacters();
  void setChosedCharacters(float currentFrame);

 public:
  ScreenChoseCharacters();

  ScreenName run(IlluminatiConfirmed::Game &game, sf::RenderWindow &window);
  ~ScreenChoseCharacters() {}
};
}

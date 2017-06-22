#pragma once

#include "ScreenMenu.h"
#include "constants.h"

namespace IlluminatiConfirmed {
class ScreenMenuChoseMap : public IlluminatiConfirmed::ScreenMenu {
  struct AvailableMap {
    sf::RectangleShape m_sprite;
    sf::Texture m_texture;
    std::string m_name;
    std::string m_fileName;

    int m_id;

    AvailableMap(int id, const std::string &fileName,
                 const std::string &mapName, const std::string &previewFile,
                 int x, int y) {
      m_sprite.setSize(sf::Vector2f(MAP_SPRITE_SIZE, MAP_SPRITE_SIZE));
      m_texture.loadFromFile(previewFile);
      m_sprite.setTexture(&m_texture);
      // m_sprite.setTextureRect(sf::Rect<int>(0, 0, width, height));
      m_sprite.setPosition(x, y);

      m_sprite.setOutlineColor(sf::Color::Transparent);
      m_sprite.setOutlineThickness(6);

      m_id = id;
      m_name = mapName;
      m_fileName = fileName;
    }
  };

  std::vector<std::shared_ptr<AvailableMap>> m_maps;
  int m_selectedMapId;

 public:
  ScreenMenuChoseMap();
  ScreenName run(IlluminatiConfirmed::Game &game, sf::RenderWindow &window);
  void showMaps();
};
}

#pragma once

#include "tinyxml2.h"
#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <vector>

#define DEBUG_ON
#if defined(DEBUG_ON)
#define LOG() std::cout
#else
#define LOG() LOGGER("level")
#endif

namespace IlluminatiConfirmed {
struct Layer {
  int m_opacity;
  std::string m_name;
  std::map<int, std::pair<sf::Rect<int>, sf::Vector2i>> m_sub_rects;
};

struct Object {
  std::string m_name;
  std::string m_type;
  sf::Rect<int> m_rect;
};

struct MapInfo {
  sf::Vector2i tile_size;
  sf::Vector2i map_size_by_tile;
  int m_firstTileId, m_columns, m_rows;
  /*!
   * \brief operator == for tests
   * \param rhs
   */
  bool operator==(const MapInfo &rhs) const {
    return (tile_size == rhs.tile_size) &&
           (map_size_by_tile == rhs.map_size_by_tile) &&
           (m_firstTileId == rhs.m_firstTileId) &&
           (m_columns == rhs.m_columns) && (m_rows == rhs.m_rows);
  }
};

class Level {
public:
  void loadMapFromFile(const std::string &filename);

  const std::vector<Object> &
  GetVecObjectsByNameOfGroup(const std::string &name);

  const Layer &GetLayerByName(const std::string &name);
  std::vector<std::vector<std::pair<sf::Rect<int>, sf::Vector2i>>>
  GetVecOfRectsByNameOfObjsGroupAndLayer(const std::string &name_obj_gr,
                                         const std::string &name_layer);
  sf::Vector2i GetTileSize();
  MapInfo GetMapInfo();

private:
  void loadMapInfoFromFile(tinyxml2::XMLDocument &levelFile);
  void loadLayersFromFile(tinyxml2::XMLDocument &levelFile);
  void loadObjectsFromFile(tinyxml2::XMLDocument &levelFile);
  int m_width, m_height, m_tileWidth, m_tileHeight, m_firstTileId, m_columns,
      m_rows;
  std::string m_name_of_tileset;
  std::map<std::string, std::vector<Object>> m_objects_by_name_group;
  std::vector<Layer> m_layers;
};
}

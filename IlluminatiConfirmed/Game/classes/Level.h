#pragma once

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

#include <map>
#include <string>
#include <vector>
#include "../Logger/Logger.h"



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
  /*!
   * \brief operator == for tests
   * \param rhs
   * \return
   */
  bool operator==(const Object &rhs) const {
#ifdef DEBUG_ON
    if (m_name == rhs.m_name && m_type == rhs.m_type && m_rect == rhs.m_rect)
      return true;
    else
      return false;
#endif
    return m_name == rhs.m_name && m_type == rhs.m_type && m_rect == rhs.m_rect;
  }
};

struct MapInfo {
  std::string m_name_of_tileset;
  sf::Vector2i tile_size;
  sf::Vector2i map_size_by_tile;
  int m_firstTileId, m_columns, m_rows;
  /*!
   * \brief operator == for tests
   * \param rhs
   */
  bool operator==(const MapInfo &rhs) const {
#ifdef DEBUG_ON
    if ((tile_size == rhs.tile_size) &&
        (map_size_by_tile == rhs.map_size_by_tile) &&
        (m_firstTileId == rhs.m_firstTileId) && (m_columns == rhs.m_columns) &&
        (m_rows == rhs.m_rows && m_name_of_tileset == rhs.m_name_of_tileset))
      return true;
    else
      return false;
#endif
    return (tile_size == rhs.tile_size) &&
           (map_size_by_tile == rhs.map_size_by_tile) &&
           (m_firstTileId == rhs.m_firstTileId) &&
           (m_columns == rhs.m_columns) && (m_rows == rhs.m_rows) && (m_name_of_tileset == rhs.m_name_of_tileset);
  }
};

struct Big_Object {
  Object sprite;
  Object body;
  std::vector<std::pair<sf::Rect<int>, sf::Vector2i>> rects_for_draw_sprites;

  /*!
   * \brief operator == for tests
   * \param rhs
   * \return
   */
  bool operator==(const Big_Object &rhs) const {
#ifdef DEBUG_ON
    if (sprite == rhs.sprite) {
      if (body == rhs.body) {
        if (rects_for_draw_sprites == rhs.rects_for_draw_sprites) {
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else {
      return false;
    }
#endif
    return sprite == rhs.sprite && body == rhs.body &&
           rects_for_draw_sprites == rhs.rects_for_draw_sprites;
  }
};

class Level {
 public:
  void loadMapFromFile(const std::string &filename);

  const std::vector<Object> &GetVecObjectsByNameOfGroup(
      const std::string &name);

  const Layer &GetLayerByName(const std::string &name);
  std::vector<Big_Object> GetVecOfBigObjs(const std::string &name_obj_gr,
                                          const std::string &name_sprite_gr,
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

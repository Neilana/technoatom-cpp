#pragma once

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

struct Object {
  int GetPropertyInt(const std::string &name);
  float GetPropertyFloat(const std::string &name);
  const std::string &GetPropertyString(const std::string &name);

  std::string name;
  std::string type;
  sf::Rect<int> rect;

  sf::Sprite sprite;
  std::map<std::string, std::string> properties;
};

struct Layer {
  int opacity;
  std::vector<sf::Sprite> tiles;
};

class Level {
 public:
  void LoadFromFile(std::string filename);
  Object GetObject(const std::string &name);
  std::vector<Object> GetObjects(const std::string &name);
  void Draw(sf::RenderWindow &window);
  sf::Vector2i GetTileSize();

 private:
  int m_width, m_height, m_tileWidth, m_tileHeight;
  int firstTileID;
  sf::Rect<float> m_drawingBounds;
  sf::Texture m_tilesetImage;
  std::vector<Object> m_objects;
  std::vector<Layer> m_layers;
};

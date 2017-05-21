#pragma once

#include <SFML/Graphics.hpp>
#include "libs/tinyxml/tinyxml2.h"

#include <map>
#include <string>
#include <vector>

#define DEBUG_ON
#if defined(DEBUG_ON)
#define LOG() std::cout
#else
#define LOG() LOGGER("level")
#endif

//struct Object {
//    int GetPropertyInt(const std::string &name);
//    float GetPropertyFloat(const std::string &name);
//    const std::string &GetPropertyString(const std::string &name);

//    std::string m_name;
//    std::string m_type;
//    sf::Rect<int> m_rect;

//    sf::Sprite m_sprite;
//    std::map<std::string, std::string> m_properties;
//};

struct Layer {
    int m_opacity;
    std::vector<sf::Sprite> m_tiles;
};

struct Object {
    int GetPropertyInt(const std::string &name);
    float GetPropertyFloat(const std::string &name);
    const std::string &GetPropertyString(const std::string &name);

    std::string m_name;
    std::string m_type;
    sf::Rect<int> m_rect;

    sf::Sprite m_sprite;
    std::map<std::string, std::string> m_properties;
};

class Level {
public:

    void loadMapFromFile(const std::string &filename);
    void loadMapInfoFromFile(tinyxml2::XMLDocument &levelFile);
    void loadLayersFromFile(tinyxml2::XMLDocument &levelFile);
    void loadObjectsFromFile(tinyxml2::XMLDocument &levelFile);

    Object GetObject(const std::string &name);
    std::vector<Object> GetObjects(const std::string &name);
    void Draw(sf::RenderWindow &window);
    sf::Vector2i GetTileSize();

private:
    int m_width, m_height, m_tileWidth, m_tileHeight;
    int m_firstTileId;
    sf::Rect<float> m_drawingBounds;
    sf::Texture m_tilesetImage;
    std::vector<Object> m_objects;
    std::vector<Layer> m_layers;

    std::vector<sf::Rect<int>> m_subRects;
};

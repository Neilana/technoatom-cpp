#include "Level.h"

#include <iostream>
#include "../Logger/Logger.h"

// int Object::GetPropertyInt(const std::string &name) {
//    return std::stoi(m_properties.at(name));
//}

// float Object::GetPropertyFloat(const std::string &name) {
//    return std::stof(m_properties.at(name));
//}

// const std::string &Object::GetPropertyString(const std::string &name) {
//    return m_properties.at(name);
//}

void Level::loadMapInfoFromFile(tinyxml2::XMLDocument &levelFile) {
  // Работаем с контейнером map
  tinyxml2::XMLElement *map;
  map = levelFile.FirstChildElement("map");

  m_width = std::stoi(map->Attribute("width"));
  m_height = std::stoi(map->Attribute("height"));
  m_tileWidth = std::stoi(map->Attribute("tilewidth"));
  m_tileHeight = std::stoi(map->Attribute("tileheight"));

  // Берем описание тайлсета и идентификатор первого тайла
  tinyxml2::XMLElement *tilesetElement;
  tilesetElement = map->FirstChildElement("tileset");
  m_firstTileId = atoi(tilesetElement->Attribute("firstgid"));

  // source - путь до картинки в контейнере image
  tinyxml2::XMLElement *image;
  image = tilesetElement->FirstChildElement("image");

  std::string imagePath = "../Game/maps/";
  imagePath += image->Attribute("source");

  // Пытаемся загрузить тайлсет
  sf::Image img;

  if (!img.loadFromFile(imagePath)) {
    LOG() << "Failed to load tile sheet.\n";
  }

  // Очищаем карту от света (109, 159, 185)
  img.createMaskFromColor(sf::Color(109, 159, 185));
  // Грузим текстуру из изображения
  m_tilesetImage.loadFromImage(img);
  // Расплывчатость запрещена
  m_tilesetImage.setSmooth(false);
}

void Level::loadLayersFromFile(tinyxml2::XMLDocument &levelFile) {
  // Получаем количество столбцов и строк тайлсета
  int columns = int(m_tilesetImage.getSize().x) / m_tileWidth;
  int rows = int(m_tilesetImage.getSize().y) / m_tileHeight;

  // Вектор из прямоугольников изображений (TextureRect)
  // std::vector<sf::Rect<int>> m_subRects;

  for (int y = 0; y < rows; y++)
    for (int x = 0; x < columns; x++) {
      m_subRects.push_back(sf::Rect<int>(x * m_tileWidth, y * m_tileHeight,
                                         m_tileWidth, m_tileHeight));
    }

  // Работа со слоями
  tinyxml2::XMLElement *map;
  map = levelFile.FirstChildElement("map");

  tinyxml2::XMLElement *layerElement;
  layerElement = map->FirstChildElement("layer");
  while (layerElement) {
    Layer layer;

    // Если присутствует opacity, то задаем прозрачность слоя, иначе он
    // полностью непрозрачен
    if (layerElement->Attribute("opacity") != NULL) {
      float opacity = std::stof(layerElement->Attribute("opacity"));
      layer.m_opacity = int(255 * opacity);
    } else {
      layer.m_opacity = 255;
    }

    // Контейнер <data>
    tinyxml2::XMLElement *layerDataElement;
    layerDataElement = layerElement->FirstChildElement("data");

    if (layerDataElement == NULL) {
      LOG() << "Bad map. No layer information found.\n";
    }

    // Контейнер <tile> - описание тайлов каждого слоя
    tinyxml2::XMLElement *tileElement;
    tileElement = layerDataElement->FirstChildElement("tile");

    if (tileElement == NULL) {
      LOG() << "Bad map. No tile information found.\n";
    }

    int x = 0;
    int y = 0;

    while (tileElement) {
      long long tileGID = std::stoll(tileElement->Attribute("gid"));
      long long subRectToUse = tileGID - m_firstTileId;

      // Устанавливаем TextureRect каждого тайла
      if (subRectToUse >= 0) {
        if (m_subRects.size() > tileGID) {
          sf::Sprite sprite;
          sprite.setTexture(m_tilesetImage);
          sprite.setTextureRect(m_subRects.at(int(subRectToUse)));
          sprite.setPosition(x * m_tileWidth, y * m_tileHeight);
          sprite.setColor(sf::Color(255, 255, 255, layer.m_opacity));

          layer.m_tiles.push_back(sprite);
        } else {
          LOG() << "Something wrong with tile element: "
                << tileElement->Attribute("gid") << " on layer "
                << layerElement->Attribute("name") << ".\n";
        }
      }
      tileElement = tileElement->NextSiblingElement("tile");

      x++;
      if (x >= m_width) {
        x = 0;
        y++;
        if (y >= m_height) y = 0;
      }
    }
    m_layers.push_back(layer);

    layerElement = layerElement->NextSiblingElement("layer");
  }
}

void Level::loadObjectsFromFile(tinyxml2::XMLDocument &levelFile) {
  // Работа с объектами
  tinyxml2::XMLElement *objectGroupElement;

  tinyxml2::XMLElement *map;
  map = levelFile.FirstChildElement("map");

  // Если есть слои объектов
  if (map->FirstChildElement("objectgroup") != NULL) {
    objectGroupElement = map->FirstChildElement("objectgroup");
    while (objectGroupElement) {
      // Контейнер <object>
      tinyxml2::XMLElement *objectElement;
      objectElement = objectGroupElement->FirstChildElement("object");

      while (objectElement) {
        // Получаем все данные - тип, имя, позиция, etc
        std::string objectType;
        if (objectElement->Attribute("type") != NULL) {
          objectType = objectElement->Attribute("type");
        }
        std::string objectName;
        if (objectElement->Attribute("name") != NULL) {
          objectName = objectElement->Attribute("name");
        }
        int x = std::stoi(objectElement->Attribute("x"));
        int y = std::stoi(objectElement->Attribute("y"));

        int width, height;

        sf::Sprite sprite;
        sprite.setTexture(m_tilesetImage);
        sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));

        sprite.setPosition(x, y);

        if (objectElement->Attribute("width") != NULL) {
          width = atoi(objectElement->Attribute("width"));
          height = atoi(objectElement->Attribute("height"));
        } else {
          width = m_subRects
                      .at(std::stoi(objectElement->Attribute("gid")) -
                          m_firstTileId)
                      .width;
          height = m_subRects
                       .at(std::stoi(objectElement->Attribute("gid")) -
                           m_firstTileId)
                       .height;
          sprite.setTextureRect(m_subRects.at(
              std::stoi(objectElement->Attribute("gid")) - m_firstTileId));
        }

        if (objectElement->Attribute("gid") != NULL) {
          sprite.setTextureRect(m_subRects.at(
              std::stoi(objectElement->Attribute("gid")) - m_firstTileId));
        }

        // "Переменные" объекта
        tinyxml2::XMLElement *properties;
        properties = objectElement->FirstChildElement("properties");
        std::map<std::string, std::string> propertiesMap;
        if (properties != NULL) {
          tinyxml2::XMLElement *prop;
          prop = properties->FirstChildElement("property");
          if (prop != NULL) {
            while (prop) {
              std::string propertyName = prop->Attribute("name");
              std::string propertyValue = prop->Attribute("value");

              propertiesMap.insert(
                  {std::move(propertyName), std::move(propertyValue)});

              prop = prop->NextSiblingElement("property");
            }
          }
        }

        // Экземпляр объекта
        Object object = {std::move(objectName), std::move(objectType),
                         sf::Rect<int>(x, y, width, height), std::move(sprite),
                         propertiesMap};

        // Пихаем объект в вектор
        m_objects.push_back(std::move(object));

        objectElement = objectElement->NextSiblingElement("object");
      }
      objectGroupElement =
          objectGroupElement->NextSiblingElement("objectgroup");
    }
  } else {
    LOG() << "No object layers found...\n";
  }
}

void Level::loadMapFromFile(const std::string &filename) {
  tinyxml2::XMLDocument levelFile;
  // TiXmlDocument levelFile(filename.c_str());

  // Загружаем XML-файл с картой
  if (levelFile.LoadFile(filename.c_str())) {
    LOG() << "Loading level \"" << filename
          << "\" failed with message: " << levelFile.ErrorName() << "\n";
  }

  loadMapInfoFromFile(levelFile);  // загружаем основную инфу
  loadLayersFromFile(levelFile);   // загружаем слои
  loadObjectsFromFile(levelFile);  // загружаем объекты
}

Object Level::GetObject(const std::string &name) {
  // Только первый объект с заданным именем
  for (auto &&it : m_objects)
    if (it.m_name == name) return it;
  throw EXCEPTION("Unknown object", nullptr);
}

std::vector<Object> Level::GetObjectsByName(const std::string &name) {
  // Все объекты с заданным именем
  std::vector<Object> vec;
  for (auto &&it : m_objects)
    if (it.m_name == name) vec.push_back(it);
  return vec;
}

std::vector<Object> Level::GetObjectsByType(const std::string &type) {
  // Все объекты с заданным именем
  std::vector<Object> vec;
  for (auto &&it : m_objects)
    if (it.m_type == type) vec.push_back(it);
  return vec;
}

sf::Vector2i Level::GetTileSize() {
  return sf::Vector2i(m_tileWidth, m_tileHeight);
}

void Level::Draw(sf::RenderWindow &window) {
  // Рисуем все тайлы (объекты НЕ рисуем!)
  for (auto &&layer : m_layers)
    for (auto &&tile : layer.m_tiles) window.draw(tile);
}


#include "ScreenMenuChoseMap.h"
#include "GameDatabase.h"
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;
using IlluminatiConfirmed::ScreenMenuChoseMap;

ScreenMenuChoseMap::ScreenMenuChoseMap() {
  m_title.setString("Chose Map");
  initBackground();
  initTitle();

  showMaps();
  m_selectedMapId = 0;
  m_maps[0].get()->m_sprite.setOutlineColor(m_activeColor);
}

ScreenName ScreenMenuChoseMap::run(Game &game, sf::RenderWindow &window) {
  sf::Event event;
  //  bool running = true;
  ScreenName screen = ScreenName::ChoseMap;

  window.clear();

  // Drawing
  window.draw(m_backgroundSprite);
  window.draw(m_title);

  window.display();
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
          return ScreenName::MainMenu;
        }
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
          game.setMapFileName(m_maps[m_selectedMapId].get()->m_fileName);

          return ScreenName::ChoseCharacters;
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
          m_maps[m_selectedMapId].get()->m_sprite.setOutlineColor(
              sf::Color::Transparent);
          m_selectedMapId++;
          if (m_selectedMapId > m_maps.size() - 1)
            m_selectedMapId = 0;
          m_maps[m_selectedMapId].get()->m_sprite.setOutlineColor(
              m_activeColor);
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
          m_maps[m_selectedMapId].get()->m_sprite.setOutlineColor(
              sf::Color::Transparent);
          m_selectedMapId--;
          if (m_selectedMapId < 0)
            m_selectedMapId = m_maps.size() - 1;
          m_maps[m_selectedMapId].get()->m_sprite.setOutlineColor(
              m_activeColor);
        }
      }
      window.clear();
      window.draw(m_backgroundSprite);
      window.draw(m_title);
      for (auto &&it : m_maps)
        window.draw(it->m_sprite);

      window.display();
    }
  }

  return screen;
}

void ScreenMenuChoseMap::showMaps() {
  float startX = 140;
  float startY = 100;

  float x = startX;
  float y = startY;

  float deltaX = 40;
  float deltaY = MAP_SPRITE_SIZE + 10;

  GameDatabase db = GameDatabase::getInstance();
  QSqlQuery query;
  query.exec("SELECT * FROM Maps");
  while (query.next()) {
    int id = query.value(0).toInt();
    std::string fileName = query.value(1).toString().toStdString();
    std::string mapName = query.value(2).toString().toStdString();
    std::string previewImage = query.value(3).toString().toStdString();

    // fileName = MAP_DIRECTORY + fileName;
    previewImage = MAP_DIRECTORY + "/preview/" + previewImage;

    std::shared_ptr<AvailableMap> bufMap = std::make_shared<AvailableMap>(
        id, fileName, mapName, previewImage, x, y);

    m_maps.push_back(std::move(bufMap));

    x += MAP_SPRITE_SIZE + deltaX;
    if (x > WINDOW_WIDTH - startX)
      x = startX, y += deltaY;

    //  qDebug() << query.value(1).toString();
  }
}

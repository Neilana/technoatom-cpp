
#include "ScreenMenuChoseMap.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "GameDatabase.h"
#include "constants.h"

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
  for (auto &&it : m_maps) window.draw(it->m_sprite);
  //  window.display();

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
          return ScreenName::MainMenu;
        }
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
          game.setMapFileName(m_maps[m_selectedMapId].get()->m_fileName);

          // reset
          m_selectedMapId = 0;
          for (auto &&it : m_maps)
            it.get()->m_sprite.setOutlineColor(sf::Color::Transparent);
          m_maps[m_selectedMapId].get()->m_sprite.setOutlineColor(
              m_activeColor);
          return ScreenName::ChoseCharacters;
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
          m_maps[m_selectedMapId].get()->m_sprite.setOutlineColor(
              sf::Color::Transparent);
          m_selectedMapId++;
          if (m_selectedMapId > m_maps.size() - 1) m_selectedMapId = 0;
          m_maps[m_selectedMapId].get()->m_sprite.setOutlineColor(
              m_activeColor);
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
          m_maps[m_selectedMapId].get()->m_sprite.setOutlineColor(
              sf::Color::Transparent);
          m_selectedMapId--;
          if (m_selectedMapId < 0) m_selectedMapId = m_maps.size() - 1;
          m_maps[m_selectedMapId].get()->m_sprite.setOutlineColor(
              m_activeColor);
        }
      }
      window.clear();
      window.draw(m_backgroundSprite);
      window.draw(m_title);

      // имя выбранной карты
      sf::Text m_name;
      m_name.setFont(m_font);
      m_name.setCharacterSize(40);
      m_name.setString(m_maps[m_selectedMapId]->m_name);
      // m_name.setPosition(
      m_name.setColor(m_activeColor);

      // center text
      sf::FloatRect textRect = m_name.getLocalBounds();
      m_name.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
      m_name.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, 90));

      window.draw(m_name);

      for (auto &&it : m_maps) {
        window.draw(it->m_sprite);
      }

      window.display();
    }
  }

  return screen;
}

void ScreenMenuChoseMap::showMaps() {
  float startX = 140;
  float startY = 130;

  float x = startX;
  float y = startY;

  float deltaX = 40;
  float deltaY = MAP_SPRITE_SIZE + 40;

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
    if (x > WINDOW_WIDTH - startX) x = startX, y += deltaY;

    //  qDebug() << query.value(1).toString();
  }
}

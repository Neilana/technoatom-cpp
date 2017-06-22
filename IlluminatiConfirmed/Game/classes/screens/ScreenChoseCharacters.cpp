#include <SFML/Graphics.hpp>

#include "GameDatabase.h"
#include "ScreenChoseCharacters.h"

#include <string>

using namespace sf;
using namespace std;

using IlluminatiConfirmed::ScreenChoseCharacters;
using IlluminatiConfirmed::GameDatabase;

ScreenChoseCharacters::ScreenChoseCharacters() {
  m_title.setString("Chose Characters");

  initBackground();
  initTitle();

  // init
  showCharacters();
  m_selectedCharId = 0;
  m_characters[0].get()->m_sprite.setOutlineColor(m_activeColor);
}

ScreenName ScreenChoseCharacters::run(Game &game, sf::RenderWindow &window) {
  bool running = true;
  sf::Event event;
  window.clear();
  // sf::RectangleShape rectangle;
  Clock clock;

  window.draw(m_backgroundSprite);
  window.draw(m_title);
  for (auto &&it : m_characters) window.draw(it->m_sprite);

  // window.display();

  while (running && window.isOpen()) {
    auto timeSf = clock.restart();
    auto time = timeSf.asMicroseconds();
    time = time / 800;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
          return ScreenName::ChoseMap;
        }

        if (Keyboard::isKeyPressed(Keyboard::Return) &&
            m_chosedCharsIds.size() > 0) {
          // m_chosedCharsIds.insert(m_characters[m_selectedCharId].get()->m_id);
          game.initNewGame(m_chosedCharsIds, window);

          // reset
          m_selectedCharId = 0;
          for (auto it : m_characters)
            it.get()->m_sprite.setOutlineColor(sf::Color::Transparent);
          m_chosedCharsIds.clear();
          m_characters[m_selectedCharId].get()->m_sprite.setOutlineColor(
              m_activeColor);

          return ScreenName::Game;
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
          m_characters[m_selectedCharId].get()->m_sprite.setOutlineColor(
              sf::Color::Transparent);
          m_selectedCharId++;
          if (m_selectedCharId > m_characters.size() - 1) m_selectedCharId = 0;
          m_characters[m_selectedCharId].get()->m_sprite.setOutlineColor(
              m_activeColor);
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
          m_characters[m_selectedCharId].get()->m_sprite.setOutlineColor(
              sf::Color::Transparent);
          m_selectedCharId--;
          if (m_selectedCharId < 0) m_selectedCharId = m_characters.size() - 1;
          m_characters[m_selectedCharId].get()->m_sprite.setOutlineColor(
              m_activeColor);
        }

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
          if (m_chosedCharsIds.count(
                  m_characters[m_selectedCharId].get()->m_id) > 0) {
            m_chosedCharsIds.erase(m_characters[m_selectedCharId].get()->m_id);
          } else if (m_chosedCharsIds.size() < TEAM_MEMBERS_COUNT) {
            m_chosedCharsIds.insert(m_characters[m_selectedCharId].get()->m_id);
          }
        }
      }
    }
    float currentFrame;
    currentFrame += 0.005 * (float)time;
    if ((int)currentFrame > m_characters[m_selectedCharId].get()->m_frames - 1)
      currentFrame = 0;

    m_characters[m_selectedCharId].get()->m_sprite.setTextureRect(
        m_characters[m_selectedCharId].get()->frontRects[(int)currentFrame]);

    setChosedCharacters(currentFrame);

    window.draw(m_backgroundSprite);
    window.draw(m_title);

    // имя выбранного перса
    sf::Text m_name;
    m_name.setFont(m_font);
    m_name.setCharacterSize(40);
    m_name.setString(m_characters[m_selectedCharId]->m_name);
    // m_name.setPosition(
    m_name.setColor(m_activeColor);

    // center text
    sf::FloatRect textRect = m_name.getLocalBounds();
    m_name.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);
    m_name.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, 90));
    window.draw(m_name);

    for (auto &&it : m_characters) window.draw(it->m_sprite);

    window.display();
  }
}

void ScreenChoseCharacters::showCharacters() {
  float startX = 100;
  float startY = 130;

  float x = startX;
  float y = startY;

  float deltaX = 30;
  float deltaY = 100;

  GameDatabase db = GameDatabase::getInstance();
  QSqlQuery query;
  query.exec("SELECT * FROM CharactersImages");
  while (query.next()) {
    int id = query.value(0).toInt();
    std::string fileName = query.value(1).toString().toStdString();
    int width = query.value(2).toInt();
    int height = query.value(3).toInt();
    int frames = query.value(4).toInt();
    std::string name = query.value(5).toString().toStdString();

    fileName = CHARACTERS_SPRITES_DIRECTORY + fileName;

    std::shared_ptr<AvailableCharacter> bufCharacter =
        std::make_shared<AvailableCharacter>(id, fileName, name, width, height,
                                             x, y, frames);

    m_characters.push_back(std::move(bufCharacter));

    x += DEFAULT_SPRITE_SIZE_X + deltaX;
    if (x > WINDOW_WIDTH - startX) x = startX, y += deltaY;

    //  qDebug() << query.value(1).toString();
  }
}

void ScreenChoseCharacters::setChosedCharacters(float currentFrame) {
  int newFrame = int(currentFrame);

  for (auto &&it : m_characters) {
    if (m_chosedCharsIds.count(it->m_id) > 0) {
      it->m_sprite.setOutlineColor(m_inactiveColor);
      newFrame = currentFrame;

      if ((int)newFrame > it->m_frames - 1) newFrame = 0;

      it->m_sprite.setTextureRect(it->frontRects[newFrame]);
    }
  }
}

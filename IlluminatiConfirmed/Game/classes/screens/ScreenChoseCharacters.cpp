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
  sf::RectangleShape rectangle;
  Clock clock;
  std::set<int> ids;
  while (running) {

    auto timeSf = clock.restart();
    auto time = timeSf.asMicroseconds();
    time = time / 800;

    while (window.pollEvent(event)) {

      if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        return ScreenName::MainMenu;
      }

      if (Keyboard::isKeyPressed(Keyboard::Return)) {
        ids.insert(m_characters[m_selectedCharId].get()->m_id);
        game.initNewGame(MAP_FILE_1, ids);
        return ScreenName::Game;
      }

      if (Keyboard::isKeyPressed(Keyboard::Right)) {
        m_characters[m_selectedCharId].get()->m_sprite.setOutlineColor(
            sf::Color::Transparent);
        m_selectedCharId++;
        if (m_selectedCharId > m_characters.size() - 1)
          m_selectedCharId = 0;
        m_characters[m_selectedCharId].get()->m_sprite.setOutlineColor(
            m_activeColor);
      }

      if (Keyboard::isKeyPressed(Keyboard::Left)) {
        m_characters[m_selectedCharId].get()->m_sprite.setOutlineColor(
            sf::Color::Transparent);
        m_selectedCharId--;
        if (m_selectedCharId < 0)
          m_selectedCharId = m_characters.size() - 1;
        m_characters[m_selectedCharId].get()->m_sprite.setOutlineColor(
            m_activeColor);
      }
    }
    float currentFrame;
    currentFrame += 0.005 * (float)time;
    if ((int)currentFrame > m_characters[m_selectedCharId].get()->m_frames - 1)
      currentFrame = 0;

    m_characters[m_selectedCharId].get()->m_sprite.setTextureRect(
        m_characters[m_selectedCharId].get()->frontRects[(int)currentFrame]);

    window.draw(m_backgroundSprite);
    window.draw(m_title);
    for (auto &&it : m_characters)
      window.draw(it->m_sprite);

    window.display();
  }
}

void ScreenChoseCharacters::showCharacters() {
  float startX = 100;
  float startY = 100;

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

    fileName = CHARACTERS_SPRITES_DIRECTORY + fileName;

    std::shared_ptr<AvailableCharacter> bufCharacter =
        std::make_shared<AvailableCharacter>(id, fileName, width, height, x, y,
                                             frames);

    m_characters.push_back(std::move(bufCharacter));

    x += DEFAULT_SPRITE_SIZE_X + deltaX;
    if (x > WINDOW_WIDTH - startX)
      x = startX, y += deltaY;

    qDebug() << query.value(1).toString();
  }
}

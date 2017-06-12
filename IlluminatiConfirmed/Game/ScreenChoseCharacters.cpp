#include <SFML/Graphics.hpp>

#include "GameDatabase.h"
#include "ScreenChoseCharacters.h"

#include <string>

using namespace sf;
using namespace std;

using IlluminatiConfirmed::ScreenChoseCharacters;
using IlluminatiConfirmed::GameDatabase;
;

void ScreenChoseCharacters::initBackground() {
  if (!m_backgroundTexture.loadFromFile(
          "../Game/sprites/backgrounds/menu3_1.png")) {
    // std::cout << "Error loading presentation.gif" << std::endl;
    // return (-1);
  }
  m_backgroundSprite.setTexture(m_backgroundTexture);
  // sprite.setColor(sf::Color(255, 255, 255, alpha));
  if (!m_font.loadFromFile("../Game/res/Franchise-Bold-hinted.ttf")) {
    // std::cerr << "Error loading verdanab.ttf" << std::endl;
    // return (-1);
  }
}

void ScreenChoseCharacters::initTitle() {
  float titleX = WINDOW_WIDTH / 2.0 - 100;
  float titleY = 25;
  float fontSize = 45;

  m_title.setFont(m_font);
  m_title.setCharacterSize(fontSize);
  m_title.setString("Chose Characters");
  // m_title.setPosition(titleX, titleY);
  m_title.setColor(sf::Color::White);

  // center text
  sf::FloatRect textRect = m_title.getLocalBounds();
  m_title.setOrigin(textRect.left + textRect.width / 2.0f,
                    textRect.top + textRect.height / 2.0f);
  m_title.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, 40));
}

ScreenChoseCharacters::ScreenChoseCharacters() {
  initBackground();
  initTitle();

  // init

  showCharacters();

  //  texture.loadFromFile("../Game/sprites/characters/panda.png");
}

ScreenName ScreenChoseCharacters::run(Game &game, sf::RenderWindow &window) {
  bool running = true;
  sf::Event event;
  window.clear();
  sf::RectangleShape rectangle;

  while (running) {
    while (window.pollEvent(event)) {
      if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        return ScreenName::MainMenu;
      }

      if (Keyboard::isKeyPressed(Keyboard::Return)) {
        return ScreenName::Game;
      }
      window.draw(m_backgroundSprite);
      window.draw(m_title);
      for (auto &&it : m_characters) window.draw(it->m_sprite);

      rectangle.setSize(sf::Vector2f(64, 64));
      rectangle.setTexture(&texture);
      rectangle.setTextureRect(sf::Rect<int>(0, 0, 64, 64));
      // rectangle.setFillColor(sf::Color::Transparent);
      rectangle.setOutlineColor(sf::Color::Green);
      rectangle.setOutlineThickness(3);
      rectangle.setPosition(10, 20);
      window.draw(rectangle);

      window.display();
    }
  }
}

void ScreenChoseCharacters::showCharacters() {
  float startX = 100;
  float startY = 100;

  float x = startX;
  float y = startY;

  float deltaX = 30;
  float deltaY = 70;

  GameDatabase db = GameDatabase::getInstance();
  QSqlQuery query;
  query.exec("SELECT * FROM CharactersImages");
  while (query.next()) {
    std::string fileName = query.value(1).toString().toStdString();
    int width = query.value(2).toInt();
    int height = query.value(3).toInt();

    fileName = "../Game/sprites/characters/" + fileName;

    std::shared_ptr<AvailableCharacter> bufCharacter =
        std::make_shared<AvailableCharacter>(fileName, width, height, x, y);

    m_characters.push_back(std::move(bufCharacter));

    x += width + deltaX;
    if (x > WINDOW_WIDTH - startX) x = startX, y += deltaY;

    qDebug() << query.value(1).toString();
  }

  //  sf::Rect<float> a = m_characters[0].get()->m_sprite.getLocalBounds();
  //  a.setOutlineThickness(10);
  //  a.setOutlineColor(sf::Color(250, 150, 100));

  // sf::FloatRect a = m_characters[0].get()->m_sprite.getLocalBounds();
  // sf::RectangleShape rectangle(sf::Vector2f(120, 50));
}

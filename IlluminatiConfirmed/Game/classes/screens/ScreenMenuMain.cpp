#include "ScreenMenuMain.h"

#include "constants.h"

using IlluminatiConfirmed::ScreenMenuMain;

void ScreenMenuMain::initMenuOptions() {
  // float x = WINDOW_WIDTH / 2.0 - 50;
  float y = 250;

  float fontSize = 35;
  int deltaY = 35;

  m_selectedOption = 0;

  // 0
  sf::Text option;
  option.setFont(m_font);
  option.setCharacterSize(fontSize);
  option.setString("New Game");
  // option.setPosition(x, y);
  option.setColor(m_activeColor);

  // center text
  sf::FloatRect textRect = option.getLocalBounds();
  option.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
  option.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, y));

  m_menuOptions.push_back(option);
  m_screenNameByOption[0] = ScreenName::ChoseMap;

  // 1
  y += deltaY;

  option.setColor(m_inactiveColor);
  option.setString("Continue");
  // option.setPosition(x, y);
  option.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, y));

  m_menuOptions.push_back(option);
  m_screenNameByOption[1] = ScreenName::Game;

  //  // 1+1
  //  y += deltaY;

  //  option.setColor(m_inactiveColor);
  //  option.setString("Chose Map");
  //  // option.setPosition(x, y);
  //  option.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, y));

  //  m_menuOptions.push_back(option);
  //  m_screenNameByOption[2] = ScreenName::ChoseMap;

  // 2
  y += deltaY;
  // option.setColor(sf::Color::White);
  option.setString("Load");
  // option.setPosition(x, y);
  option.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, y));
  m_menuOptions.push_back(option);
  m_screenNameByOption[2] = ScreenName::Load;

  // 3
  y += deltaY;
  // option.setColor(sf::Color::White);
  option.setString("Save");
  // option.setPosition(x, y);
  option.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, y));
  m_menuOptions.push_back(option);
  m_screenNameByOption[3] = ScreenName::Save;

  // 4
  y += deltaY;
  option.setString("Exit");
  // option.setPosition(x, y);
  option.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, y));
  m_menuOptions.push_back(option);
  // m_screenByOption[0] = ScreenName::Game;
}

ScreenMenuMain::ScreenMenuMain() {
  //  alpha_max = 3 * 255;
  // alpha_div = 3;
  m_title.setString("Main Menu");

  initBackground();
  initMenuOptions();
  initTitle();

  playing = false;
}

ScreenName ScreenMenuMain::run(Game &game, sf::RenderWindow &window) {
  sf::Event Event;
  bool running = true;
  ScreenName screen = ScreenName::MainMenu;

  // рисуем первый раз, потом будем перерисовывать только если была нажата
  // кнопка
  // Clearing screen
  window.clear();
  // Drawing
  window.draw(m_backgroundSprite);
  window.draw(m_title);
  // рисуем пункты меню
  for (auto &&it : m_menuOptions)
    window.draw(it);
  window.display();

  while (running && window.isOpen()) {
    // Verifying events
    while (window.pollEvent(Event)) {
      // Window closed
      if (Event.type == sf::Event::Closed) {
        running = false;
        break;
        // return (-1);
      }
      // Key pressed
      if (Event.type == sf::Event::KeyPressed) {
        m_menuOptions[m_selectedOption].setColor(m_inactiveColor);
        switch (Event.key.code) {
        case sf::Keyboard::Up:
          m_selectedOption = m_selectedOption == 0 ? m_menuOptions.size() - 1
                                                   : m_selectedOption - 1;
          break;
        case sf::Keyboard::Down:
          m_selectedOption = m_selectedOption < m_menuOptions.size() - 1
                                 ? m_selectedOption + 1
                                 : 0;
          break;
        case sf::Keyboard::Return:

          if (m_selectedOption == m_menuOptions.size() - 1)
            window.close();
          // if (m_selectedOption == 1) screen = ScreenName::Game;
          // if (m_selectedOption == 0)
          //  screen = ScreenName::ChoseCharacters;  // new game
          screen = m_screenNameByOption[m_selectedOption];
          running = false;

          break;
        default:
          break;
        }

        m_menuOptions[m_selectedOption].setColor(m_activeColor);

        // Clearing screen
        window.clear();

        // Drawing
        window.draw(m_backgroundSprite);
        window.draw(m_title);
        // рисуем пункты меню
        for (auto &&it : m_menuOptions)
          window.draw(it);
        window.display();
      }
    }
  }

  return screen;
}

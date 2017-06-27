#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"
#include "b2dJson.h"

#include <algorithm>
#include <iostream>

#include <QObject>
#include <QtCore>

#include "Factories.h"
#include "Game.h"
#include "GameDatabase.h"
#include "Weapons.h"

using namespace sf;
using namespace std;

using namespace IlluminatiConfirmed;

Game::Game(sf::RenderWindow &window) {
  m_world = std::make_shared<b2World>(b2Vec2({0.f, 0.f}));
  MyContactListener *listner = new MyContactListener;
  (*m_world).SetContactListener(listner);

  SFMLDebugDraw *debugDraw =
      new SFMLDebugDraw(window);  //утечка памяти, бокс не будет это удалять
  debugDraw->SetFlags(b2Draw::e_shapeBit + b2Draw::e_centerOfMassBit +
                      b2Draw::e_pairBit);
  m_world->SetDebugDraw(debugDraw);
  //"E:/Git_ver3000/technoatom-cpp/IlluminatiConfirmed/Game/resources/";
  m_running = false;
  m_mapFileName = MAP_DIRECTORY + DEFAULT_MAP_FILE;
}

void Game::initNewGame(std::set<int> ids, sf::RenderWindow &window) {
  m_heroes.clear();
  m_HUDs.clear();
  m_bullets.clear();
  // listner_of_bullets.clear();
  m_ground.reset();
  m_vector_of_objs.clear();
  m_bullets.clear();

  m_world.reset();
  m_world = std::make_unique<b2World>(b2Vec2({0.f, 0.f}));
  m_running = true;
  listner_of_bullets.setPointers(m_world.get(), &m_bullets, &m_vector_of_objs);

  auto ground_and_maps_stuff =
      experimental::FactoryObjects::Instance().create_map(
          MAP_DIRECTORY + m_mapFileName, m_world.get());

  m_ground = std::move(ground_and_maps_stuff.first);

  m_vector_of_objs.reserve(ground_and_maps_stuff.second.size() +
                           m_heroes.size());
  m_vector_of_objs.insert(m_vector_of_objs.end(),
                          ground_and_maps_stuff.second.begin(),
                          ground_and_maps_stuff.second.end());
  m_vector_of_objs.insert(m_vector_of_objs.end(), m_heroes.begin(),
                          m_heroes.end());

  initCharacters(ids);
  m_currentHeroId = m_heroes.size() - 1;

  b2_listner_collision = std::make_unique<MyContactListener>();

  m_world->SetContactListener(
      b2_listner_collision.get());  //не работает, здания имеют другой
  //базовый класс, крошится если оставить
  //прежний
  SFMLDebugDraw *debugDraw =
      new SFMLDebugDraw(window);  //утечка памяти, бокс не будет это удалять
  debugDraw->SetFlags(b2Draw::e_shapeBit + b2Draw::e_centerOfMassBit +
                      b2Draw::e_pairBit);
  (*m_world).SetDebugDraw(debugDraw);
}

void Game::initObjects(std::set<int> ids) {}

void Game::initCharacters(std::set<int> ids) {
  // float hudX = 40;
  // float hudY = 835;

  float hudX = 815;
  float hudY = 20;

  for (auto it : ids) {
    auto hero = experimental::FactoryObjects::Instance().create_character(
        it, m_world.get());

    // hud
    QString str =
        "SELECT * FROM CharactersImages WHERE Id=" + QString::number(it);
    QSqlQuery query;
    query.exec(str);
    while (query.next()) {
      std::string fileName = query.value(1).toString().toStdString();
      int width = query.value(2).toInt();
      int height = query.value(3).toInt();
      int frames = query.value(4).toInt();
      std::string healthBarFile = query.value(6).toString().toStdString();
      std::string master = query.value(7).toString().toStdString();
      int size = query.value(8).toInt();

      // auto bufHUD = std::make_shared<HUD>(
      //  HUD(fileName, healthBarFile, width, height, hudX, hudY));
      // hudX += DEFAULT_SPRITE_SIZE_X + BAR_WIDTH + 10;

      auto bufHud = static_pointer_cast<experimental::BaseCharacter>(hero)
                        .get()
                        ->getHud();
      bufHud->setBigHudPosition(hudX, hudY);
      hudY += DEFAULT_SPRITE_SIZE_Y + BAR_HEIGHT + 10;
      m_HUDs.push_back(std::move(bufHud));
    }

    auto hero2Character =
        static_pointer_cast<experimental::BaseCharacter>(hero);

    static bool type;
    std::unique_ptr<experimental::Weapon> weapon;
    if (type)
      weapon = experimental::FactoryObjects::FactoryObjects::Instance()
                   .create_weapon(experimental::WeaponType::AK);
    else
      weapon = experimental::FactoryObjects::FactoryObjects::Instance()
                   .create_weapon(experimental::WeaponType::BAZOOKA);
    type = !type;

    QObject::connect(weapon.get(), &experimental::Weapon::create_bullet,
                     &listner_of_bullets,
                     &experimental::ListnerWeapon::pushBullet);

    hero2Character->setWeapon(std::move(weapon));

    m_vector_of_objs.push_back(hero);
    m_heroes.push_back(static_pointer_cast<experimental::BaseCharacter>(hero));
  }
}

void Game::draw(sf::RenderWindow &window) {
  auto deleteEverythingDead = [](auto &vector) {
    vector.erase(std::remove_if(vector.begin(), vector.end(),
                                [](auto it) -> bool { return it->isDead(); }),
                 vector.end());
  };

  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;
  if (!backgroundTexture.loadFromFile("E:/Git_ver3000/technoatom-"
                                      "cpp/IlluminatiConfirmed/Game/resources/m"
                                      "aps/bars_backgrounds/3.png")) {
    // std::cout << "Error loading presentation.gif" << std::endl;
    // return (-1);
  }
  backgroundSprite.setTexture(backgroundTexture);
  backgroundSprite.setPosition(sf::Vector2f(800, 0));
  window.draw(backgroundSprite);

  m_ground->draw_ground(window);
  deleteEverythingDead(m_vector_of_objs);
  deleteEverythingDead(m_heroes);
  deleteEverythingDead(m_bullets);
  std::sort(m_vector_of_objs.begin(), m_vector_of_objs.end(),
            [](auto &&lhs, auto &&rhs) { return lhs->getY() < rhs->getY(); });
  for (auto &&it : m_vector_of_objs) {
    it->draw(window);
  }

  // for (auto &&it : m_HUDs) {
  //  it->draw(window);
  //}
}

void Game::initPhysics() {}

void Game::updatePhysics(float time) {
  m_world->Step(1 / 60.f, 8, 3);
  for (auto &&it : m_heroes)
    it->updatePhysics(time);  //я не понимаю зачем нужен этот метод)
  for (auto &&it : m_bullets) it->move({0, 0}, time);
  //  static bool k = 1;
  //  if (k) {
  //    k = false;

  //  b2dJson json(false);

  //  std::string str = json.writeToString(m_world.get());
  //  std::string err;
}

void Game::saveGame(const std::string &fileName) {}

void Game::loadGame(const std::string &fileName) {}

void Game::setMapFileName(const std::string &fileName) {
  m_mapFileName = fileName;
}

void Game::setNewWeapon(
    const std::shared_ptr<experimental::BaseCharacter> &hero) {
  std::unique_ptr<experimental::Weapon> weapon;
  static bool type;
  if (type)
    weapon =
        experimental::FactoryObjects::FactoryObjects::Instance().create_weapon(
            experimental::WeaponType::AK);
  else
    weapon =
        experimental::FactoryObjects::FactoryObjects::Instance().create_weapon(
            experimental::WeaponType::BAZOOKA);
  type = !type;

  QObject::connect(weapon.get(), &experimental::Weapon::create_bullet,
                   &listner_of_bullets,
                   &experimental::ListnerWeapon::pushBullet);

  hero->setWeapon(std::move(weapon));
}

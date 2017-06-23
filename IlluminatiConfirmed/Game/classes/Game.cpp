#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"

#include "b2dJson.h"

#include <iostream>

#include "Factories.h"
#include "Game.h"
#include "GameDatabase.h"
#include "MyContactListener.h"

using namespace sf;
using namespace std;

using namespace IlluminatiConfirmed;

Game::Game(sf::RenderWindow &window) {
  m_world = std::make_shared<b2World>(b2Vec2({0.f, 0.f}));
  //MyContactListener *listner = new MyContactListener;
  // m_world->SetContactListener(listner);
  SFMLDebugDraw *debugDraw =
      new SFMLDebugDraw(window);  //утечка памяти, бокс не будет это удалять
  debugDraw->SetFlags(b2Draw::e_shapeBit + b2Draw::e_centerOfMassBit +
                      b2Draw::e_pairBit);
  m_world->SetDebugDraw(debugDraw);

  p_texture = std::make_shared<sf::Texture>();

  p_texture->loadFromFile(
      "E:/Git_ver3000/technoatom-cpp/IlluminatiConfirmed/Game/resources/"
      "sprites/characters/Kyle.png");
  listner_of_bullets =
      experimental::ListnerWeapon(m_world.get(), &m_bullets, &m_vector_of_objs);
}

void Game::initNewGame(const std::string &map_puth, const std::string &file) {
  auto ground_and_maps_stuff = experimental::FactoryObjects::create_map(
      MAP__DIRECTORY + MAP_FILE, m_world.get());

  m_ground = std::move(ground_and_maps_stuff.first);
  //хз, мб надо присвоить, новая жи игра

  m_vector_of_objs.clear();
  m_vector_of_objs.reserve(ground_and_maps_stuff.second.size() +
                           m_heroes.size());
  m_vector_of_objs.insert(m_vector_of_objs.end(),
                          ground_and_maps_stuff.second.begin(),
                          ground_and_maps_stuff.second.end());
  m_vector_of_objs.insert(m_vector_of_objs.end(), m_heroes.begin(),
                          m_heroes.end());
  auto hero =
      experimental::FactoryObjects::create_character("4", m_world.get());
  m_vector_of_objs.push_back(hero);
  m_heroes.push_back(static_pointer_cast<experimental::BaseCharacter>(hero));

  auto hero2 = std::static_pointer_cast<experimental::BaseInterface>(
      std::make_shared<experimental::CharacterSouthPark>(
          m_world.get(), p_texture.get(),
          experimental::CharacterSpriteInfo({192, 192, 192, 2, 300, 300})));
  auto hero2Character = static_pointer_cast<experimental::BaseCharacter>(hero2);

  sf::Texture *text_weapon = new sf::Texture();
  LOG() << "Result: "
        << text_weapon->loadFromFile(
               "E:/Git_ver3000/technoatom-cpp/IlluminatiConfirmed/Game/"
               "resources/sprites/bullets/ak.png")
        << std::endl;

  experimental::Weapon *weapon =
      new experimental::Weapon(text_weapon,
                               {experimental::TypeBullet::ROCKET,
                                {0, 0, 604, 187},
                                {607, 0, 727, 187},
                                10,
                                0.3f});
  listner_of_bullets.addWeapon(weapon);
  hero2Character->setWeapon(weapon);
  m_vector_of_objs.push_back(hero2);

  m_heroes.push_back(hero2Character);

  {
    //    p_texture_bullet = experimental::FactoryObjects::getTexture(
    //        "E:/Git_ver3000/technoatom-cpp/IlluminatiConfirmed/Game/"
    //        "resources/sprites/bullets/ak.png");

    //    auto bullet = std::make_shared<experimental::Bullet>(
    //        m_world.get(), p_texture_bullet.get(),
    //        experimental::BulletInfo({{{0, 0, 604, 187}}, 0.1f, 10, 0.01f, 1,
    //        1}));

    //    bullet->setTransform({{2.f, 10.f}, {0.5, 0.5}});
    //    m_bullets.push_back(bullet);
    //    m_vector_of_objs.push_back(std::move(bullet));
  }
}

void Game::initObjects(std::set<int> ids) {}

void Game::draw(sf::RenderWindow &window) {
  // рисуем землю
  m_ground->draw_ground(window);

  std::sort(m_vector_of_objs.begin(), m_vector_of_objs.end(),
            [](auto &&lhs, auto &&rhs) { return lhs->getY() < rhs->getY(); });

  for (auto &&it : m_vector_of_objs) {
    it->draw(window);
  }
}

void Game::initPhysics() {
  // sf::Vector2i tileSize = m_level.GetTileSize();

  // загружаем в Box2D стены
  // std::vector<Object> walls = m_level.GetObjectsByType("Wall");
  // buildBarriers(walls);

  // загружаем здания
  // walls = m_level.GetObjectsByType("Building");
  // buildBarriers(walls);
}

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

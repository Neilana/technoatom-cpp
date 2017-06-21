#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"
#include <SFML/Graphics.hpp>

#include <algorithm>

#include "b2dJson.h"

#include <iostream>

#include "CharacterAlinasBoys.h"
#include "Factories.h"
#include "Game.h"
#include "GameDatabase.h"
#include "MyContactListener.h"

using namespace sf;
using namespace std;

using namespace IlluminatiConfirmed;

Game::Game(sf::RenderWindow &window) {

  m_currentHeroId = 0;
  m_running = false;
  //  m_world = std::make_unique<b2World>(b2Vec2({0.f, 0.f}));

  //  MyContactListener *listner = new MyContactListener;
  //  // m_world.SetContactListener(listner);  //не работает, здания имеют
  //  другой
  //  //базовый класс, крошится если оставить
  //  //прежний
  //  SFMLDebugDraw *debugDraw =
  //      new SFMLDebugDraw(window); //утечка памяти, бокс не будет это удалять
  //  debugDraw->SetFlags(b2Draw::e_shapeBit + b2Draw::e_centerOfMassBit +
  //                      b2Draw::e_pairBit);
  //  (*m_world).SetDebugDraw(debugDraw);
}

// void Game::initNewGame(const std::string &map_puth, const std::string &file,
//                        std::set<int> ids, sf::RenderWindow &window) {
//   m_world.release();
//   m_world = std::make_unique<b2World>(b2Vec2({0.f, 0.f}));
//   m_running = true;
//   Level level;

//   level.loadMapFromFile(map_puth + file);

//   m_texture.loadFromFile(map_puth + level.GetMapInfo().m_name_of_tileset);
//   m_ground = Ground(m_texture, level.GetLayerByName(LAYER_GROUND));

//   auto big_objs =
//       level.GetVecOfBigObjs(OBJECT_SPRITE, OBJECT_BODY, LAYER_BUILDINGS);

//   int j = 0;
//   for (auto &&it : big_objs) {
//     if (j == 0) {
//       auto temp = experimental::Building(*m_world, m_texture, std::move(it));
//       m_vec_map.push_back(temp);
//     }
//     j = 1;
//   }
//   m_bullets.clear();
//   m_heroes.clear();

//   MyContactListener *listner = new MyContactListener;
//   // m_world.SetContactListener(listner);  //не работает, здания имеют другой
//   //базовый класс, крошится если оставить
//   //прежний
//   SFMLDebugDraw *debugDraw =
//       new SFMLDebugDraw(window); //утечка памяти, бокс не будет это удалять
//   debugDraw->SetFlags(b2Draw::e_shapeBit + b2Draw::e_centerOfMassBit +
//                       b2Draw::e_pairBit);
//   (*m_world).SetDebugDraw(debugDraw);

//   initCharacters(ids); // загружаем персонажей
//   initPhysics();
// =======
//   m_world = std::make_shared<b2World>(b2Vec2({0.f, 0.f}));
//   MyContactListener *listner = new MyContactListener;
//   // m_world->SetContactListener(listner);
//   SFMLDebugDraw *debugDraw =
//       new SFMLDebugDraw(window); //утечка памяти, бокс не будет это удалять
//   debugDraw->SetFlags(b2Draw::e_shapeBit + b2Draw::e_centerOfMassBit +
//                       b2Draw::e_pairBit);
//   m_world->SetDebugDraw(debugDraw);
// }

void Game::initNewGame(const std::string &map_puth, const std::string &file,
                       std::set<int> ids, sf::RenderWindow &window) {

  m_heroes.clear();
  m_ground.reset();
  m_vector_of_objs.clear();

  m_world.reset();
  m_world = std::make_unique<b2World>(b2Vec2({0.f, 0.f}));
  m_running = true;

  auto ground_and_maps_stuff = experimental::FactoryObjects::create_map(
      MAP__DIRECTORY + MAP_FILE, m_world.get());

  // m_ground = ground_and_maps_stuff.first;
  m_ground = std::move(ground_and_maps_stuff.first);
  //хз, мб надо присвоить, новая жи игра

  m_vector_of_objs.reserve(ground_and_maps_stuff.second.size() +
                           m_heroes.size());
  m_vector_of_objs.insert(m_vector_of_objs.end(),
                          ground_and_maps_stuff.second.begin(),
                          ground_and_maps_stuff.second.end());
  m_vector_of_objs.insert(m_vector_of_objs.end(), m_heroes.begin(),
                          m_heroes.end());

  initCharacters(ids);

  MyContactListener *listner = new MyContactListener;
  // m_world.SetContactListener(listner);  //не работает, здания имеют другой
  //базовый класс, крошится если оставить
  //прежний
  SFMLDebugDraw *debugDraw =
      new SFMLDebugDraw(window); //утечка памяти, бокс не будет это удалять
  debugDraw->SetFlags(b2Draw::e_shapeBit + b2Draw::e_centerOfMassBit +
                      b2Draw::e_pairBit);
  (*m_world).SetDebugDraw(debugDraw);
}

void Game::initObjects(std::set<int> ids) {}

void Game::initCharacters(std::set<int> ids) {
  for (auto it : ids) {
    auto hero =
        experimental::FactoryObjects::create_character(it, m_world.get());

    //  auto hero = experimental::FactoryObjects::create_character("13",
    //                                                             m_world.get());
    m_vector_of_objs.push_back(hero);
    m_heroes.push_back(static_pointer_cast<experimental::BaseCharacter>(hero));
  }
}

void Game::draw(sf::RenderWindow &window) {
  // рисуем землю
  // <<<<<<< HEAD
  //   m_ground.draw_ground(window);

  //   //рисуем здания
  //   for (auto &&it : m_vec_map) {
  //     it.draw(window);
  //   }

  //   // рисуем всех персонажей
  //   for (auto &&it : m_heroes)
  //     it->draw(window);

  //   // рисуем пули
  //   for (auto &&it : m_bullets)
  //     it->draw(window);
  // =======
  m_ground->draw_ground(window);

  std::sort(m_vector_of_objs.begin(), m_vector_of_objs.end(),
            [](auto &&lhs, auto &&rhs) { return lhs->getY() < rhs->getY(); });
  //>>>>>>> task7_kyle3

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
    it->updatePhysics(time); //я не понимаю зачем нужен этот метод)

  //  b2dJson json(false);

  //  std::string str = json.writeToString(m_world.get());
  //  std::string err;
}

void Game::saveGame(const std::string &fileName) {}

void Game::loadGame(const std::string &fileName) {}

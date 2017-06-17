#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"
#include <SFML/Graphics.hpp>

#include "b2dJson.h"

#include <iostream>

#include "CharacterAlinasBoys.h"
#include "Game.h"
#include "MyContactListener.h"

using namespace sf;
using namespace std;

using namespace IlluminatiConfirmed;

Game::Game(sf::RenderWindow &window) : m_world(b2Vec2(0.0f, 0.0f)) {
  m_currentHeroId = 0;

  MyContactListener *listner = new MyContactListener;
  m_world.SetContactListener(listner);
  SFMLDebugDraw *debugDraw =
      new SFMLDebugDraw(window); //утечка памяти, бокс не будет это удалять
  debugDraw->SetFlags(b2Draw::e_shapeBit + b2Draw::e_centerOfMassBit +
                      b2Draw::e_pairBit);
  m_world.SetDebugDraw(debugDraw);
}

void Game::initNewGame(const std::string &mapFile) {
  m_level.loadMapFromFile(mapFile); // загружаем карту
  initCharacters();                 // загружаем персонажей
  initPhysics();
}

void Game::initCharacters() {
  m_heroes.push_back(std::static_pointer_cast<BaseCharacter>(
      std::make_shared<CharacterAlinasBoys>(
          m_world, CharacterSpriteInfo(
                       {"../Game/resources/sprites/characters/demon2.png", 64,
                        48, 48, 4, 100, 100}))));

  m_heroes.push_back(std::static_pointer_cast<BaseCharacter>(
      std::make_shared<CharacterAlinasBoys>(
          m_world,
          CharacterSpriteInfo({"../Game/resources/sprites/characters/panda.png",
                               32, 32, 32, 3, 200, 200}))));

  m_heroes.push_back(std::static_pointer_cast<BaseCharacter>(
      std::make_shared<CharacterAlinasBoys>(
          m_world, CharacterSpriteInfo(
                       {"../Game/resources/sprites/characters/spider1.png", 64,
                        64, 64, 10, 300, 300}))));

  m_heroes.push_back(std::static_pointer_cast<BaseCharacter>(
      std::make_shared<CharacterSouthPark>(
          m_world,
          CharacterSpriteInfo({"../Game/resources/sprites/characters/kyle.png",
                               192, 192, 64, 2, 400, 400}))));
}

void Game::draw(sf::RenderWindow &window) {
  window.clear();

  // рисуем карту
  m_level.Draw(window);

  // рисуем всех персонажей
  for (auto &&it : m_heroes)
    it->draw(window);

  // рисуем пули
  for (auto &&it : m_bullets)
    it->draw(window);

  // дебаг
  // m_world.Dump();
}

void Game::initPhysics() {
  // sf::Vector2i tileSize = m_level.GetTileSize();

  // загружаем в Box2D стены
  std::vector<Object> walls = m_level.GetObjectsByType("Wall");
  buildBarriers(walls);

  // загружаем здания
  walls = m_level.GetObjectsByType("Building");
  buildBarriers(walls);
}

void Game::updatePhysics() {
  m_world.Step(1 / 60.f, 8, 3);

  //  b2dJson json(false);

  // std::string str = json.writeToString(&m_world);
  // std::string err;

  // json.readFromString(str, err, &m_world);

  // LOG() << err << std::endl;

  // for (auto &&it : m_heroes) it->updatePhysics();
  // for (auto &&it : m_bullets)
  // it->updatePhysics();
  // m_bullets.remove_if([](auto &i) { return i->hasStopped(); });
}

void Game::buildBarriers(std::vector<Object> &walls) {
  for (size_t i = 0; i < walls.size(); i++) {
    b2PolygonShape polygonShape;

    // fixture definition
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;
    myFixtureDef.density = 1;

    // a static body
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);
    b2Body *staticBody = m_world.CreateBody(&myBodyDef);

    // add four walls to the static body
    polygonShape.SetAsBox(
        walls[i].m_rect.width / 64.0,
        walls[i].m_rect.height / 64.0, // 64 - потому что сначала мы делим на 2,
        // чтобы получить половину ширины/высоты,
        // а затем делим на SCALE = 32
        SfVector2toB2Vec2(
            sf::Vector2i((walls[i].m_rect.left + walls[i].m_rect.width / 2),
                         (walls[i].m_rect.top + walls[i].m_rect.height / 2))),
        0);

    staticBody->CreateFixture(&myFixtureDef);
  }
}

void Game::sendBullet(BaseCharacter *hero) {
  // std::shared_ptr<Bullet> bullet = hero->attack(m_world);
  // m_bullets.push_back(bullet);
}

void Game::saveGame(const std::string &fileName) {
  b2dJson json;
  json.writeToFile(&m_world, fileName.c_str());

  //  b2dJson json(false);
  //  std::string str = json.writeToString(&m_world);
  //  std::string err;

  //  json.readFromString(str, err, &m_world);

  //  LOG() << err << std::endl;
}

void Game::loadGame(const std::string &fileName) {
  std::string err;
  b2dJson json;
  m_world = *(json.readFromFile(
      fileName.c_str(),
      err)); // ыыыыы, оно почему-то заработало, но выглядит стрёмно
  updatePhysics();
}

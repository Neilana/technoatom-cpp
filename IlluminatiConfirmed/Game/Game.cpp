#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"

#include <iostream>
#include "Game.h"

using namespace sf;
using namespace std;

using IlluminatiConfirmed::Game;

Game::Game(sf::RenderWindow &window) : m_world(b2Vec2(0.0f, 0.0f)) {
  m_currentHeroId = 0;
}

void Game::initNewGame(const std::string &mapFile) {
  m_level.loadMapFromFile(mapFile);  // загружаем карту
  initCharacters();                  // загружаем персонажей
  initPhysics();
}

void Game::initCharacters() {
  std::shared_ptr<Character> hero1 =
      std::make_shared<Character>("../Game/sprites/demon.png", m_world, 4, 64,
                                  64, "../Game/sprites/bullets/bullet1.png");
  hero1->setCoordinates(sf::Vector2u(500, 500));
  m_heroes.push_back(std::move(hero1));

  std::shared_ptr<Character> hero2 =
      std::make_shared<Character>("../Game/sprites/panda.png", m_world, 3, 32,
                                  32, "../Game/sprites/bullets/bullet2.png");
  hero2->setCoordinates(sf::Vector2u(100, 100));
  m_heroes.push_back(std::move(hero2));

  std::shared_ptr<Character> hero3 =
      std::make_shared<Character>("../Game/sprites/spider.png", m_world, 10, 64,
                                  64, "../Game/sprites/bullets/bullet3.png");
  hero3->setCoordinates(sf::Vector2u(300, 300));
  m_heroes.push_back(std::move(hero3));
}

void Game::draw(sf::RenderWindow &window) {
  window.clear();

  // рисуем карту
  m_level.Draw(window);

  // рисуем всех персонажей
  for (auto &&it : m_heroes) it->draw(window);

  // рисуем пули
  for (auto &&it : m_bullets) it->draw(window);

  // дебаг
  // m_world.Dump();
  SFMLDebugDraw debugDraw(window);
  m_world.SetDebugDraw(&debugDraw);
  debugDraw.SetFlags(b2Draw::e_shapeBit + b2Draw::e_aabbBit +
                     b2Draw::e_centerOfMassBit + b2Draw::e_pairBit);
  m_world.DrawDebugData();
  //  sstream.precision(0);
  //  sstream << std::fixed << "FPS: " << 1.f / timeSf.asSeconds();
  //  fpsCounter.setString(sstream.str());
  //  window.draw(fpsCounter);
  //  sstream.str("");
  window.display();
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
  for (auto &&it : m_heroes) it->updatePhysics();
  for (auto &&it : m_bullets) it->updatePhysics();
  m_bullets.remove_if([](auto &i) { return i->hasStopped(); });
}

void Game::buildBarriers(std::vector<Object> &walls) {
  for (size_t i = 0; i < walls.size(); i++) {
    // я запуталась, в  том, что вверху и переписала. ща стены норм рисуются
    // ещё здесь надо будет сделать оптимизацию и вынести часть этой ерунды за
    // пределы for
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
        walls[i].m_rect.height /
            64.0,  // 64 - потому что сначала мы делим на 2,
        // чтобы получить половину ширины/высоты,
        // а затем делим на SCALE = 32
        SfVector2toB2Vec2(
            sf::Vector2i((walls[i].m_rect.left + walls[i].m_rect.width / 2),
                         (walls[i].m_rect.top + walls[i].m_rect.height / 2))),
        0);

    staticBody->CreateFixture(&myFixtureDef);
  }
}

void Game::sendBullet(Character *hero) {
  std::shared_ptr<Bullet> bullet = hero->attack(m_world);
  m_bullets.push_back(bullet);
}

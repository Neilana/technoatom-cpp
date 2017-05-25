#include "Game.h"
#include <iostream>

Game::Game(b2World *world) : m_world(world) { m_currentHeroId = 0; }

void Game::initNewGame(const std::string &mapFile) {
  m_level.loadMapFromFile(mapFile);  // загружаем карту
  initCharacters();                  // загружаем персонажей
  initPhysics();
}

void Game::initCharacters() {
  std::shared_ptr<Character> hero1 = std::make_shared<Character>(
      "../Game/sprites/demon.png", m_world, 4, 64, 64);
  m_heroes.push_back(std::move(hero1));

  std::shared_ptr<Character> hero2 = std::make_shared<Character>(
      "../Game/sprites/panda.png", m_world, 3, 32, 32);
  hero2->setCoordinates(sf::Vector2u(100, 100));
  m_heroes.push_back(std::move(hero2));

  std::shared_ptr<Character> hero3 = std::make_shared<Character>(
      "../Game/sprites/spider.png", m_world, 10, 64, 64);
  hero3->setCoordinates(sf::Vector2u(300, 300));
  m_heroes.push_back(std::move(hero3));
}

void Game::draw(sf::RenderWindow &window) {
  // рисуем карту
  m_level.Draw(window);

  // рисуем всех персонажей
  for (auto &&it : m_heroes) it->draw(window);
}

void Game::initPhysics() {
  sf::Vector2i tileSize = m_level.GetTileSize();

  // загружаем в Box2D стены
  walls = m_level.GetObjectsByType("Wall");
  for (int i = 0; i < walls.size(); i++) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = SfVector2toB2Vec2(sf::Vector2i(
        walls[i].m_rect.left +
            tileSize.x / 2 * (walls[i].m_rect.width / tileSize.x - 1),
        walls[i].m_rect.top +
            tileSize.y / 2 * (walls[i].m_rect.height / tileSize.y - 1)));

    b2Body *body = m_world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    auto size = SfVector2toB2Vec2(
        sf::Vector2i(walls[i].m_rect.width / 2, walls[i].m_rect.height / 2));
    shape.SetAsBox(size.x, size.y);
    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.restitution = 0.1f;

    body->CreateFixture(&fixture);
  }
}

void Game::updatePhysics() {}

#include "Game.h"
#include <iostream>

Game::Game() { m_currentHeroId = 0; }

void Game::initNewGame(const std::string &mapFile) {
  m_level.loadMapFromFile(mapFile);  // загружаем карту
  initCharacters();                  // загружаем персонажей
  initPhysics();
}

void Game::initCharacters() {
  Character *hero1 = new Character("../sprites/demon.png", 4, 64, 64);
  m_heroes.push_back(*hero1);

  Character *hero2 = new Character("../sprites/panda.png", 3, 32, 32);
  hero2->setCoordinates(100, 100);
  m_heroes.push_back(*hero2);

  Character *hero3 = new Character("../sprites/spider.png", 10, 64, 64);
  hero3->setCoordinates(300, 300);
  m_heroes.push_back(*hero3);
}

void Game::draw(sf::RenderWindow &window) {
  // рисуем карту
  m_level.Draw(window);

  // рисуем всех персонажей
  for (auto it = m_heroes.begin(); it != m_heroes.end(); it++) it->draw(window);
}

void Game::initPhysics() {
  b2Vec2 gravity(0, -9.8);
  world = new b2World(gravity);
  sf::Vector2i tileSize = m_level.GetTileSize();

  // загружаем в Box2D стены
  walls = m_level.GetObjectsByType("Wall");
  for (int i = 0; i < walls.size(); i++) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(
        walls[i].m_rect.left +
            tileSize.x / 2 * (walls[i].m_rect.width / tileSize.x - 1),
        walls[i].m_rect.top +
            tileSize.y / 2 * (walls[i].m_rect.height / tileSize.y - 1));
    b2Body *body = world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(walls[i].m_rect.width / 2, walls[i].m_rect.height / 2);
    body->CreateFixture(&shape, 1.0f);
  }

  // загружаем в Box2D как основного игрока панду :) (потом надо будет всех,
  // сейчас просто
  // тестим что физика норм работает - точнее НЕ работает...)
  Character *hero = &m_heroes[1];

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(hero->getX(), hero->getY());
  bodyDef.fixedRotation = true;
  playerBody = world->CreateBody(&bodyDef);

  b2PolygonShape shape;
  shape.SetAsBox(hero->tileWidth / 2, hero->tileHeight / 2);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;
  playerBody->CreateFixture(&fixtureDef);
}

void Game::updatePhysics() {
  // здесь ничё не работает, надо химичить с координатами. в Box2D там всё в
  // системе Си,
  // а нам нужны пиксели
  playerBody->SetLinearVelocity(
      b2Vec2(m_heroes[1].vx / 64.0, m_heroes[1].vy / 64.0));

  // выводим в консоль координаты Box2D и координаты панды (должны совпадать -
  // но пока нет)
  std::cerr << playerBody->GetPosition().x << " ";
  std::cerr << m_heroes[1].x << "\n";

  // проверяем с чем там столкнулась панда - пока не работает :(
  for (b2ContactEdge *ce = playerBody->GetContactList(); ce; ce = ce->next) {
    b2Contact *c = ce->contact;
    std::cout << "! ";
  }
  world->Step(1.0f / 60.0f, 1,
              1);  // обновляем мир Box2D, не факт что оно здесь должно быть
}

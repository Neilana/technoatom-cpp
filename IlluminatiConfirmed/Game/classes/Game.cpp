#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"

#include "b2dJson.h"

#include <iostream>

#include "CharacterAlinasBoys.h"
#include "Game.h"
#include "GameDatabase.h"
#include "MyContactListener.h"

using namespace sf;
using namespace std;

using namespace IlluminatiConfirmed;

Game::Game(sf::RenderWindow &window) : m_world(b2Vec2(0.0f, 0.0f)) {
  m_currentHeroId = 0;

  MyContactListener *listner = new MyContactListener;
  //m_world.SetContactListener(listner);  //не работает, здания имеют другой
                                        //базовый класс, крошится если оставить
                                        //прежний
  SFMLDebugDraw *debugDraw =
      new SFMLDebugDraw(window);  //утечка памяти, бокс не будет это удалять
  debugDraw->SetFlags(b2Draw::e_shapeBit + b2Draw::e_centerOfMassBit +
                      b2Draw::e_pairBit);
  m_world.SetDebugDraw(debugDraw);
}

void Game::initNewGame(const std::string &map_puth, const std::string &file,
                       std::set<int> ids) {
  Level level;

  level.loadMapFromFile(map_puth + file);

  m_texture.loadFromFile(map_puth + level.GetMapInfo().m_name_of_tileset);
  m_ground = Ground(m_texture, level.GetLayerByName(LAYER_GROUND));

  auto big_objs =
      level.GetVecOfBigObjs(OBJECT_SPRITE, OBJECT_BODY, LAYER_BUILDINGS);

  for (auto &&it : big_objs) {
    m_vec_map.push_back(MapsStuff(m_texture, std::move(it), m_world));
  }
  initCharacters(ids);  // загружаем персонажей
  initPhysics();
}

void Game::initCharacters(std::set<int> ids) {
  //  m_heroes.push_back(std::static_pointer_cast<BaseCharacter>(
  //      std::make_shared<CharacterAlinasBoys>(
  //          m_world, CharacterSpriteInfo(
  //                       {"../Game/resources/sprites/characters/demon1.png",
  //                       64,
  //                        64, 64, 4, 100, 100}))));

  //  m_heroes.push_back(std::static_pointer_cast<BaseCharacter>(
  //      std::make_shared<CharacterAlinasBoys>(
  //          m_world,
  //          CharacterSpriteInfo({"../Game/resources/sprites/characters/panda.png",
  //                               32, 32, 32, 3, 200, 200}))));

  //  m_heroes.push_back(std::static_pointer_cast<BaseCharacter>(
  //      std::make_shared<CharacterAlinasBoys>(
  //          m_world, CharacterSpriteInfo(
  //                       {"../Game/resources/sprites/characters/spider1.png",
  //                       64,
  //                        64, 64, 10, 300, 300}))));

  //  m_heroes.push_back(std::static_pointer_cast<BaseCharacter>(
  //      std::make_shared<CharacterSouthPark>(
  //          m_world,
  //          CharacterSpriteInfo({"../Game/resources/sprites/characters/kyle.png",
  //                               192, 192, 64, 2, 400, 400}))));

  GameDatabase db = GameDatabase::getInstance();
  for (auto it : ids) {
    int id = it;
    QString str =
        "SELECT * FROM CharactersImages WHERE Id=" + QString::number(it);
    QSqlQuery query;
    query.exec(str);
    while (query.next()) {
      std::string fileName = CHARACTERS_SPRITES_DIRECTORY +
                             query.value(1).toString().toStdString();
      int width = query.value(2).toInt();
      int height = query.value(3).toInt();
      int frames = query.value(4).toInt();
      std::string master = query.value(7).toString().toStdString();
      std::string bulletsFile =
          BULLETS_SPRITES_DIRECTORY + query.value(6).toString().toStdString();
      if (master == "Alina") {
        m_heroes.push_back(std::static_pointer_cast<BaseCharacter>(
            std::make_shared<CharacterAlinasBoys>(
                m_world, CharacterSpriteInfo({fileName, width, height, width,
                                              frames, 300, 300}),
                bulletsFile)));
      }
      if (master == "Anton") {
        m_heroes.push_back(std::static_pointer_cast<BaseCharacter>(
            std::make_shared<CharacterSouthPark>(
                m_world,
                CharacterSpriteInfo({fileName, width, height,
                                     DEFAULT_SPRITE_SIZE_X, frames, 300, 300}),
                bulletsFile)));
      }
    }
  }
}

void Game::draw(sf::RenderWindow &window) {
  // рисуем землю
  m_ground.draw_ground(window);

  //рисуем здания
  for (auto &&it : m_vec_map) {
    it.draw(window);
  }

  // рисуем всех персонажей
  for (auto &&it : m_heroes) it->draw(window);

  // рисуем пули
  for (auto &&it : m_bullets) it->draw(window);

  // дебаг
  // m_world.Dump();
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
  m_world.Step(1 / 60.f, 8, 3);

  //  b2dJson json(false);

  // std::string str = json.writeToString(&m_world);
  // std::string err;

  // json.readFromString(str, err, &m_world);

  // LOG() << err << std::endl;3

  for (auto &&it : m_heroes) it->updatePhysics(time);
  for (auto &&it : m_bullets) it->updatePhysics();
  m_bullets.remove_if([](auto &i) { return i->hasStopped(); });
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

void Game::sendBullet(BaseCharacter *hero) {
  std::shared_ptr<Bullet> bullet = hero->attack(m_world);
  m_bullets.push_back(bullet);
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
      err));  // ыыыыы, оно почему-то заработало, но выглядит стрёмно
  // updatePhysics();
}

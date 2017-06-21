#pragma once

#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

#include "Bullet.h"
#include "Event/Event.h"
#include "Factories.h"

namespace IlluminatiConfirmed {
namespace experimental {

struct WeaponInfo {
  TypeBullet bullet_type;
  sf::Rect<int> rect_with_weapon;
  sf::Rect<int> rect_with_weapon_fire;
  int number_of_cartridge;  // damage в пульке
  float scale;
};

class SpriteInterface {
  virtual void draw(sf::RenderWindow *) = 0;
};

struct BulletSetsInfo {
  BulletSets sets;
  TypeBullet type;
};

class Weapon {
 public:
  Weapon(sf::Texture *texture, const WeaponInfo &info)
      : m_number_of_cartridge(info.number_of_cartridge),
        m_rect_with_weapon(info.rect_with_weapon),
        m_rect_with_weapon_fire(info.rect_with_weapon_fire),
        m_type_bullet(info.bullet_type) {
    m_sprite.setTexture(*texture);
    m_sprite.setTextureRect(info.rect_with_weapon);
    m_sprite.setScale(info.scale, info.scale);
    m_sprite.setOrigin(info.rect_with_weapon.width / 2.f,
                       info.rect_with_weapon.height / 2.f -
                           info.rect_with_weapon.height * 0.90f);
  }

  void setPositionRotation(const sf::Vector2f &pos, float rotation) {
    m_sprite.setPosition(pos);

    auto flip_check = m_sprite.getScale();
    if ((rotation > 90 || rotation < -90) && flip_check.x > 0) {  // degrees

      m_sprite.setScale(-flip_check.x, flip_check.y);
    } else if (flip_check.x < 0)
      m_sprite.setScale(-flip_check.x, flip_check.y);

    m_sprite.setRotation(rotation);
  }

  void attack() {
    if (m_number_of_cartridge > 0) {
      --m_number_of_cartridge;
      m_sprite.setTextureRect(m_rect_with_weapon_fire);
      m_time = 30;
      {
        //кроче, пуля должна вылетать прямо изствола, надо расчитать
        //этукоординату
        sf::Vector2<float> place_of_shoot;
        auto position = m_sprite.getPosition();

        auto al = m_sprite.getRotation();

        auto c = m_rect_with_weapon.width / 2.f;
        auto a = sin(1.f);
      }
      auto pos = m_sprite.getPosition();
      pos.x += m_sprite.getTextureRect().height;
      event_create_bullet.notifyListeners(
          {{{b2Vec2(pos.x, pos.y)}, b2Vec2(1.f, 1.f)}, m_type_bullet});
    }
  }

  void draw(sf::RenderWindow &window) {
    if (m_time == 0)
      m_sprite.setTextureRect(m_rect_with_weapon);
    else
      --m_time;

    window.draw(m_sprite);
  }

  Event<BulletSetsInfo> event_create_bullet;

 private:
  sf::Sprite m_sprite;
  int m_number_of_cartridge;
  sf::Rect<int> m_rect_with_weapon;
  sf::Rect<int> m_rect_with_weapon_fire;
  int m_time;
  TypeBullet m_type_bullet;
};

class ListnerWeapon {
 public:
  ListnerWeapon(Weapon *class_, b2World *world,
                std::vector<std::shared_ptr<experimental::Bullet>> *bullets,
                std::vector<std::shared_ptr<experimental::BaseInterface>> *objs)
      : syncVal(class_->event_create_bullet.createSyncValue()) {
    eventListener =
        class_->event_create_bullet.createListener([this, world, bullets, objs](
            auto bul) { pushBullet(std::move(bul), world, bullets, objs); });
  }

  void pushBullet(
      BulletSetsInfo &&bullet_sets, b2World *world,
      std::vector<std::shared_ptr<experimental::Bullet>> *bullets,
      std::vector<std::shared_ptr<experimental::BaseInterface>> *objs) {
    //здесь некая фабрика пулек, причем настройки должны кэшироваться, иначе
    //каждая пулька запрос к бд, мы же performance freak
    if (objs != nullptr && bullets != nullptr && world != nullptr) {
      auto texture = experimental::FactoryObjects::getTexture(
          "E:/Git_ver3000/technoatom-cpp/IlluminatiConfirmed/Game/"
          "resources/sprites/bullets/ak.png");

      auto bullet = std::make_shared<experimental::Bullet>(
          world, texture.get(),
          experimental::BulletInfo(
              {{{0, 0, 604, 187}}, 0.1f, 10, 0.01f, 1, 1}));
      bullet->setTransform(std::move(bullet_sets.sets));

      objs->push_back(bullet);
      bullets->push_back(std::move(bullet));
    } else
      throw EXCEPTION("Pointer on null", nullptr);
  }
  SyncValue<BulletSetsInfo> syncVal;

 private:
  EventListener<BulletSetsInfo> eventListener;
};
}
}

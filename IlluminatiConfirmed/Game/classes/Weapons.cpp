#include "Weapons.h"

IlluminatiConfirmed::experimental::Weapon::Weapon(
    sf::Texture *texture,
    const IlluminatiConfirmed::experimental::WeaponInfo &info)
    : m_number_of_cartridge(info.number_of_cartridge),
      m_rect_with_weapon(info.rect_with_weapon),
      m_rect_with_weapon_fire(info.rect_with_weapon_fire),
      m_type_bullet(info.bullet_type) {
  m_sprite.setTexture(*texture);
  m_sprite.setTextureRect(info.rect_with_weapon);
  m_sprite.setScale(info.scale, info.scale);
  m_sprite.setOrigin(info.rect_with_weapon.width / 2.f -
                         0.2f * info.rect_with_weapon.width / 2.f,
                     info.rect_with_weapon.height / 2.f);
}

void IlluminatiConfirmed::experimental::Weapon::setPositionRotation(
    const sf::Vector2f &pos, float rotation) {
  // LOG() << "os Weapon: " << pos.x << " " << pos.y  << std::endl;
  m_sprite.setPosition(pos);
  // LOG() << "Rotate Weapon: " << rotation;

  auto flip_check = m_sprite.getScale();

  // LOG() << "flip before: " << flip_check;

  if (((rotation < 90) && (rotation > -90)) && flip_check.y < 0) { // degrees

    m_sprite.setScale(flip_check.x, -flip_check.y);
  } else if (((rotation > 90) || (rotation < -90)) && flip_check.y > 0)
    m_sprite.setScale(flip_check.x, -flip_check.y);

  // LOG() << " after: " << rotation <<std::endl;
  // LOG() << "flip after: " << flip_check << std::endl;
  m_sprite.setRotation(rotation);
}

void IlluminatiConfirmed::experimental::Weapon::attack() {
  if (m_number_of_cartridge > 0) {
    --m_number_of_cartridge;
    m_sprite.setTextureRect(m_rect_with_weapon_fire);
    m_time = 15;

    auto a = m_sprite.getRotation();
    auto pos = m_sprite.getPosition();

    auto dir =
        sf::Vector2f(m_rect_with_weapon.width * cosf(a / 180 * b2_pi) / 4.f,
                     m_rect_with_weapon.width * sinf(a / 180 * b2_pi) / 4.f);

    pos.x += dir.x;
    pos.y += dir.y;

    auto dir_ = b2Vec2(cosf(a / 180 * b2_pi), sinf(a / 180 * b2_pi));

    LOG() << "Pos after: " << pos << std::endl;
    event_create_bullet.notifyListeners(
        {{{SfVector2toB2Vec2(pos)}, {SfVector2toB2Vec2(dir)}}, m_type_bullet});
  }
}

void IlluminatiConfirmed::experimental::Weapon::draw(sf::RenderWindow &window) {
  if (m_time <= 0)
    m_sprite.setTextureRect(m_rect_with_weapon);
  else
    --m_time;

  window.draw(m_sprite);
}

IlluminatiConfirmed::experimental::ListnerWeapon::ListnerWeapon()
    : m_world(nullptr), m_bullets(nullptr), m_objs(nullptr) {}

IlluminatiConfirmed::experimental::ListnerWeapon::ListnerWeapon(
    b2World *world,
    std::vector<std::shared_ptr<IlluminatiConfirmed::experimental::Bullet>>
        *bullets,
    std::vector<
        std::shared_ptr<IlluminatiConfirmed::experimental::BaseInterface>>
        *objs)
    : m_world(world), m_bullets(bullets), m_objs(objs) {
  // syncVal(class_->event_create_bullet.createSyncValue());
}

void IlluminatiConfirmed::experimental::ListnerWeapon::addWeapon(
    IlluminatiConfirmed::experimental::Weapon *class_) {
  auto syncVal = class_->event_create_bullet.createSyncValue();

  auto eventListener = class_->event_create_bullet.createListener(
      [this](auto bul) { pushBullet(std::move(bul)); });

  m_syncValues_and_eventListener.push_back(
      {std::move(syncVal), std::move(eventListener)});
}

void IlluminatiConfirmed::experimental::ListnerWeapon::pushBullet(
    IlluminatiConfirmed::experimental::BulletSetsInfo &&bullet_sets) {
  //здесь некая фабрика пулек, причем настройки должны кэшироваться, иначе
  //каждая пулька запрос к бд, мы же performance freak
  if (m_objs != nullptr && m_bullets != nullptr && m_world != nullptr) {
    auto texture = experimental::FactoryObjects::getTexture(
        BULLETS_SPRITES_DIRECTORY + "ak.png");

    auto bullet = std::make_shared<experimental::Bullet>(
        m_world, texture.get(),
        experimental::BulletInfo({{{0, 0, 604, 187}}, 0.1f, 10, 1.f, 1, 1}));
    bullet->setTransform(std::move(bullet_sets.sets));

    m_objs->push_back(bullet);
    m_bullets->push_back(std::move(bullet));
  } else
    throw EXCEPTION("Pointer on null", nullptr);
}

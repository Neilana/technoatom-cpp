#include "Weapons.h"
#include "Factories.h"

#include <QSound>

IlluminatiConfirmed::experimental::Weapon::Weapon(
    sf::Texture *texture,
    const IlluminatiConfirmed::experimental::WeaponInfo &info)
    : QObject(nullptr),
      m_number_of_cartridge(info.number_of_cartridge),
      m_type_bullet(info.bullet_type),
      m_whose(nullptr) {
  m_sprite.setTexture(*texture);

  for (int i = 0; i < info.count_of_rect; ++i) {
    auto rect = info.rect_weapon;
    rect.left = i * info.rect_weapon.width;

    m_rects_weapon.push_back(std::move(rect));
  }

  m_sprite.setTextureRect(m_rects_weapon.at(0));
  m_sprite.setScale(info.scale, info.scale);
  m_sprite.setOrigin(
      info.rect_weapon.width / 2.f - 0.2f * info.rect_weapon.width / 2.f,
      info.rect_weapon.height / 2.f);
}

void IlluminatiConfirmed::experimental::Weapon::setPositionRotation(
    const sf::Vector2f &pos, float rotation) {
  m_sprite.setPosition(pos);
  auto flip_check = m_sprite.getScale();

  if (((rotation < 90) && (rotation > -90)) && flip_check.y < 0) {  // degrees
    m_sprite.setScale(flip_check.x, -flip_check.y);
  } else if (((rotation > 90) || (rotation < -90)) && flip_check.y > 0)
    m_sprite.setScale(flip_check.x, -flip_check.y);
  m_sprite.setRotation(rotation);
}

void IlluminatiConfirmed::experimental::Weapon::attack(BaseCharacter *who) {
  if (m_number_of_cartridge > 0) {
    --m_number_of_cartridge;

    m_animation.setStartTime(30);
    m_animation.time = m_animation.getStartTime();
    m_animation.count = m_animation.getStartTime() / m_rects_weapon.size();

    auto a = m_sprite.getRotation();
    auto pos = m_sprite.getPosition();
    auto scale = m_sprite.getScale().x;
    if (scale < 0) scale *= -1.f;

    auto dir = sf::Vector2f(
        m_rects_weapon.at(0).width * scale * cosf(a / 180 * b2_pi) / 2.f,
        m_rects_weapon.at(0).width * scale * sinf(a / 180 * b2_pi) / 2.f);

    pos.x += dir.x;
    pos.y += dir.y;

    LOG() << "Pos: " << pos << std::endl;
    LOG() << "dir: " << dir << std::endl;

    emit create_bullet({{{SfVector2toB2Vec2(pos)}, {SfVector2toB2Vec2(dir)}},
                        m_type_bullet,
                        who});
  }
}

void IlluminatiConfirmed::experimental::Weapon::draw(sf::RenderWindow &window) {
  if (m_animation.time > 0) {
    auto index = m_animation.time-- / m_animation.count;
    m_sprite.setTextureRect(m_rects_weapon.at(
        (index < m_rects_weapon.size()) ? index : m_rects_weapon.size() - 1));
  } else
    m_rects_weapon.at(0);

  window.draw(m_sprite);
}

void IlluminatiConfirmed::experimental::Weapon::initTimeAnimation() {}

IlluminatiConfirmed::experimental::ListnerWeapon::ListnerWeapon()
    : QObject(nullptr), m_world(nullptr), m_bullets(nullptr), m_objs(nullptr) {}

void IlluminatiConfirmed::experimental::ListnerWeapon::setPointers(
    b2World *world,
    std::vector<
        std::shared_ptr<IlluminatiConfirmed::experimental::BulletInterface>>
        *bullets,
    std::vector<
        std::shared_ptr<IlluminatiConfirmed::experimental::BaseInterface>>
        *objs) {
  m_world = world;
  m_bullets = bullets;
  m_objs = objs;
}

void IlluminatiConfirmed::experimental::ListnerWeapon::pushBullet(
    BulletSetsInfo bullet_sets) {
  if (m_objs != nullptr && m_bullets != nullptr && m_world != nullptr) {
    auto bullet = FactoryObjects::Instance().create_bullet(
        bullet_sets.type, m_world, bullet_sets.whose);

    bullet->setTransform(std::move(bullet_sets.sets));

    m_objs->push_back(bullet);
    m_bullets->push_back(std::move(bullet));
  } else
    throw EXCEPTION("Pointer on null", nullptr);
}

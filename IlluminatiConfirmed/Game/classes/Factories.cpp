#include "Factories.h"

using namespace IlluminatiConfirmed;
using namespace experimental;

std::pair<std::shared_ptr<Ground>,
          std::vector<std::shared_ptr<experimental::BaseInterface>>>
FactoryObjects::create_map(const std::string &file, b2World *world) {
  Level level;
  level.loadMapFromFile(file);

  auto p_texture = Instance().getTexture(std::string(MAP_DIRECTORY) +
                                         level.GetMapInfo().m_name_of_tileset);

  std::shared_ptr<Ground> vec_of_graund;
  vec_of_graund = std::make_shared<Ground>(p_texture.get(),
                                           level.GetLayerByName(LAYER_GROUND));

  std::vector<std::shared_ptr<experimental::BaseInterface>> p_vec_of_maps_stuff;
  auto big_objs =
      level.GetVecOfBigObjs(OBJECT_SPRITE, OBJECT_BODY, LAYER_BUILDINGS);
  for (auto &&it : big_objs) {
    auto pointer = std::static_pointer_cast<experimental::BaseInterface>(
        std::make_shared<experimental::Building>(world, p_texture.get(),
                                                 std::move(it)));

    p_vec_of_maps_stuff.push_back(std::move(pointer));
  }
  return {std::move(vec_of_graund), std::move(p_vec_of_maps_stuff)};
}

std::shared_ptr<experimental::BaseCharacter> FactoryObjects::create_character(
    int id, b2World *world) {
  static auto characters_factory = registrationTypesOfCharacters();

  QString str =
      "SELECT * FROM CharactersImages WHERE Id=" + QString::number(id);
  QSqlQuery query;
  query.exec(str);
  while (query.next()) {
    std::string fileName = query.value(1).toString().toStdString();
    int width = query.value(2).toInt();
    int height = query.value(3).toInt();
    int frames = query.value(4).toInt();
    std::string master = query.value(7).toString().toStdString();
    int size = query.value(8).toInt();
    std::string healthBarFile = query.value(6).toString().toStdString();

    auto p_texture =
        Instance().getTexture(CHARACTERS_SPRITES_DIRECTORY + fileName);

    if (master == "Park") {
      auto killed = experimental::FactoryObjects::Instance().getSound(
          SOUNDS_DIRECTORY + std::string("killed_kyle.wav"));

      BaseCharacter::SoundPack pack({std::move(killed)});

      auto pers =
          std::shared_ptr<experimental::BaseCharacter>(characters_factory.get(
              master)(world, p_texture.get(),
                      experimental::CharacterSpriteInfo(
                          {width, height, size, frames, 300, 300}),
                      std::move(pack)));
      auto bufHud = std::make_shared<HUD>(
          HUD(fileName, healthBarFile, width, height, size));
      pers.get()->setHud(std::move(bufHud));

      return pers;
    } else {
      std::shared_ptr<IlluminatiSound> killed;

      BaseCharacter::SoundPack pack({std::move(killed)});

      auto pers =
          std::shared_ptr<experimental::BaseCharacter>(characters_factory.get(
              master)(world, p_texture.get(),
                      experimental::CharacterSpriteInfo(
                          {width, height, size, frames, 300, 300}),
                      std::move(pack)));

      auto bufHud = std::make_shared<HUD>(
          HUD(fileName, healthBarFile, width, height, size));
      pers.get()->setHud(std::move(bufHud));
      return pers;
    }
  }
  throw EXCEPTION("Something wrong", nullptr);
}

std::shared_ptr<BulletInterface> FactoryObjects::create_bullet(
    experimental::TypeBullet type, b2World *world, BaseCharacter *whose) {
  static auto bullets_factory = registrationTypesOfBullets();

  std::shared_ptr<experimental::BulletInterface> bullet;

  if (type == TypeBullet::little_bullet) {
    auto p_hitting_building = experimental::FactoryObjects::Instance().getSound(
        SOUNDS_DIRECTORY + std::string("hit_building_bullet.wav"));
    auto p_flying = experimental::FactoryObjects::Instance().getSound(
        SOUNDS_DIRECTORY + std::string("flying_bullet.wav"));
    BulletInterface::SoundPack pack(
        {std::move(p_hitting_building), std::move(p_flying)});

    auto texture = experimental::FactoryObjects::Instance().getTexture(
        BULLETS_SPRITES_DIRECTORY + "ak.png");
    bullet = std::shared_ptr<experimental::BulletInterface>(bullets_factory.get(
        "little")(world, texture.get(), std::move(pack),
                  experimental::BulletInfo(
                      {{{0, 0, 604, 187}}, whose, 0.1f, 10, 7.f, 1, 1})));
  } else if (type == TypeBullet::ROCKET) {
    auto p_hitting_building = experimental::FactoryObjects::Instance().getSound(
        SOUNDS_DIRECTORY + std::string("expl_rocket.wav"));
    auto p_flying = experimental::FactoryObjects::Instance().getSound(
        SOUNDS_DIRECTORY + std::string("flying_bullet.wav"));
    BulletInterface::SoundPack pack(
        {std::move(p_hitting_building), std::move(p_flying)});

    auto texture = experimental::FactoryObjects::Instance().getTexture(
        BULLETS_SPRITES_DIRECTORY + "rocket_1.png");
    bullet = std::shared_ptr<experimental::BulletInterface>(bullets_factory.get(
        "rocket")(world, texture.get(), std::move(pack),
                  experimental::BulletInfo(
                      {{{0, 0, 56, 18}}, whose, 1.5f, 10, 3.f, 1, 1})));
  } else
    throw EXCEPTION("Unknow class name of bullet", nullptr);

  return bullet;
}

std::unique_ptr<Weapon> FactoryObjects::create_weapon(WeaponType type) {
  std::shared_ptr<sf::Texture> p_weapon_text;

  std::unique_ptr<experimental::Weapon> weapon;
  if (type == WeaponType::BAZOOKA) {
    p_weapon_text = experimental::FactoryObjects::Instance().getTexture(
        BULLETS_SPRITES_DIRECTORY + std::string("bazooka.png"));
    weapon = std::make_unique<experimental::Weapon>(
        p_weapon_text.get(),
        experimental::WeaponInfo({experimental::TypeBullet::ROCKET,
                                  {0, 0, 900, 362},
                                  4,
                                  10,
                                  0.09f}));
  } else if (type == WeaponType::AK) {
    p_weapon_text = experimental::FactoryObjects::Instance().getTexture(
        BULLETS_SPRITES_DIRECTORY + std::string("ak.png"));
    weapon = std::make_unique<experimental::Weapon>(
        p_weapon_text.get(),
        experimental::WeaponInfo({experimental::TypeBullet::little_bullet,
                                  {0, 0, 663, 187},
                                  2,
                                  10,
                                  0.1f}));
  } else
    throw EXCEPTION("Unknow class name of weapon", nullptr);

  return weapon;
}

std::string FactoryObjects::getList() {
  //как то надо вывести все чо есть, заготовка для dll
  return std::string();
}

std::shared_ptr<sf::Texture> FactoryObjects::getTexture(
    const std::string &file) {
  return m_textures.getResource(file);
}

std::shared_ptr<IlluminatiSound> FactoryObjects::getSound(
    const std::string &file) {
  return m_sounds.getResource(file);
}

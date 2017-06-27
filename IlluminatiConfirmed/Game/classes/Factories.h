#pragma once

#include <QSound>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <SFML/Graphics.hpp>

#include <map>

#include "../../Exceptions/Exception.h"
#include "Base.h"
#include "Character.h"
#include "Ground.h"
#include "Weapons.h"
#include "constants.h"

namespace IlluminatiConfirmed {
namespace experimental {

template <class TSound>
class Resource {
 public:
  std::shared_ptr<TSound> getResource(const std::string &file);

 private:
  std::map<std::string, std::shared_ptr<TSound>> m_vec_of_resources;
};

template <class TSound>
std::shared_ptr<TSound> Resource<TSound>::getResource(const std::string &file) {
  auto p_source = std::make_shared<TSound>();
  auto it = m_vec_of_resources.find(file);

  if (it == m_vec_of_resources.end()) {
    if (!p_source->loadFromFile(file))
      EXCEPTION(std::string("Resource hasn't opened, puth: ") + file, nullptr);

    m_vec_of_resources.insert({std::move(file), p_source});
  } else
    p_source = (*it).second;
  return p_source;
}

template <>
class Resource<QSound> {
 public:
  std::shared_ptr<QSound> getResource(const std::string &file) {
    std::shared_ptr<QSound> p_sound;
    auto it = m_vec_of_resources.find(file);
    if (it == m_vec_of_resources.end()) {
      p_sound = std::make_shared<QSound>(QString::fromStdString(file));
      m_vec_of_resources.insert({std::move(file), p_sound});
    } else
      p_sound = (*it).second;
    return p_sound;
  }

 private:
  std::map<std::string, std::shared_ptr<QSound>> m_vec_of_resources;
};

template <class ID, class Base, class... Args>
class GenericObjectFactory {
 private:
  typedef Base *(*fInstantiator)(Args...);
  template <class Derived>
  static Base *instantiator(Args... args) {
    return new Derived(args...);
  }
  std::map<ID, fInstantiator> classes;

 public:
  GenericObjectFactory() {}
  template <class Derived>
  void add(ID id) {
    classes[id] = &instantiator<Derived>;
  }
  fInstantiator get(ID id) { return classes[id]; }
};

class FactoryObjects {
 public:
  static FactoryObjects &Instance() {
    static FactoryObjects myInstance;
    return myInstance;
  }

  FactoryObjects(FactoryObjects const &) = delete;
  FactoryObjects(FactoryObjects &&) = delete;
  FactoryObjects &operator=(FactoryObjects const &) = delete;
  FactoryObjects &operator=(FactoryObjects &&) = delete;

  std::pair<std::shared_ptr<Ground>,
            std::vector<std::shared_ptr<experimental::BaseInterface>>>
  create_map(const std::string &file, b2World *world);

  std::shared_ptr<experimental::BaseCharacter> create_character(int id,
                                                                b2World *world);

  std::unique_ptr<Weapon> create_weapon(WeaponType type);

  std::shared_ptr<experimental::BulletInterface> create_bullet(
      experimental::TypeBullet type, b2World *world, BaseCharacter *whose);

  std::string getList();

  std::shared_ptr<sf::Texture> getTexture(const std::string &file);
  std::shared_ptr<IlluminatiSound> getSound(const std::string &file);

 private:
  Resource<sf::Texture> m_textures;
  Resource<IlluminatiSound> m_sounds;
  static GenericObjectFactory<std::string, BaseCharacter, b2World *,
                              sf::Texture *, CharacterSpriteInfo,
                              BaseCharacter::SoundPack>
  registrationTypesOfCharacters() {
    GenericObjectFactory<std::string, BaseCharacter, b2World *, sf::Texture *,
                         CharacterSpriteInfo, BaseCharacter::SoundPack>
        characters_factory;
    characters_factory.add<CharacterSouthPark>("Park");
    characters_factory.add<CharacterAlinasBoys>("Alinas");
    return characters_factory;
  }
  static GenericObjectFactory<std::string, BulletInterface, b2World *,
                              sf::Texture *, BulletInterface::SoundPack,
                              IlluminatiConfirmed::experimental::BulletInfo>
  registrationTypesOfBullets() {
    GenericObjectFactory<std::string, BulletInterface, b2World *, sf::Texture *,
                         BulletInterface::SoundPack,
                         IlluminatiConfirmed::experimental::BulletInfo>
        bullets_factory;
    bullets_factory.add<experimental::LittleBullet>("little");
    bullets_factory.add<experimental::Rocket>("rocket");
    return bullets_factory;
  }

 protected:
  FactoryObjects() {}

  ~FactoryObjects() {}
};
}
}

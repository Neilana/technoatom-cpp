#pragma once

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <SFML/Graphics.hpp>
#include <map>

#include "../../Exceptions/Exception.h"
#include "Character.h"
#include "Ground.h"
#include "constants.h"
#include "Base.h"

namespace IlluminatiConfirmed {
namespace experimental {

template <class ID, class Base, class... Args> class GenericObjectFactory {
private:
  typedef Base *(*fInstantiator)(Args...);
  template <class Derived> static Base *instantiator(Args... args) {
    return new Derived(args...);
  }
  std::map<ID, fInstantiator> classes;

public:
  GenericObjectFactory() {}
  template <class Derived> void add(ID id) {
    classes[id] = &instantiator<Derived>;
  }
  fInstantiator get(ID id) { return classes[id]; }
};

class FactoryObjects {
public:
  static std::pair<std::shared_ptr<Ground>,
                   std::vector<std::shared_ptr<experimental::BaseInterface>>>
  create_map(const std::string &file, b2World *world);

  static std::shared_ptr<experimental::BaseInterface>
  create_character(int id, b2World *world);

  static std::string getList();
  static std::shared_ptr<sf::Texture> getTexture(
      const std::string& file);  //временно

 private:
  static GenericObjectFactory<std::string, BaseCharacter, b2World*,
                              sf::Texture*, CharacterSpriteInfo>
  registrationTypesOfCharacters() {
    GenericObjectFactory<std::string, BaseCharacter, b2World*, sf::Texture*,
                         CharacterSpriteInfo>
        characters_factory;
    characters_factory.add<CharacterSouthPark>("Park");
    characters_factory.add<CharacterAlinasBoys>("Alinas");
    return characters_factory;
  }
};
}
}

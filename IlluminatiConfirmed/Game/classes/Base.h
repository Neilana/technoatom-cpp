#pragma once

#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include <vector>

#include "constants.h"
#include "Level.h"

namespace IlluminatiConfirmed {
namespace experimental {
class Weapon;
class BaseInterface {
public:
  enum TypeBase { MAPS_STUFF, CHARACTER, BULLET };

  BaseInterface(TypeBase type);
  virtual void draw(sf::RenderWindow &window) = 0;
  virtual void move(b2Vec2 velocity, float deltaTime) = 0;
  virtual void contact(b2Fixture *B) = 0;
  virtual void endContact(b2Fixture *B) = 0;
  virtual bool isDead();

  float getY();

  virtual ~BaseInterface();

protected:
  b2Body *m_b2_base;
  b2Fixture *m_b2_base_fixture;
  bool is_dead;
  TypeBase m_type_base;
};

class BaseMapsStuff : public BaseInterface {
public:
  enum TypeMap { BUILDING }; //мб какие то коины или жизни или оружее
  BaseMapsStuff(TypeMap type) : BaseInterface(MAPS_STUFF), m_type_map(type) {
    LOG() << "Create BaseMapsStuff " << int(m_type_base) << std::endl;
  }
  virtual void move(b2Vec2 velocity, float deltaTime) override = 0;
  virtual void draw(sf::RenderWindow &window) override = 0;
  virtual void contact(b2Fixture *B) override = 0;
  virtual void endContact(b2Fixture *B) override = 0;
  virtual ~BaseMapsStuff() {
    LOG() << "Destroy BaseMapsStuff " << int(m_type_map) << std::endl;
  }
  TypeMap m_type_map;
};

class Building : public BaseMapsStuff {
 public:
  Building(b2World *world, const sf::Texture *texture, Big_Object &&big_obj);
  virtual void move(b2Vec2 velocity, float deltaTime) override;
  virtual void draw(sf::RenderWindow &window) override;
  virtual void contact(b2Fixture *B) override;
  virtual void endContact(b2Fixture *B) override;

  ~Building();

     private:
      std::vector<sf::Sprite> m_vec_sprite;
};
}
}

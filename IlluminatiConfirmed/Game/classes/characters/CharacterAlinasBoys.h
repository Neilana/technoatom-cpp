#pragma once

#include "BaseCharacter.h"
using IlluminatiConfirmed::BaseCharacter;

namespace IlluminatiConfirmed {
class CharacterAlinasBoys : public BaseCharacter {
public:
  CharacterAlinasBoys(b2World &world, const CharacterSpriteInfo &sprite_data);
  void move(b2Vec2 velocity, float deltaTime) override;
  void draw(sf::RenderWindow &window) override;
  void contact(b2Fixture *B) override;
  void endContact(b2Fixture *B) override;
  ~CharacterAlinasBoys();
};
}

// class Kolobashka : public CharacterAlinasBoys {
// public:
//  Kolobashka(b2World &world, const CharacterSpriteInfo &sprite_data)
//      : CharacterAlinasBoys(world, sprite_data) {}
//  void move(float deltaTime) override { CharacterAlinasBoys::move(deltaTime);
//  }
//  void draw(sf::RenderWindow &window) override {
//    static int rad;
//    rad += 1;
//    m_sprite.setPosition(B2Vec2toSfVector2<float>(m_b2_body->GetPosition()));
//    m_sprite.setRotation(rad);
//    window.draw(m_sprite);
//  }
//  void contact(b2Fixture *B) override {
//    LOG() << "I'am AlinasBoys Kolobashka and I've begun the colliding with..
//    hz"
//          << std::endl;
//  }
//  void endContact(b2Fixture *B) override {
//    LOG() << "I'am AlinasBoys Kolobashka and I've dune the colliding with..
//    hz"
//          << std::endl;
//  }
//  ~Kolobashka() {}
//};

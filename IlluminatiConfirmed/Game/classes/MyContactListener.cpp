#include "MyContactListener.h"
#include "Character.h"
using namespace IlluminatiConfirmed;
using namespace experimental;

void MyContactListener::BeginContact(b2Contact *contact) {
  void *user_data_A = contact->GetFixtureA()->GetUserData();
  if (user_data_A)
    static_cast<BaseCharacter *>(user_data_A)->contact(contact->GetFixtureB());
  void *user_data_B = contact->GetFixtureA()->GetUserData();
  if (user_data_B)
    static_cast<BaseCharacter *>(user_data_B)->contact(contact->GetFixtureB());
  // if (Type::CHARACTER_SOUTH_PARK ==
  //    static_cast<BaseCharacter*>(user_data)->getType()) {
  //    static_cast<BaseCharacter*>(user_data)->getType()
  // };
}

void MyContactListener::EndContact(b2Contact *contact) {
  void *user_data_A = contact->GetFixtureA()->GetUserData();
  if (user_data_A)
    static_cast<BaseCharacter *>(user_data_A)
        ->endContact(contact->GetFixtureB());
  void *user_data_B = contact->GetFixtureA()->GetUserData();
  if (user_data_B)
    static_cast<BaseCharacter *>(user_data_B)
        ->endContact(contact->GetFixtureB());
}

void MyContactListener::PreSolve(b2Contact *contact,
                                 const b2Manifold *oldManifold) {
  //    const b2Manifold* manifold = contact->GetManifold();

  //    b2Fixture* fixtureA = contact->GetFixtureA();
  //    b2Fixture* fixtureB = contact->GetFixtureB();

  //    b2WorldManifold worldManifold;
  //    contact->GetWorldManifold(&worldManifold);

  //    b2Body* bodyA = fixtureA->GetBody();
  //    b2Body* bodyB = fixtureB->GetBody();
}

void MyContactListener::PostSolve(b2Contact *contact,
                                  const b2ContactImpulse *Impulse) {}

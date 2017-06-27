#include "MyContactListener.h"
#include "Character.h"
using namespace IlluminatiConfirmed;
using namespace experimental;

void MyContactListener::BeginContact(b2Contact *contact) {
  void *user_data_A = contact->GetFixtureA()->GetUserData();
  void *user_data_B = contact->GetFixtureB()->GetUserData();
  if (user_data_A && user_data_B) {
    static_cast<BaseInterface *>(user_data_A)
        ->contact(static_cast<BaseInterface *>(user_data_B));
    static_cast<BaseInterface *>(user_data_B)
        ->contact(static_cast<BaseInterface *>(user_data_A));
  } else
    throw EXCEPTION("User data have nullptr ", nullptr);
}

void MyContactListener::EndContact(b2Contact *contact) {}

void MyContactListener::PreSolve(b2Contact *contact,
                                 const b2Manifold *oldManifold) {}

void MyContactListener::PostSolve(b2Contact *contact,
                                  const b2ContactImpulse *Impulse) {}

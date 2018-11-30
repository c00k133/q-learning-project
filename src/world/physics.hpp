#ifndef Q_LEARNING_PHYSICS_HPP
#define Q_LEARNING_PHYSICS_HPP

#include "Box2D/Box2D.h"


// TODO(Cookie): check if this should be a const variable instead
#define GRAVITATIONAL_FORCE -9.81f

class PhysicsEngine {
 public:
    explicit PhysicsEngine(float world_pos = -10.0f);

    b2World* getWorld();

 private:
    b2World* world;
    b2Body* ground_body;
};

#endif  // Q_LEARNING_PHYSICS_HPP

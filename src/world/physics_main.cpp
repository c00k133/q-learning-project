#include <stdio.h>
#include <iostream>
#include <vector>

#include "physics.hpp"
#include "body.hpp"
#include "Box2D/Box2D.h"


int main(int argc, char** argv) {
  B2_NOT_USED(argc);
  B2_NOT_USED(argv);

  PhysicsEngine engine = PhysicsEngine();
  b2World* world = engine.getWorld();

  WormBody worm;
  b2Body* worm_body = worm.createB2Body(world);

  // This is our little game loop
  for (int32 i = 0; i < 300; ++i) {
    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    engine.step();

    // Now print the position and angle of the body.
    b2Vec2 position = worm_body->GetPosition();
    float32 angle = worm_body->GetAngle();

    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
  }

  // When the world destructor is called, all bodies and joints are freed. This
  // can create orphaned pointers, so be careful about your world management.
  std::cin.get();

  return 0;
}

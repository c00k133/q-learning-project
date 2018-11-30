#include <stdio.h>
#include <iostream>
#include <list>

#include "physics.hpp"
#include "body.hpp"
#include "Box2D/Box2D.h"


int main(int argc, char** argv) {
  B2_NOT_USED(argc);
  B2_NOT_USED(argv);

  PhysicsEngine engine = PhysicsEngine();
  b2World* world = engine.getWorld();

  std::list<int> angles = std::list<int>(0, 0);
  WormBody worm = WormBody(angles, 5);
  b2Body* worm_body = worm.createB2Body(world);

  // Prepare for simulation. Typically we use a time step of 1/60 of a second
  // (60Hz) and 10 iterations. This provides a high quality simulation in most
  // game scenarios.
  float32 time_step = 1.0f / 60.0f;
  int32 velocity_iterations = 6;
  int32 position_iterations = 2;

  // This is our little game loop
  for (int32 i = 0; i < 300; ++i) {
    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world->Step(time_step, velocity_iterations, position_iterations);

    // Now print the position and angle of the body.
    b2Vec2 position = worm_body->GetPosition();
    float32 angle = worm_body->GetAngle();
    //b2Vec2 speed = body->GetLinearVelocity();

    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
  }

  // When the world destructor is called, all bodies and joints are freed. This
  // can create orphaned pointers, so be careful about your world management.
  std::cin.get();

  return 0;
}

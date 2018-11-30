#include "physics.hpp"
#include "Box2D/Box2D.h"


PhysicsEngine::PhysicsEngine(float world_pos, float32 time_step_) {
  time_step = 1.0f / time_step_;

  // Define the gravity vector
  b2Vec2 gravity = b2Vec2(0.0f, GRAVITATIONAL_FORCE);
  // Construct a world object, which will hold and simulate the rigid bodies
  world = new b2World(gravity);

  // Define the ground body
  b2BodyDef ground_body_def;
  ground_body_def.position.Set(0.0f, world_pos);

  // Call the body factory which allocates memory for the ground body
  // from a pool and creates the ground box shape (also from a pool)
  // The body is also added to the world
  ground_body = world->CreateBody(&ground_body_def);

  // Define the ground box shape
  b2PolygonShape ground_box;

  // The extents are the half-widths of the box
  ground_box.SetAsBox(50.0f, 10.0f);

  // Add the ground fixture to the ground body
  ground_body->CreateFixture(&ground_box, 0.0f);
}

b2World* PhysicsEngine::getWorld() {
  return world;
}

float32 PhysicsEngine::getTimeStep() const {
  return time_step;
}

void PhysicsEngine::setTimeStep(float32 new_time_step) {
  time_step = new_time_step;
}

void PhysicsEngine::step() {
  world->Step(time_step, velocity_iterations, position_iterations);
}

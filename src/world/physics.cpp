#include "physics.hpp"
#include "Box2D/Box2D.h"


PhysicsEngine::PhysicsEngine(float world_pos, float32 in_time_step) {
  time_step = 1.0f / in_time_step;

  // Define the gravity vector
  b2Vec2 gravity = b2Vec2(0.0f, gravitational_force);
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
  ground_box.SetAsBox(ground_width, ground_height);

  b2FixtureDef ground_fixture_def;
  ground_fixture_def.density = 1.f;
  ground_fixture_def.shape = &ground_box;
  ground_fixture_def.filter.categoryBits = 2;
  ground_fixture_def.filter.maskBits = 1;

  // Add the ground fixture to the ground body
  ground_body->CreateFixture(&ground_fixture_def);
}

PhysicsEngine::~PhysicsEngine() {
  delete world;
}

b2World* PhysicsEngine::getWorld() const {
  return world;
}

b2Body* PhysicsEngine::getGround() const {
  return ground_body;
}

const b2Vec2 PhysicsEngine::getGroundDimensions() const {
  return b2Vec2(ground_width, ground_height);
}

void PhysicsEngine::step() {
  world->Step(time_step, velocity_iterations, position_iterations);
}

#include "Box2D/Box2D.h"
//#include "Physics.hpp"
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv) {
  B2_NOT_USED(argc);
  B2_NOT_USED(argv);

  // Define the gravity vector.
  b2Vec2 gravity(0.0f, -9.81f);

  // Construct a world object, which will hold and simulate the rigid bodies.
  b2World world(gravity);

  // Define the ground body.
  b2BodyDef ground_body_def;
  ground_body_def.position.Set(0.0f, -10.0f);

  // Call the body factory which allocates memory for the ground body
  // from a pool and creates the ground box shape (also from a pool).
  // The body is also added to the world.
  b2Body* ground_body = world.CreateBody(&ground_body_def);

  // Define the ground box shape.
  b2PolygonShape ground_box;

  // The extents are the half-widths of the box.
  ground_box.SetAsBox(50.0f, 10.0f);

  // Add the ground fixture to the ground body.
  ground_body->CreateFixture(&ground_box, 0.0f);

  // The amount of joints the user wants the worm to have.
  unsigned int joints_wanted = 2;

  // prev_body is a variable that tells where the new joint should connect.
  b2Body* prev_body = NULL;

  // Define the first bone.

  b2PolygonShape first_bone;
  first_bone.SetAsBox(0.5f, 2.0f);

  b2BodyDef first_body_def;
  first_body_def.type = b2_dynamicBody;
  first_body_def.position.Set(0.0f, 13.0f);
  b2Body* first_body = world.CreateBody(&first_body_def);

  b2FixtureDef first_fixture_def;
  first_fixture_def.shape = &first_bone;
  first_fixture_def.density = 1.0f;
  first_body->CreateFixture(&first_fixture_def);

  // Declaring the previous body for linking the next body to it.
  prev_body = first_body;

  b2Body* new_body = NULL;

  // Define another bone and connect it to the previous one with a joint.
  for (unsigned int amount_of_joints = 0; amount_of_joints < joints_wanted; amount_of_joints++) {
    b2PolygonShape new_bone;
    new_bone.SetAsBox(0.5f, 2.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef new_body_def;
    new_body_def.type = b2_dynamicBody;
    new_body_def.position.Set(0.0f, 7.0f);
    new_body = world.CreateBody(&new_body_def);

    /*
    // Define another box shape for our dynamic body.
    b2EdgeShape bone;
    bone.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f,0.0f));
    */

    // Define the dynamic body fixture.
    b2FixtureDef new_fixture_def;
    new_fixture_def.shape = &new_bone;
    // Set the box density to be non-zero, so it will be dynamic.
    new_fixture_def.density = 1.0f;
    // Override the default friction.
    new_fixture_def.friction = 0.3f;
    // Add the shape to the body.
    new_body->CreateFixture(&new_fixture_def);

    // Defining the joint that links the first bone to the second.
    b2RevoluteJointDef joint_def;
    joint_def.Initialize(prev_body, new_body, b2Vec2(0.0f, 5.0f));
    joint_def.motorSpeed = 5.0f;
    joint_def.maxMotorTorque = 10.0f;
    joint_def.enableMotor = true;
    b2RevoluteJoint* joint = (b2RevoluteJoint*)world.CreateJoint(&joint_def);

    prev_body = new_body;
  }

  // Prepare for simulation. Typically we use a time step of 1/60 of a
  // second (60Hz) and 10 iterations. This provides a high quality simulation
  // in most game scenarios.
  float32 time_step = 1.0f / 60.0f;
  int32 velocity_iterations = 6;
  int32 position_iterations = 2;



  // This is our little game loop.
  for (int32 i = 0; i < 300; ++i) {
    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world.Step(time_step, velocity_iterations, position_iterations);

    // Now print the position and angle of the body.
    b2Vec2 position = new_body->GetPosition();
    float32 angle = new_body->GetAngle();
    b2Vec2 speed = new_body->GetLinearVelocity();

    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
  }

  // When the world destructor is called, all bodies and joints are freed. This can
  // create orphaned pointers, so be careful about your world management.
  std::cin.get();
  return 0;
}
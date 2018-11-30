#include <vector>

#include "body.hpp"
#include "Box2D/Box2D.h"


WormBody::WormBody(
        std::vector<int> list,
        unsigned int len
) : angles(list), len(len) {}

void WormBody::increase_angle(int num) {
  change_angle(num, angle_change);
}

void WormBody::decrease_angle(int num) {
  change_angle(num, -angle_change);
}

void WormBody::change_angle(int num, int change) {
  angles[num] += change;
  count++;
}

int WormBody::getAngleChange() const {
  return angle_change;
}

unsigned int WormBody::get_len() const {
  return len;
}

int WormBody::get_angle(unsigned int num) const {
  return angles[num];
}

unsigned long WormBody::get_joint_amount() const {
  return angles.size();
}

unsigned int WormBody::get_count() const {
  return count;
}

const std::vector<int> WormBody::get_all_angles() const {
  return angles;
}

b2Body* WormBody::createB2Body(b2World* world) const {
  // The amount of joints the user wants the worm to have
  unsigned long joints_wanted = get_joint_amount();

  // prev_body is a variable that tells where the new joint should connect
  b2Body* prev_body = createBone(world);
  b2Body* new_body = nullptr;

  // Define another bone and connect it to the previous one with a joint
  for (unsigned joint = 0; joint < joints_wanted; joint++) {
    new_body = createBone(world);

    // Defining the joint that links the first bone to the second
    b2RevoluteJointDef joint_def;
    joint_def.Initialize(prev_body, new_body, b2Vec2(0.0f, 5.0f));
    joint_def.motorSpeed = 5.0f;
    joint_def.maxMotorTorque = 10.0f;
    joint_def.enableMotor = true;
    world->CreateJoint(&joint_def);

    prev_body = new_body;
  }

  return prev_body;
}

b2Body* WormBody::createBone(b2World* world) const {
  b2PolygonShape bone;
  bone.SetAsBox(bone_width, bone_length);

  // Define the dynamic body, we set its position and call the body factory
  b2BodyDef body_def;
  body_def.type = b2_dynamicBody;
  body_def.position.Set(0.0f, 13.0f);
  b2Body* body = world->CreateBody(&body_def);

  b2FixtureDef fixture_def;
  fixture_def.shape = &bone;
  // Set the box density to be non-zero, so it will be dynamic
  fixture_def.density = 1.0f;
  // Override the default friction
  fixture_def.friction = 0.3f;

  // Add the shape to the body
  body->CreateFixture(&fixture_def);
  return body;
}

#include "body.hpp"
#include "Box2D/Box2D.h"


void WormBody::init(unsigned int bone_amount) {
  // FIXME(Cookie): throw an initialization error if bone_amount == 0
  joints = std::vector<b2Joint*>(bone_amount - 1);
  bones = std::vector<b2Body*>(bone_amount);
}

WormBody::WormBody(unsigned int bone_amount) : bone_amount(bone_amount) {
  init(bone_amount);
}

WormBody::WormBody(
        b2World* world,
        unsigned int bone_amount) :
        bone_amount(bone_amount)
{
  init(bone_amount);
  createBodyParts(world);
}

int WormBody::getAngleChange() const {
  return angle_change;
}

unsigned int WormBody::getBoneAmount() const {
  return bone_amount;
}

unsigned int WormBody::getCount() const {
  return count;
}

b2Body* WormBody::createB2Body(b2World* world) {
  // The amount of joints the user wants the worm to have
  unsigned long joints_wanted = getBoneAmount();

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

void WormBody::createBodyParts(b2World* world) {
  b2BodyDef body_def;
  body_def.type = b2_dynamicBody;
  body_def.position.Set(0.f, 13.f);
  body_def.linearDamping = 0.f;
  body_def.angularDamping = 0.01f;
  body_def.allowSleep = false;
  body_def.awake = true;

  b2PolygonShape body_shape;
  body_shape.SetAsBox(bone_width, bone_length);

  b2FixtureDef body_fixture;
  body_fixture.shape = &body_shape;
  body_fixture.density = 1.0f;
  body_fixture.filter.categoryBits = 1;
  body_fixture.filter.maskBits = 2;
}

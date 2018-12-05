#include <string>
#include <sstream>

#include "body.hpp"
#include "Box2D/Box2D.h"
#include "body-exceptions.hpp"


void WormBody::init(unsigned int bone_amount) {
  if (bone_amount == 0) {
    throw QLearningExceptions::BodyRuntimeException(
        "Bone amount has to be greater than zero!");
  }

  joints = std::vector<b2Joint*>(bone_amount - 1);
  bones = std::vector<b2Body*>(bone_amount);
}

WormBody::WormBody(unsigned int bone_amount) : bone_amount(bone_amount) {
  init(bone_amount);
}

WormBody::WormBody(
        b2World* world,
        unsigned int bone_amount) :
        bone_amount(bone_amount) {
  init(bone_amount);
  createBodyParts(world);
}

void WormBody::checkInitialization(std::string message) const {
  if (!initialized) {
    throw QLearningExceptions::BodyRuntimeException(message);
  }
}

const b2Joint* WormBody::getJoint(unsigned int index) const {
  if (index >= joints.size()) {
    throw QLearningExceptions::BodyRuntimeException(
            "Index "
            + std::to_string(index)
            + " is larger than or equal to joints list length: "
            + std::to_string(joints.size()));
  }

  return joints[index];
}

float32 WormBody::getJointAngle(unsigned int index) const {
  auto tmp = (b2RevoluteJoint*) getJoint(index);
  return tmp->GetJointAngle();
}

unsigned int WormBody::getBoneAmount() const {
  return bone_amount;
}

std::vector<b2Body*> WormBody::getBones() const {
  checkInitialization("Bot bones not initialized!");
  return bones;
}

std::vector<b2Joint*> WormBody::getJoints() const {
  checkInitialization("Bot joints not initialized!");
  return joints;
}

void WormBody::setJointAngle(unsigned int index, float angle) {
  float32 current_angle = getJointAngle(index);

  float32 lower, upper, direction;
  bool motor_enabled = true;
  if (current_angle > angle) {
    lower = angle;
    upper = current_angle;
    direction = -1.f;
  } else if (current_angle < angle) {
    lower = current_angle;
    upper = angle;
    direction = 1.f;
  } else {
    lower = current_angle;
    upper = current_angle;
    direction = 0.f;
    motor_enabled = false;
  }

  auto joint = (b2RevoluteJoint*) getJoint(index);
  joint->SetLimits(lower, upper);
  joint->SetMotorSpeed(motor_speed * direction);
  joint->EnableMotor(motor_enabled);
}

const std::tuple<float, float> WormBody::getCoordinatesTuple() const {
  float x = 0.f;
  float y = 0.f;

  for (auto bone : bones) {
    auto tmp = bone->GetWorldCenter();
    x += tmp.x;
    y += tmp.y;
  }

  x /= bones.size();
  y /= bones.size();
  return std::make_tuple(x, y);
}

const b2Vec2 WormBody::getCoordinatesVector() const {
  std::tuple<float, float> tmp = getCoordinatesTuple();
  return b2Vec2(std::get<0>(tmp), std::get<1>(tmp));
}

const std::tuple<float, float> WormBody::getBoneDimensions() const {
  return std::make_tuple(bone_width, bone_length);
}

b2BodyDef WormBody::createBodyDef() const {
  b2BodyDef body_def;

  body_def.type = b2_dynamicBody;
  body_def.position.Set(0.f, 13.f);
  body_def.linearDamping = linear_damping;
  body_def.angularDamping = angular_damping;
  body_def.allowSleep = false;
  body_def.awake = true;

  return body_def;
}

b2PolygonShape WormBody::createBodyShape() const {
  b2PolygonShape body_shape;
  body_shape.SetAsBox(bone_width, bone_length);

  return body_shape;
}

b2FixtureDef WormBody::createBodyFixtureDef(const b2PolygonShape* shape) const {
  b2FixtureDef body_fixture;
  body_fixture.shape = shape;
  // Set the box density to be non-zero, so it will be dynamic
  body_fixture.density = density;
  // Override the default friction
  body_fixture.friction = friction;
  body_fixture.filter.categoryBits = 1;
  body_fixture.filter.maskBits = 2;

  return body_fixture;
}

inline int WormBody::calculateDistance(
    unsigned int index,
    unsigned int offset) const
{
  return ((int) bone_width) * index - offset;
}

b2RevoluteJointDef WormBody::createJoint(unsigned int index) const {
  b2RevoluteJointDef joint_def;
  joint_def.enableLimit = true;
  joint_def.enableMotor = false;
  joint_def.upperAngle = 0;
  joint_def.lowerAngle = 0;
  joint_def.motorSpeed = motor_speed;
  joint_def.maxMotorTorque = 200000;

  joint_def.Initialize(
      bones[index - 1],
      bones[index],
      b2Vec2(calculateDistance(index - 1), 0)
  );

  return joint_def;
}

void WormBody::createBodyParts(b2World* world) {
  // Set initialization flag to true
  initialized = true;

  b2BodyDef body_def = createBodyDef();
  b2PolygonShape body_shape = createBodyShape();
  b2FixtureDef body_fixture = createBodyFixtureDef(&body_shape);

  body_def.position.Set(0, y_distance);
  b2Body* first_body = world->CreateBody(&body_def);
  first_body->CreateFixture(&body_fixture);

  bones[0] = first_body;
  for (unsigned int i = 1; i < bone_amount; ++i) {
    body_def.position.Set(calculateDistance(i, 0), y_distance);
    b2Body* body = world->CreateBody(&body_def);
    body->CreateFixture(&body_fixture);
    bones[i] = body;

    b2RevoluteJointDef joint_def = createJoint(i);
    joints[i - 1] = (b2RevoluteJoint*) world->CreateJoint(&joint_def);
  }
}

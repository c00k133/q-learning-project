#include <ctgmath>

#include "brain.hpp"
#include "body.hpp"


void WormBrain::init(int in_precision, float max_error) {
  precision = in_precision;
  rotate_size = 2.0 * M_PI / precision;
  maximum_error = rotate_size / max_error;
}

WormBrain::WormBrain(
        WormBody* body,
        QLearning* qLearning,
        int precision,
        float max_error
): body(body), qLearning(qLearning) {
  init(precision, max_error);
}

WormBrain::WormBrain(
        int precision,
        b2World *world,
        float max_error,
        unsigned int bone_amount) {
  init(precision, max_error);

  body = new WormBody(world, bone_amount);
  auto joint_amount = (unsigned int) body->getJoints().size();
  auto states = (unsigned int) pow(precision, joint_amount);
  qLearning = new QLearning(states, 1 + joint_amount * 2);
}

WormBrain::~WormBrain() {
  delete body;
  delete qLearning;
}

int WormBrain::getCount() {
  return count;
}

const b2Vec2 WormBrain::getBodyCoordinatesVector() const {
  return body->getCoordinatesVector();
}

const std::tuple<float, float> WormBrain::getBodyCoordinatesTuple() const {
  return body->getCoordinatesTuple();
}

const std::tuple<float, float> WormBrain::getBodyBoneDimensions() const {
  return body->getBoneDimensions();
}

std::vector<b2Body*> WormBrain::getBodyBones() const {
  return body->getBones();
}

std::vector<b2Joint*> WormBrain::getBodyJoints() const {
  return body->getJoints();
}

unsigned int WormBrain::updateState(unsigned int state, unsigned int action) {
  // 0 == take no action
  if (action == 0) {
    next_rotation = 0;
    return state;
  }

  int change = 2 * (action % 2) - 1;
  unsigned int joint = (action + 1) / 2 - 1;

  next_rotation = change;
  next_joint = joint;

  double precision_joint = pow(precision, joint);
  auto old_angle =
      static_cast<unsigned int>(state / precision_joint) % precision;
  int new_angle = ((int) (old_angle + change) < 0 ?
    precision + (old_angle + change) : old_angle + change) % precision;

  auto return_state = static_cast<unsigned int>(
      state + (new_angle - old_angle) * precision_joint);
  return return_state;
}

void WormBrain::act(bool random, float curiosity) {
  next_action = random ?
    qLearning->getRandomAction(curiosity) : qLearning->calculateBestAction();

  unsigned int new_state = updateState(qLearning->getState(), next_action);
  qLearning->setFutureState(new_state);
}

bool WormBrain::inspectAngle(unsigned int index, double change) const {
  float angle = body->getJointAngle(index);
  double diff = angle - change;
  return diff > maximum_error || diff < -maximum_error;
}

void WormBrain::process() {
  float wormPositionX = std::get<0>(body->getCoordinatesTuple());
  float reward = wormPositionX - current_body_position_x;
  current_body_position_x = wormPositionX;

  qLearning->updateMatrix(reward, next_action);
  act(false);

  auto joint_angle_change = (float) rotate_size * next_rotation;
  bool valid = inspectAngle(next_joint, joint_angle_change);
  if (valid) {
    body->setJointAngle(next_joint, joint_angle_change);
  }

  ++count;
}

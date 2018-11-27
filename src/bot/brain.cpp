#include <ctgmath>

#include "brain.hpp"
#include "body.hpp"


WormBrain::WormBrain(
        WormBody body,
        QLearning qLearning,
        int precision,
        float max_error): BotBrain(body, qLearning), precision(precision) {
  rotate_size = 2.0 * M_PI / precision;
  maximum_error = rotate_size / max_error;
}

int WormBrain::getCount() {
  return count;
}

unsigned int WormBrain::updateState(unsigned int state, unsigned int action) {
  int change = -1 + (2 * (action % 2));
  unsigned int joint = (action + 1) / 2 - 1;

  next_rotation = change;
  next_joint = joint;

  double precision_joint = pow(precision, joint);
  auto old_angle =
      static_cast<unsigned int>(state / precision_joint) % precision;
  int new_angle = (old_angle + change < 0 ?
    precision + (old_angle + change) : old_angle + change) % precision;

  auto return_state = static_cast<unsigned int>(
      state + (new_angle - old_angle) * precision_joint);
  return return_state;
}

void WormBrain::act(bool random, float curiosity) {
  next_action = random ?
    qLearning.getRandomAction(curiosity) : qLearning.calculateBestAction();

  unsigned int new_state = updateState(qLearning.getState(), next_action);
  qLearning.setFutureState(new_state);
}

bool WormBrain::inspectAngle(unsigned int index, double change) const {
  // TODO(Cookie): wait for implementation of getJoints
  double diff = 0.0 - change;
  return diff > maximum_error || diff < -maximum_error;
}

void WormBrain::process() {
  float wormPositionX = 0.0f;  // TODO(Cookie): wait for implementation
  float reward = wormPositionX - current_body_position_x;
  current_body_position_x = wormPositionX;

  qLearning.updateMatrix(reward, next_action);
  act(false);

  double joint_angle_change = rotate_size * next_rotation;
  bool valid = inspectAngle(next_joint, joint_angle_change);
  if (valid) {
    // TODO(Cookie): update joint angle
  }

  ++count;
}

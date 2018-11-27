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

int WormBrain::updateState(int state, int action) {
  int change = -1 + (2 * (action % 2));
  int joint = (action + 1) / 2 - 1;

  next_rotation = change;
  next_joint = joint;

  double precision_joint = pow(precision, joint);
  int old_angle = static_cast<int>(state / precision_joint) % precision;
  int new_angle = (old_angle + change < 0 ?
    precision + (old_angle + change) : old_angle + change) % precision;

  int return_state =
    static_cast<int>(state + (new_angle - old_angle) * precision_joint);
  return return_state;
}

void WormBrain::act(int dir, float curiosity) {
  next_action = dir == 0 ?
    qLearning.calculateBestAction() : qLearning.getRandomAction(curiosity);

  next_state = updateState(qLearning.getState(), next_action);
}

bool WormBrain::checkAllAngles() const {
  unsigned int jointAmount = 0;  // TODO(Cookie): get method from body
  for (unsigned int i = 0; i < jointAmount; i++) {
    double diff = 0.0;  // TODO(Cookie): wait for implementation of getJoints
    if (diff > maximum_error || diff < -maximum_error)
      return false;
  }
  return true;
}

void WormBrain::process() {
  bool angleCheck = checkAllAngles();
  if (angleCheck) {
    float wormPositionX = 0.0f;  // TODO(Cookie): wait for implementation
    float reward = wormPositionX - 0.0f;  // TODO(Cookie): get body position
    qLearning.updateMatrix(reward);
    // TODO(Cookie): implement update of body current position
    act(0, 0.1f);

    float joint_angle_change = rotate_size * next_rotation;
    next_joint;  // TODO(Cookie): update some intermediate container
  }
  ++count;
}

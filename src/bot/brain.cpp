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
        b2World *world,
        int precision,
        unsigned int bone_amount,
        float max_error) {
  init(precision, max_error);

  body = new WormBody(world, bone_amount);
  auto joint_amount = body->getJointAmount();
  auto states = (unsigned int) pow(precision, joint_amount);
  qLearning = new QLearning(states, 1 + joint_amount * 2);

  saved_angles = std::vector<float>(joint_amount, 0.f);
}

WormBrain::~WormBrain() {
  delete body;
  delete qLearning;
}

int WormBrain::getCount() {
  return count;
}

void WormBrain::setRandomActs(bool choice) {
  random_act = choice;
}

void WormBrain::setDebug(unsigned int frequency) {
  qLearning->setDebug(frequency);
  debug_frequency = frequency;
}

void WormBrain::setBodyColor(sf::Color body_color) {
  body->setBodyColor(body_color);
}

void WormBrain::setBodyOutlineColor(sf::Color outline_color) {
  body->setBodyOutlineColor(outline_color);
}

const b2Vec2 WormBrain::getBodyCoordinatesVector() const {
  return body->getCoordinatesVector();
}

const std::tuple<float, float> WormBrain::getBodyCoordinatesTuple() const {
  return body->getCoordinatesTuple();
}

const WormBody* WormBrain::getBody() const {
  return body;
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
      static_cast<int>(state / precision_joint) % precision;
  int combined = old_angle + change;
  int new_angle = (combined + (combined < 0 ? precision : 0)) % precision;

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

inline bool WormBrain::inspectAngle(unsigned int index, double change) const {
  float angle = body->getJointAngle(index);
  double diff = angle - change;
  return diff <= maximum_error && diff >= -maximum_error;
}

bool WormBrain::inspectAngles() {
  unsigned int joint_amount = body->getJointAmount();
  bool flag = true;

  for (unsigned int i = 0; i < joint_amount; ++i) {
    float saved_angle = saved_angles[i];
    if (!inspectAngle(i, saved_angle)) {
      body->setJointAngle(i, saved_angle);
      flag = false;
    }
  }

  return flag;
}

void WormBrain::process() {
  bool will_continue = inspectAngles();
  if (will_continue) {
    // Calculate reward based on movement in x direction
    float worm_position_x = std::get<0>(body->getCoordinatesTuple());
    float reward = worm_position_x - current_body_position_x;
    current_body_position_x = worm_position_x;

    qLearning->updateMatrix(reward, next_action);
    act(random_act);

    auto joint_angle_change = (float) rotate_size * next_rotation;
    saved_angles[next_joint] += joint_angle_change;
  }

  ++count;

  if (debug_frequency != 0 && count % debug_frequency == 0) {
    std::cout << "-------------------------------" << std::endl << std::endl;
  }
}

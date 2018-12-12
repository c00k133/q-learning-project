#include <ctgmath>

#include "brain.hpp"
#include "body.hpp"


void WormBrain::init(int in_precision, float max_error, std::string _name) {
  name = _name;
  precision = in_precision;
  rotate_size = 2.0 * M_PI / precision;
  maximum_error = rotate_size / max_error;
}

WormBrain::WormBrain(
        WormBody* body,
        QLearning* qLearning,
        int precision,
        float max_error,
        std::string name
): body(body), qLearning(qLearning) {
  init(precision, max_error, name);
}

WormBrain::WormBrain(
        b2World& world,
        int precision,
        unsigned int bone_amount,
        float max_error,
        std::string name) {
  init(precision, max_error, name);

  body = std::shared_ptr<WormBody>(new WormBody(world, bone_amount));
  auto joint_amount = body->getJointAmount();
  auto states = (unsigned int) pow(precision, joint_amount);
  qLearning = std::unique_ptr<QLearning>(new QLearning(states, 1 + joint_amount * 2));
}

int WormBrain::getCount() {
  return count;
}

const std::string WormBrain::getName() const {
  return name;
}

bool WormBrain::getRandomAct() const {
  return random_act;
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

const std::shared_ptr<WormBody> WormBrain::getBody() const {
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

void WormBrain::process() {
  unsigned int last_joint = std::get<0>(saved_angle);
  float last_angle = std::get<1>(saved_angle);

  if (inspectAngle(last_joint, last_angle)) {
    // Calculate reward based on movement in x direction
    float worm_position_x = std::get<0>(body->getCoordinatesTuple());
    float reward = worm_position_x - current_body_position_x;
    current_body_position_x = worm_position_x;

    qLearning->updateMatrix(reward, next_action);
    act(random_act);

    auto joint_angle_change = (float) rotate_size * next_rotation;
    saved_angle = std::make_tuple(next_joint, last_angle + joint_angle_change);
  } else {
    body->setJointAngle(last_joint, last_angle);
  }

  ++count;
}

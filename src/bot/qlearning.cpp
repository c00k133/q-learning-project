#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "qlearning.hpp"


QLearning::QLearning(
        unsigned int states,
        unsigned int actions,
        double gamma,
        double alpha
) : states(states), actions(actions), gamma(gamma), alpha(alpha) {
  q_matrix =
    std::vector<std::vector<double>>(states, std::vector<double>(actions, 0.0));

  // Set RNG for later use
  srand((unsigned) time(nullptr));
}

unsigned int QLearning::getState() const {
  return state;
}

int QLearning::getAccuracy() const {
  return accuracy;
}

void QLearning::setDebug(unsigned int frequency) {
  debug_frequency = frequency;
}

bool QLearning::print() const {
  return debug_frequency != 0 && counter % debug_frequency == 0;
}

void QLearning::printMatrix() const {
  for (unsigned int r = 0; r < states; ++r) {
    std::cout << r << '\t';
    for (unsigned int c = 0; c < actions; ++c) {
      printf("%.4f\t", q_matrix[r][c]);
    }
    std::cout << std::endl;
  }
}

float QLearning::setReward(float changeAmount) {
  float change = move_reward + changeAmount;
  // Bounds check for change: 0.0 <= move_reward <= 10.0
  move_reward = change < 0.f ? 0.f : (change > 10.f ? 10.f : change);
  return move_reward;
}

float QLearning::getReward() const {
  return move_reward;
}

void QLearning::setFutureState(unsigned int state) {
  future_state = state;
}

void QLearning::setRandomBestAction(bool randomize) {
  random_best_action = randomize;
}

unsigned int QLearning::calculateBestAction() {
  // Randomization here ensures that bots do have the same start position
  unsigned int current_best = random_best_action ? rand() % actions : 0;
  double current_max = q_matrix[state][current_best];

  for (unsigned int i = random_best_action ? 0 : 1; i < actions; ++i) {
    if (q_matrix[state][i] > current_max) {
      current_max = q_matrix[state][i];
      current_best = i;
    }
  }

  if (print()) {
    std::cout
      << "QLearning - best calculated action: "
      << current_best
      << std::endl;
  }

  return current_best;
}

double QLearning::getMaxActionValue(unsigned int state) {
  double current_max = 0.0;

  for (unsigned int i = 0; i < actions; i++) {
    if (q_matrix[state][i] > current_max) {
      current_max = q_matrix[state][i];
    }
  }

  if (print()) {
    std::cout
      << "QLearning - max action value: "
      << current_max
      << std::endl;
  }

  return current_max;
}

inline double QLearning::qValueBounded(
    unsigned int index,
    double else_value,
    double lower_bound
) {
  double tmp = q_matrix[state][index];
  return tmp <= lower_bound ? else_value : tmp;
}

unsigned int QLearning::getRandomAction(float curiosity) {
  double sum = 0.0;
  for (unsigned int i = 0; i < actions; i++) {
    sum += qValueBounded(i, curiosity);
  }

  double ratio = accuracy / sum;
  int count = static_cast<int>(ratio * qValueBounded(0, curiosity));
  int random = rand() % accuracy;

  unsigned int choose = 0;
  for (unsigned int i = 0; i < actions; i++) {
    if (random < count) {
      choose = i;
      break;
    } else {
      count += static_cast<int>(ratio * qValueBounded(i + 1, curiosity));
    }
  }

  if (print()) {
    std::cout
      << "QLearning - "
      << "sum: " << sum
      << "count: " << count
      << std::endl;
  }

  return choose;
}

inline double QLearning::calculateNewValue(
    float reward,
    double max_q,
    unsigned int next_action
) {
  return alpha *
      (reward - move_reward + gamma * max_q - q_matrix[state][next_action]);
}

void QLearning::updateMatrix(float reward, unsigned int next_action) {
  double max_q = getMaxActionValue(future_state);
  double calculate_value = calculateNewValue(reward, max_q, next_action);

  // Update the matrix
  q_matrix[state][next_action] += calculate_value;

  // Update state
  state = future_state;

  ++counter;
}

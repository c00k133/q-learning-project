#include <vector>
#include <ctime>
#include <cstdlib>

#include "qlearning.hpp"


QLearning::QLearning(
        unsigned int states,
        unsigned int actions,
        int step
) : states(states), actions(actions), step(step) {
  q_matrix =
    std::vector<std::vector<double>>(states, std::vector<double>(actions, 0.0));

  // Set RNG for later use
  srand((unsigned) time(nullptr));
}

void QLearning::act(float curiosity) {
  // TODO(Cookie): flesh out when rest of the class is implemented
}

float QLearning::setReward(float changeAmount) {
  float change = move_reward + changeAmount;
  // Bounds check for change: 0.0 <= move_reward <= 10.0
  move_reward = change < 0.f ? 0.f : (change > 10.f ? 10.f : change);
  return move_reward;
}

int QLearning::calculateBestAction() {
  int current_best = 0;
  double current_max = q_matrix[state][current_best];

  for (unsigned int i = 1; i < actions; i++) {
    if (q_matrix[state][i] > current_max) {
      current_max = q_matrix[state][i];
      current_best = i;
    }
  }

  return current_best;
}

double QLearning::getMaxActionValue() {
  double current_max = 0.0;

  for (unsigned int i = 0; i < actions; i++) {
    if (q_matrix[state][i] > current_max) {
      current_max = q_matrix[state][i];
    }
  }

  return current_max;
}

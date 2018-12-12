#include <vector>

#include "gtest/gtest.h"
#include "qlearning.hpp"
#include "test_utils.hpp"


TEST(qlearning_generic_test, matrix_test) {
  const int16 columns = 5;
  const int16 rows = 5;
  QLearning qLearning = QLearning(columns, rows, 0.5);

  for (unsigned int i = 0; i < columns; ++i) {
    double max_action_value = qLearning.getMaxActionValue(i);
    EXPECT_EQ(max_action_value, 0.0);
  }
}

TEST(qlearning_generic_test, rewards_bounds_test) {
  QLearning qLearning = QLearning(0, 0, 0.5);

  // Test lower bound
  const float reward_lower_bound = -5.f;
  qLearning.setReward(reward_lower_bound);
  EXPECT_EQ(qLearning.getReward(), 0.f);

  // Test upper bound
  const float reward_upper_bound = 25.f;
  qLearning.setReward(reward_upper_bound);
  EXPECT_EQ(qLearning.getReward(), 10.f);
}

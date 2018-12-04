#include <vector>

#include "gtest/gtest.h"
#include "body.hpp"
#include "test_utils.hpp"


TEST(body_test_generic, test_counter) {
  TestUtils utils = TestUtils(10, 20);
  WormBody body = utils.createWormBody(utils.getRandomInt());

  static const unsigned int count_default = 0;
  EXPECT_EQ(count_default, body.get_count());

  const int rni = utils.getRandomInt();
  int angle = utils.setBoundsAndGetInt(0, body.get_len());
  for (int i = 0; i < rni; ++i) {
    body.decrease_angle(angle);
    EXPECT_EQ(i + 1, body.get_count());
    angle = utils.getRandomInt();
  }
}

TEST(body_test_generic, test_angles) {
  TestUtils utils = TestUtils(10, 20);
  int vector_length = utils.getRandomInt();
  WormBody body = utils.createWormBody(vector_length);
  std::vector<int> reference = std::vector<int>(vector_length, 0);

  // Initialized vector should be filled with zeros
  EXPECT_EQ(body.get_all_angles(), reference);

  const int rni = utils.getRandomInt();
  int angle = utils.setBoundsAndGetInt(0, body.get_len());
  for (int i = 0; i < rni; ++i) {
    bool decrease_or_increase = utils.getRandomInt() % 2 == 0;
    if (decrease_or_increase) {
      body.decrease_angle(angle);
      reference[angle] -= body.getAngleChange();
    } else {
      body.increase_angle(angle);
      reference[angle] += body.getAngleChange();
    }
    angle = utils.getRandomInt();
    EXPECT_EQ(body.get_all_angles(), reference);
  }
}

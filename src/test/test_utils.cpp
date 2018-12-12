#include <random>
#include <vector>

#include "test_utils.hpp"


TestUtils::TestUtils(int lower, int upper) {
  distribution = std::uniform_int_distribution<int>(lower, upper);
}

int TestUtils::getRandomInt() {
  return distribution(generator);
}

void TestUtils::setBounds(int lower, int upper) {
  distribution = std::uniform_int_distribution<int>(lower, upper);
}

int TestUtils::setBoundsAndGetInt(int lower, int upper) {
  setBounds(lower, upper);
  return getRandomInt();
}

std::vector<std::vector<double>> TestUtils::create2DVector(
        int16 columns, int16 rows, double values) {
  return std::vector<std::vector<double>>(
          columns, std::vector<double>(rows, values));
}

unsigned int TestUtils::getTestAmount() const {
  return default_test_amount;
}

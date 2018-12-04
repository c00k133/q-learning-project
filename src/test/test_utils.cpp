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

WormBody TestUtils::createWormBody(int vector_length, int default_value) const {
  std::vector<int> angles = std::vector<int>(vector_length, default_value);
  return WormBody(angles);
}

std::vector<std::vector<double>> TestUtils::create2DVector(
        unsigned long columns,
        unsigned long rows,
        double values
) {
  return std::vector<std::vector<double>>(
          columns, std::vector<double>(rows, values));
}

unsigned int TestUtils::getTestAmount() const {
  return default_test_amount;
}

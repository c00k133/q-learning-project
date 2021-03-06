#ifndef Q_LEARNING_TEST_UTILS_H
#define Q_LEARNING_TEST_UTILS_H

#include <random>
#include <vector>
#include <body.hpp>


class TestUtils {
 public:
    explicit TestUtils(int lower = 0, int upper = 100);
    int getRandomInt();
    void setBounds(int lower, int upper);
    int setBoundsAndGetInt(int lower, int upper);
    std::vector<std::vector<double>> create2DVector(
            int16 columns, int16 rows, double values = 0.0);
    unsigned int getTestAmount() const;

 private:
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;

    static constexpr unsigned int default_test_amount = 10;
};

#endif  // Q_LEARNING_TEST_UTILS_H

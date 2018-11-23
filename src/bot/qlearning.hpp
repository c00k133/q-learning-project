#ifndef QLEARNING_HPP
#define QLEARNING_HPP

#include <vector>


class QLearning {
 public:
    QLearning(unsigned int states, unsigned int actions, int step);

    void act(float curiosity = 0.1f);
    float setReward(float changeAmount);
    int calculateBestAction();
    double getMaxActionValue();

 private:
    unsigned int states;
    unsigned int actions;
    std::vector<std::vector<double>> q_matrix;
    int step;

    float move_reward = 0.1f;
    unsigned int state = 0;
};


#endif  // QLEARNING_HPP

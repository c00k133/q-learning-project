#ifndef QLEARNING_HPP
#define QLEARNING_HPP

#include <vector>


class QLearning {
 public:
    QLearning(unsigned int states, unsigned int actions, int step);

    float setReward(float changeAmount);
    void act(float curiosity = 0.1f);

    /**
     * Calculates the best action in the Q-matrix in the current state.
     * I.e. the largest value in the Q-matrix.
     * @return the best current action
     */
    int calculateBestAction();
    /**
     * Get the current best action of the algorithm.
     * I.e. get the largest value from the Q-matrix.
     * @return current best action in whole Q-matrix
     */
    double getMaxActionValue();
    /**
     * Get a random action from the Q-matrix.
     * @param curiosity substitute for Q-values <= 0
     * @return random action from the Q-matrix
     */
    int getRandomAction(float curiosity = 0.1f);

    void updateMatrix(float reward);

 private:
    /**
     * Get bounded values out of the Q-matrix.
     * If a value is lower than set amount, return lower bound.
     * @param index index of matrix
     * @param else_value default value if under bound
     * @param lower_bound adhering lower bound
     * @return value of matrix at index i if over lower bound, else else_value
     */
    inline double qValueBounded(
        unsigned int index,
        double else_value = 0.0,
        double lower_bound = 0.0
    );

    unsigned int states;  // Number of states; number of matrix columns
    unsigned int actions;  // Number of actions; number of matrix rows
    std::vector<std::vector<double>> q_matrix;
    int step;

    float move_reward = 0.1f;
    // Current state of this Q-algorithm
    unsigned int state = 0;
    // Number of times this Q-algorithm has acted
    unsigned int number_of_acts = 0;

    static const int accuracy = 100000;
};


#endif  // QLEARNING_HPP

#ifndef QLEARNING_HPP
#define QLEARNING_HPP

#include <vector>


/**
 * Q learning class.
 *
 * Works as a container class for larger Q-learning implementations.
 */
class QLearning {
 public:
    /**
     * Q learning instantiation.
     * @param states number of states in this Q algorithm; matrix columns amount
     * @param actions number of actions in this Q algorithm; matrix row amount
     * @param gamma gamma value used in Q matrix update calculations
     */
    QLearning(
            unsigned int states,
            unsigned int actions,
            double gamma);

    /**
     * Getter for current state of this Q object.
     * @return current state of this Q object
     */
     unsigned int getState() const;
     int getAccuracy() const;

    /**
     * Setter for move reward.
     * @param changeAmount new move reward
     * @return the update move reward
     */
    float setReward(float changeAmount);

    /**
     * Getter for move reward.
     * Currently used for testing.
     * @return current move reward
     */
    float getReward() const;

    /**
     * Setter for future state.
     * @param state new future state
     */
    void setFutureState(unsigned int state);

    /**
     * Calculates the best action in the Q-matrix in the current state.
     * I.e. the largest value in the Q-matrix.
     * @return the best current action
     */
    unsigned int calculateBestAction();
    /**
     * Get the current best action of the algorithm for a certain state.
     * I.e. get the largest value from the Q-matrix for a state.
     * @return current best action in whole Q-matrix for a certain state
     */
    double getMaxActionValue(unsigned int state);
    /**
     * Get a random action from the Q-matrix.
     * @param curiosity substitute for Q-values <= 0
     * @return random action from the Q-matrix
     */
    unsigned int getRandomAction(float curiosity = 0.1f);

    /**
     * Update the Q matrix with a certain reward in mind.
     * @param reward the reward to address in updating
     */
    void updateMatrix(float reward, unsigned int next_action);

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
        double lower_bound = 0.0);

    /**
     * The transition rule of Q learning.
     * @param reward possible reward that can be attained
     * @param max_q maximum value of Q matrix, calculated separately
     * @return the newly calculate value
     */
    inline double calculateNewValue(
        float reward,
        double max_q,
        unsigned int next_action);

    unsigned int states;  // Number of states; number of matrix columns
    unsigned int actions;  // Number of actions; number of matrix rows
    std::vector<std::vector<double>> q_matrix;  // Storage for Q matrix

    unsigned int state = 0;  // Current state of this Q-algorithm
    unsigned int future_state = 0;  // Next state to take in future iteration

    float move_reward = 0.1f;  // Reward for moving, default to 0.1f
    double gamma;  // Gamma value used in Q calculation, range 0.0 - 1.0

    // Accuracy used in calculations, same for all QLearning instances
    static const int accuracy = 100000;
};


#endif  // QLEARNING_HPP

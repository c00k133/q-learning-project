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
            double gamma = 0.8,
            double alpha = 0.8);

    /**
     * Getter for current state of this Q object.
     * @return current state of this Q object
     */
     unsigned int getState() const;
     /**
      * Getter for accuracy
      * @return accuracy as an int
      */
     int getAccuracy() const;

     /**
      * Setter for debugging frequency, set to 0 for no printing.
      * @param frequency debugging frequency
      */
     void setDebug(unsigned int frequency);

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
     * Setter for randomizing best action calculation.
     * Setting this to true will randomize which initial best action is chosen
     * before actually iterating through all actions. This being true will
     * ensure that bots will initialize differently resulting in different
     * learning outcomes.
     * @param randomize true for randomization, false otherwise
     */
    void setRandomBestAction(bool randomize);

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

    /** Method for printing the whole q-matrix. */
    void printMatrix() const;

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

    /**
     * Helper method for checking when to print debugging info based on
     * frequency.
     * @return print if true, else do not
     */
    bool print() const;

    // Randomize initial current best for varying learning results
    bool random_best_action = true;

    // Counter used for debugging.
    unsigned int counter;

    // Debugging frequency, 0 aor no printing
    unsigned int debug_frequency = 0;

    unsigned int states;  // Number of states; number of matrix columns
    unsigned int actions;  // Number of actions; number of matrix rows
    std::vector<std::vector<double>> q_matrix;  // Storage for Q matrix

    unsigned int state = 0;  // Current state of this Q-algorithm
    unsigned int future_state = 0;  // Next state to take in future iteration

    float move_reward = 0.1f;  // Reward for moving, default to 0.1f
    double gamma;  // Gamma value used in Q calculation, range 0.0 - 1.0
    double alpha;  // Alpha value used in Q calculation, range 0.0 -1.0;

    // Accuracy used in calculations, same for all QLearning instances
    static const int accuracy = 100000;
};


#endif  // QLEARNING_HPP

#ifndef QLEARNING_HPP
#define QLEARNING_HPP

#include <vector>

#define QLEARNING_DEFAULT_MOVE_REWARD 0.1f


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

    /**
     * Method for altering the move reward of this QLearning object.
     * Has to stay within range of [0.f, 10.f].
     * @param move_reward_change change of move reward
     */
    void alterMoveReward(float move_reward_change);

    /** Method for resetting the move reward to default value. */
    void resetMoveReward();

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

    /**
     * Helper method for correctly calculating value with which one can index
     * the Q matrix.
     * Throws an QLearningException if row is larger than states and column is
     * larger than actions, which would be out of bounds.
     * @param row which row is indexed in the matrix
     * @param column which column is indexed in the matrix
     * @return an unsigned int representing the correct indexing value for the
     *         Q matrix
     */
    inline unsigned int calculateIndex(
            unsigned int row, unsigned int column) const;

    /**
     * Helper method for correctly indexing the Q matrix.
     * @param row which row is indexed in the matrix
     * @param column which column is indexed in the matrix
     * @return the value in the matrix chosen by `row` and `column`
     */
    inline double indexMatrix(unsigned int row, unsigned int column) const;

    // Randomize initial current best for varying learning results
    bool random_best_action = true;

    // Counter used for debugging.
    unsigned int counter;

    // Debugging frequency, 0 aor no printing
    unsigned int debug_frequency = 0;

    unsigned int states;  // Number of states; number of matrix columns
    unsigned int actions;  // Number of actions; number of matrix rows
    std::vector<double> q_matrix;  // Storage for Q matrix

    unsigned int state = 0;  // Current state of this Q-algorithm
    unsigned int future_state = 0;  // Next state to take in future iteration

    float move_reward = QLEARNING_DEFAULT_MOVE_REWARD;  // Reward for moving
    double gamma;  // Gamma value used in Q calculation, range 0.0 - 1.0
    double alpha;  // Alpha value used in Q calculation, range 0.0 -1.0;

    // Accuracy used in calculations, same for all QLearning instances
    static const int accuracy = 100000;
};


#endif  // QLEARNING_HPP

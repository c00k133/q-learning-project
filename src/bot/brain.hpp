#ifndef Q_LEARNING_BRAIN_HPP
#define Q_LEARNING_BRAIN_HPP

#include "body.hpp"
#include "qlearning.hpp"

/**
 * Abstract class Brain: represents the brains of bots.
 */
class BotBrain {
 public:
    BotBrain(
       BotBody body,
       QLearning qLearning) : body(body), qLearning(qLearning) {}
    virtual ~BotBrain() = default;

 protected:
    BotBody body;
    QLearning qLearning;
};

class WormBrain : BotBrain {  // TODO(cookie): check if superclass is needed
 public:
    WormBrain(
       WormBody body,
       QLearning qLearning,
       int precision,
       float max_error);

    void process();

 private:
    int updateState(int state, int action);
    void act(int dir = 1, float curiosity = 0.1f);
    bool checkAllAngles() const;

    double rotate_size;
    double maximum_error;

    int precision;
    int count;

    int next_action = 0;
    int next_state = 0;
    int next_joint = 0;
    int next_rotation = 0;
};

#endif  // Q_LEARNING_BRAIN_HPP

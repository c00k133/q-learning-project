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
    virtual void process() = 0;

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

    void process() override;

 private:
    unsigned int updateState(unsigned int state, unsigned int action);
    void act(int dir = 1, float curiosity = 0.1f);
    bool inspectAngle(unsigned int index, double change = 0) const;

    float current_body_position_x = 0.0f;

    double rotate_size;
    double maximum_error;

    int precision;
    int count;

    int next_rotation = 0;
    unsigned int next_action = 0;
    unsigned int next_joint = 0;
};

#endif  // Q_LEARNING_BRAIN_HPP

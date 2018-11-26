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
       QLearning qLearning
       ) : body(body), qLearning(qLearning);

 private:
   BotBody body;
   QLearning qLearning;
};

class WormBrain : BotBrain {
 public:
   WormBrain(WormBody body, QLearning qLearning) : BotBrain(body, qLearning);
};

#endif  // Q_LEARNING_BRAIN_HPP

#ifndef Q_LEARNING_BODY_EXCEPTIONS_HPP
#define Q_LEARNING_BODY_EXCEPTIONS_HPP

#include "qlearning-runtime-exception.hpp"


namespace QLearningExceptions {

 class BodyRuntimeException
     : public QLearningExceptions::QLearningRuntimeException {
  public:
    explicit BodyRuntimeException(std::string message);
 };

}

#endif  // Q_LEARNING_BODY_EXCEPTIONS_HPP

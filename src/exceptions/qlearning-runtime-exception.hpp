#ifndef Q_LEARNING_QLEARNING_RUNTIME_EXCEPTION_HPP
#define Q_LEARNING_QLEARNING_RUNTIME_EXCEPTION_HPP

#include <stdexcept>
#include <string>


namespace QLearningExceptions {
 class QLearningRuntimeException : public std::runtime_error {
  public:
    explicit QLearningRuntimeException(std::string message);
    ~QLearningRuntimeException() override = default;
 };
}

#endif  // Q_LEARNING_QLEARNING_RUNTIME_EXCEPTION_HPP

#ifndef Q_LEARNING_QLEARNING_RUNTIME_EXCEPTION_HPP
#define Q_LEARNING_QLEARNING_RUNTIME_EXCEPTION_HPP

#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>


namespace QLearningExceptions {

 /** Base class for runtime exceptions. */
 class QLearningRuntimeException : public std::runtime_error {
  public:
    explicit QLearningRuntimeException(std::string message);
    ~QLearningRuntimeException() override = default;
 };

 /** Base class for exceptions. */
 class QLearningException : public std::exception {
  public:
    explicit QLearningException(std::string message);
    ~QLearningException() override = default;
    virtual const char* what() const throw();
  private:
    std::string message;
 };

}

#endif  // Q_LEARNING_QLEARNING_RUNTIME_EXCEPTION_HPP

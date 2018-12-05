#ifndef Q_LEARNING_BODY_EXCEPTIONS_HPP
#define Q_LEARNING_BODY_EXCEPTIONS_HPP

#include <sstream>

#include "qlearning-runtime-exception.hpp"


namespace QLearningExceptions {

 class BodyRuntimeException
     : public QLearningExceptions::QLearningRuntimeException {
  public:
    explicit BodyRuntimeException(std::string message);
    // FIXME(Cookie): function what() does not print the message correctly
    // The function prints gibberish instead of the input error message.
    // The problem might stem from inheritance of std::runtime_error.
    const char* what() const throw() override {
      std::ostringstream output;
      output << message << std::endl;
      return output.str().c_str();
    };

  private:
    std::string message;
 };

}

#endif  // Q_LEARNING_BODY_EXCEPTIONS_HPP

#ifndef Q_LEARNING_BODY_EXCEPTIONS_HPP
#define Q_LEARNING_BODY_EXCEPTIONS_HPP

#include <sstream>

#include "qlearning-runtime-exception.hpp"


namespace QLearningExceptions {

 class BodyRuntimeException
     : public QLearningExceptions::QLearningRuntimeException {
  public:
    explicit BodyRuntimeException(std::string message);
    virtual const char* what() const throw() {
      std::ostringstream output;
      output << message << std::endl;
      return output.str().c_str();
    };

  private:
    std::string message;
 };

}

#endif  // Q_LEARNING_BODY_EXCEPTIONS_HPP

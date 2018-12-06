#include "qlearning-exception.hpp"


namespace QLearningExceptions {

 QLearningRuntimeException::QLearningRuntimeException(std::string message) :
    std::runtime_error(message) {}

 QLearningException::QLearningException(std::string message) :
    message(message) {}

 const char* QLearningException::what() const throw() {
   return message.c_str();
 }

}

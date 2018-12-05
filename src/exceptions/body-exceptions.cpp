#include <sstream>

#include "body-exceptions.hpp"


namespace QLearningExceptions {
 BodyRuntimeException::BodyRuntimeException(std::string message) :
      QLearningRuntimeException(message) {}

}

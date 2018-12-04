#include <sstream>

#include "body-exceptions.hpp"


namespace QLearningExceptions {
 BodyRuntimeException::BodyRuntimeException(std::string message) :
    QLearningRuntimeException(message), message(message) {}

// const char* BodyRuntimeException::what() const throw() {
//   std::ostringstream output;
//   output << message << std::endl;
//   return output.str().c_str();
// }
}

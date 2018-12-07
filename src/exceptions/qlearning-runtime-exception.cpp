#include "qlearning-runtime-exception.hpp"


namespace QLearningExceptions {
 QLearningRuntimeException::QLearningRuntimeException(std::string message) :
    std::runtime_error(message) {}
}

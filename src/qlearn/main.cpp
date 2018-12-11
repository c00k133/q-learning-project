#include <string>

#include "qlearn.hpp"


/**
 * Check if input arguments are correct.
 * @param argv input argument values
 * @return true if success, false otherwise
 */
bool withArguments(char* argv[]) {
  unsigned int amount, bone_amount;
  int precision;

  try {
    amount = (unsigned int) std::stoi(argv[1]);
    precision = std::stoi(argv[2]);
    bone_amount = (unsigned int) std::stoi(argv[3]);
  } catch (std::invalid_argument& e) {
    std::cerr
        << "Invalid arguments, reverting to normal mode."
        << std::endl << std::endl;
    return false;
  } catch (std::out_of_range& e) {
    std::cerr
        << "Argument out of range, reverting to normal mode."
        << std::endl << std::endl;
    return false;
  }

  QLearn q_learn = QLearn(amount, precision, bone_amount);
  q_learn.run();

  return true;
}

/** Run the whole program. */
int main(int argc, char* argv[]) {
  if (argc != 4 || !withArguments(argv)) {
    QLearn q_learn;
    q_learn.run();
  }

  return 0;
}
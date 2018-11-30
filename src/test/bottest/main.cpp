#include "gtest/gtest.h"


/**
 * Run all tests in folder `bottest`.
 */
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}

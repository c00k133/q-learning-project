#include "gtest/gtest.h"
#include "body.hpp"
#include "test_utils.hpp"
#include "qlearning-exception.hpp"
#include "body-exceptions.hpp"


TEST(body_test_generic, test_exceptions) {
  EXPECT_THROW(
      WormBody((unsigned) 0), QLearningExceptions::BodyRuntimeException);
}


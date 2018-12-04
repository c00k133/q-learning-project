#include <vector>

#include "gtest/gtest.h"
#include "body.hpp"
#include "test_utils.hpp"
#include "qlearning-runtime-exception.hpp"
#include "body-exceptions.hpp"


TEST(body_test_generic, test_exceptions) {
//  EXPECT_THROW(
//      WormBody((unsigned) 0), QLearningExceptions::BodyRuntimeException);
  EXPECT_ANY_THROW(new WormBody((unsigned) 0));
}


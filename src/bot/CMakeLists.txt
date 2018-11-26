set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(QLearning "qlearning.cpp")
add_library(BotBody "body.hpp")
add_library(BotBrain "brain.hpp")

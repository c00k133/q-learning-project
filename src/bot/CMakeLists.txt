SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

ADD_LIBRARY(QLearning qlearning.cpp)
ADD_LIBRARY(BotBody body.cpp)
ADD_LIBRARY(BotBrain brain.cpp)

ADD_EXECUTABLE(bot main.cpp)

#TARGET_LINK_LIBRARIES(bot)

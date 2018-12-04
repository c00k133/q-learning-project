FILE(GLOB SRCS *.cpp)

ADD_EXECUTABLE(bottest ${SRCS})

TARGET_LINK_LIBRARIES(bottest
        libgtest
        libgmock
        BotBody
        QLearning
        Box2D
        TestUtils
        QLearningException
        BodyExceptions
)

ADD_TEST(NAME bottest COMMAND bottest)
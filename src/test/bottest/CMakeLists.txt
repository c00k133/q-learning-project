FILE(GLOB SRCS *.cpp)

ADD_EXECUTABLE(bottest ${SRCS})

TARGET_LINK_LIBRARIES(bottest
        # gtest specifics
        libgtest
        libgmock

        # q-learning specifics
        BotBody
        QLearning
        Box2D
        TestUtils
        BodyExceptions
        QLearningException

        # SFML specifics
        ${SFML_LIBRARIES}
)

ADD_TEST(NAME bottest COMMAND bottest)
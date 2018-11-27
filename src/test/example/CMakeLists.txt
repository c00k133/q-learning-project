FILE(GLOB SRCS *.cpp)

ADD_EXECUTABLE(exampletest ${SRCS})

TARGET_LINK_LIBRARIES(exampletest
        libgtest
        libgmock
)

ADD_TEST(NAME exampletest COMMAND exampletest)
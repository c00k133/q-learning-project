SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/libs")
FIND_PACKAGE(SFML REQUIRED system window graphics network audio)
IF(SFML_FOUND)
    INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
ENDIF()

SET(BOTSOURCES BotBrain QLearning BotBody)
SET(PHYSICSSOURCES Physics)
SET(EXCEPTIONSOURCES BodyExceptions QLearningException)

ADD_LIBRARY(SFMLDrawer sfml-drawer.cpp)

ADD_EXECUTABLE(sfml-testing main.cpp)

TARGET_LINK_LIBRARIES(sfml-testing
        SFMLDrawer
        ${SFML_LIBRARIES}
        ${BOTSOURCES}
        ${EXCEPTIONSOURCES}
        ${PHYSICSSOURCES}
        Box2D
)

SET(SFMLSOURCES SFMLDrawer)
SET(BOTSOURCES BotBrain QLearning BotBody)
SET(PHYSICSSOURCES Physics)
SET(EXCEPTIONSOURCES BodyExceptions QLearningException)

ADD_LIBRARY(QLearnStarter qlearn.cpp)
SET(QLEARNLIB QLearnStarter)

ADD_EXECUTABLE(qlearn main.cpp)

TARGET_LINK_LIBRARIES(qlearn
        ${QLEARNLIB}
        ${SFMLSOURCES}
        ${SFML_LIBRARIES}
        ${BOTSOURCES}
        ${EXCEPTIONSOURCES}
        ${PHYSICSSOURCES}
        Box2D
)
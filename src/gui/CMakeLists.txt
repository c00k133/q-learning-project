SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/libs")
FIND_PACKAGE(SFML REQUIRED system window graphics network audio)
IF(SFML_FOUND)
    INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
ENDIF()

# Find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
SET(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
SET(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
FIND_PACKAGE(Qt5Widgets CONFIG REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Network REQUIRED)

# Populate a CMake variable with the sources
SET(GUISOURCES
        mainwindow.ui
        mainwindow.cpp
        main.cpp
        mycanvas.cpp
        qsfmlwidget.cpp
)

SET(BOTSOURCES BotBrain QLearning BotBody)
SET(PHYSICSSOURCES Physics)
SET(EXCEPTIONSOURCES BodyExceptions QLearningException)

ADD_EXECUTABLE(qlearningGUI ${GUISOURCES})
# Use the Widgets module from Qt 5
TARGET_LINK_LIBRARIES(qlearningGUI
        Qt5::Widgets
        Qt5::Core
        Qt5::Network
        ${SFML_LIBRARIES}
        ${BOTSOURCES}
        ${EXCEPTIONSOURCES}
        ${PHYSICSSOURCES}
        Box2D
)

GET_TARGET_PROPERTY(QtCore_location Qt5::Core LOCATION)
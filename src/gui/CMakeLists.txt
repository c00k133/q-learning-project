FIND_PACKAGE(SFML 2.5 COMPONENTS graphics audio REQUIRED)

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

ADD_EXECUTABLE(q-learningGUI ${GUISOURCES})
# Use the Widgets module from Qt 5
TARGET_LINK_LIBRARIES(q-learningGUI
        Qt5::Widgets
        Qt5::Core
        Qt5::Network
        sfml-graphics
        sfml-audio
)

GET_TARGET_PROPERTY(QtCore_location Qt5::Core LOCATION)
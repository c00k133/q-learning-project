# Check that the build does not happen in the source tree
IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    MESSAGE("src dir: ${CMAKE_SOURCE_DIR}\tbinary dir: ${CMAKE_BINARY_DIR}")
    MESSAGE(FATAL_ERROR "Prevented in-tree build. This is bad practice.")
ENDIF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

# Project wide settings
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
PROJECT(q-learning)

IF(NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    SET(CMAKE_BUILD_TYPE Debug)
    MESSAGE("* Default to build type: ${CMAKE_BUILD_TYPE}")
ELSE()
    message("* Build type: ${CMAKE_BUILD_TYPE}")
ENDIF(NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")

# Check tool versions, initialize to defaults
SET(COMPILER_VERSION 0.0.0)

STRING(REGEX MATCH "[0-9]\\.[0-9]\\.[0-9]" COMPILER_VERSION ${CMAKE_CXX_COMPILER_VERSION})
IF(${CMAKE_COMPILER_IS_GNUCXX} AND ${COMPILER_VERSION} VERSION_GREATER 4.8.1)
    MESSAGE("* Compiler version is supported")
ELSE()
    MESSAGE(FATAL_ERROR "* Compiler is not supported (needs at least g++ 4.8.1)")
ENDIF(${CMAKE_COMPILER_IS_GNUCXX} AND ${COMPILER_VERSION} VERSION_GREATER 4.8.1)

# Set common compiler and linker flags
ADD_DEFINITIONS(-std=c++11)
ADD_DEFINITIONS(-Wall)

# Per build type flags
IF(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    ADD_DEFINITIONS(-O3)
    ADD_DEFINITIONS(-fno-keep-static-consts)
    ADD_DEFINITIONS(-mtune=native)
ENDIF(${CMAKE_BUILD_TYPE} STREQUAL "Release")

IF(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    ADD_DEFINITIONS(-Og)
    ADD_DEFINITIONS(-finline-functions-called-once)
    ADD_DEFINITIONS(-Wall)
    ADD_DEFINITIONS(-W)
    ADD_DEFINITIONS(-Wextra)
    ADD_DEFINITIONS(-pedantic)
    ADD_DEFINITIONS(-Wno-unused-function)
ENDIF(${CMAKE_BUILD_TYPE} STREQUAL "Debug")

# Add all 3rd party libraries
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/libs/gtest-1.7.0")

ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/libs/gtest-1.7.0")

LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/libs/gtest-1.7.0")

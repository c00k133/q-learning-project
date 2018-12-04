ADD_LIBRARY(Physics physics.cpp)
ADD_LIBRARY(PhysicsMain physics_main.cpp)

ADD_EXECUTABLE(physics physics_main.cpp)

TARGET_LINK_LIBRARIES(physics
        Physics
        Box2D
        BotBody
        BodyExceptions
        QLearningException
)
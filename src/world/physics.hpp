#ifndef Q_LEARNING_PHYSICS_HPP
#define Q_LEARNING_PHYSICS_HPP

#include "Box2D/Box2D.h"


// TODO(Cookie): check if this should be a const variable instead
#define GRAVITATIONAL_FORCE -9.81f

class PhysicsEngine {
 public:
    explicit PhysicsEngine(float world_pos = -10.0f, float32 time_step = 60.0f);

    b2World* getWorld();
    void step();

    float32 getTimeStep() const;
    void setTimeStep(float32 new_time_step);

 private:
    b2World* world;
    b2Body* ground_body;

    // Typically we use a time of 1/60 of a second (60Hz)
    // This provides a high quality simulation in most game scenarios
    float32 time_step;
    static constexpr int32 velocity_iterations = 6;
    static constexpr int32 position_iterations = 2;
};

#endif  // Q_LEARNING_PHYSICS_HPP

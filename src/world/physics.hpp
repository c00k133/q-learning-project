#ifndef Q_LEARNING_PHYSICS_HPP
#define Q_LEARNING_PHYSICS_HPP

#include <memory>

#include "Box2D/Box2D.h"

#define PHYSICS_ENGINE_DEFAULT_WORLD_POSITION_X 10.f
#define PHYSICS_ENGINE_DEFAULT_TIME_STEP 60.f


class PhysicsEngine {
 public:
    /**
     * PhysicsEngine constructor.
     * @param world_pos x position of the ground
     * @param time_step time step size used in world simulation
     */
    explicit PhysicsEngine(
        float world_pos = PHYSICS_ENGINE_DEFAULT_WORLD_POSITION_X,
        float32 time_step = PHYSICS_ENGINE_DEFAULT_TIME_STEP);

    /**
     * Alters the time step of this engine by the input amount.
     * Bounds are checked, the final time step should be within [1.f, 1000.f]
     * @param time_step_change change of time step
     */
    void alterTimeStep(float32 time_step_change);

    /** Method for resetting the time step back to default value. */
    void resetTimeStep();

    /**
     * Getter for the Box2D world.
     * @return pointer to world
     */
    b2World& getWorld() const;
    /**
     * Getter for the Box2D ground.
     * @return pointer to the ground
     */
    b2Body& getGround() const;

    /**
     * Getter for the dimensions of the ground.
     * @return b2Vec2 with ground dimensions, width and height respectively
     */
    const b2Vec2 getGroundDimensions() const;

    /** Make one step in the world simulation. */
    void step();

 private:
    // Pointer to the simulated world
    std::shared_ptr<b2World> world;
    // Pointer to the ground body
    b2Body* ground_body;

    // Typically we use a time of 1/60 of a second (60Hz)
    // This provides a high quality simulation in most game scenarios
    float32 time_step;

    // Velocity constraint resolver for the world stepping
    static constexpr int32 velocity_iterations = 8;
    // Position constraint resolver for the world stepping
    static constexpr int32 position_iterations = 3;

    // Gravitational force: positive as origin of the world is "up-left"
    static constexpr float gravitational_force = 9.81f;

    // Width of the ground
    static constexpr float ground_width = 8000.f;
    // Height of the ground
    static constexpr float ground_height = 10.f;
};

#endif  // Q_LEARNING_PHYSICS_HPP

#ifndef Q_LEARNING_BRAIN_HPP
#define Q_LEARNING_BRAIN_HPP

#include "body.hpp"
#include "qlearning.hpp"
#include "Box2D/Box2D.h"


/**
 * Class WormBrain: represents the brains of our first movable creature, the
 * worm.
 */
class WormBrain {
 public:
    /**
     * WormBrain constructor.
     *
     * This constructor takes a ready made body and q-learning object for
     * controlling.
     *
     * @param body controlled worm bot body
     * @param qLearning queried Q learning object
     * @param precision precision used in angle calculations
     * @param max_error maximum allowed error for bot joint rotation
     */
    WormBrain(
       WormBody* body,
       QLearning* qLearning,
       int precision,
       float max_error = 3);

    /**
     * WormBrain constructor.
     *
     * Takes an input world to create a new body and q-learning object with.
     *
     * @param world world that the worm body moves in
     * @param precision precision used in angle calculations
     * @param max_error maximum allowed error for bot joint rotation
     * @param bone_amount amount of bones in the worm body,
     *                    must be larger than 0, defaults to 3
     */
    WormBrain(
            b2World* world,
            int precision,
            float max_error = 3,
            unsigned int bone_amount = 3);

    /**
     * WormBrain destructor.
     *
     * Takes care of releasing body and q-learning allocated memory.
     */
    ~WormBrain();

    /**
     * Updates the state of the whole worm based on actions.
     *
     * The process() method updates the state of the WormBrain, WormBody, and
     * the QLearning object according to physical reactions.
     *
     * This method can be thought of as the brains thought-process.
     */
    void process();

    /**
     * Getter for the coordinates of the body as a b2Vec2.
     * @return the body coordinates as a b2Vec2
     */
    const b2Vec2 getBodyCoordinatesVector() const;

    /**
     * Getter for the coordinates of the body as a std::tuple.
     * @return the body coordinates as a std::tuple
     */
    const std::tuple<float, float> getBodyCoordinatesTuple() const;

    /**
     * Getter for the WormBody.
     * @return a const pointer to the WormBody.
     */
    const WormBody* getBody() const;

    /**
     * Getter for private count variable.
     * @return count value
     */
    int getCount();

 private:
    /**
     * Common initialization method for all brain constructors.
     *
     * @param precision input precision used in angle calculations
     * @param max_error maximum allowed error for bot joint rotation
     */
    void init(int precision, float max_error);

    /**
     * Method for updating the current brain state.
     * Calculates new angles and returns new state.
     * @param state input state, i.e. current state
     * @param action action to take, used for Q learning matrix
     * @return the new state that shall be taken
     */
    unsigned int updateState(unsigned int state, unsigned int action);

    /**
     * Small helper method for updating the next action and setting new future
     * state for Q learning object.
     * @param random true for getting random action, false for optimal
     * @param curiosity possible curiosity given to random action
     */
    void act(bool random = true, float curiosity = 0.1f);

    /**
     * Check whether joint angle is withing bounds.
     * @param index index of joint
     * @param change the amount of change
     * @return true if withing bounds, false otherwise
     */
    bool inspectAngle(unsigned int index, double change = 0) const;

    WormBody* body;  // Controlled bot body object
    QLearning* qLearning;  // Queried Q learning object

    // Current position of body in the world
    float current_body_position_x = 0.0f;

    double rotate_size;  // Size of joint angle rotation
    double maximum_error;  // Maximum error allowed for rotation

    int precision;  // Precision for use within angle calculations
    int count;  // Incremented counter for calls on process

    int next_rotation = 0;  // Rotation to take in future iteration
    unsigned int next_action = 0;  // Action to take in future iteration
    unsigned int next_joint = 0;  // Joint to consider in future iteration
};

#endif  // Q_LEARNING_BRAIN_HPP

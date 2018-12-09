#ifndef Q_LEARNING_BRAIN_HPP
#define Q_LEARNING_BRAIN_HPP

#include "body.hpp"
#include "qlearning.hpp"
#include "Box2D/Box2D.h"


#define WORMBRAIN_DEFAULT_MAX_ERROR 3
#define WORMBRAIN_DEFAULT_BONE_AMOUNT 3


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
       float max_error = WORMBRAIN_DEFAULT_MAX_ERROR);

    /**
     * WormBrain constructor.
     *
     * Takes an input world to create a new body and q-learning object with.
     *
     * @param world world that the worm body moves in
     * @param precision precision used in angle calculations
     * @param bone_amount amount of bones in the worm body,
     *                    must be larger than 0, defaults to 3
     * @param max_error maximum allowed error for bot joint rotation
     */
    WormBrain(
            b2World* world,
            int precision,
            unsigned int bone_amount = WORMBRAIN_DEFAULT_BONE_AMOUNT,
            float max_error = WORMBRAIN_DEFAULT_MAX_ERROR);

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

    /**
     * Setter for acting randomly.
     * If true the worm will not search for optimal target, but include some
     * randomness.
     * @param choice
     */
    void setRandomActs(bool choice);

    /**
     * Setter for debugging frequency, set to 0 for no printing.
     * @param frequency debugging frequency
     */
    void setDebug(unsigned int frequency);

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
    inline bool inspectAngle(unsigned int index, double change = 0) const;
    /**
     * Helper function checking if we can continue with the q learning or have
     * to convert back to older angles.
     * @return true if we may continue, false otherwise
     */
    bool inspectAngles();

    // Save the last angles to see if anything gets stuck
    // When doing this the worm stops being lazy and moves properly
    std::vector<float> saved_angles;

    WormBody* body;  // Controlled bot body object
    QLearning* qLearning;  // Queried Q learning object

    // Current x position of body in the world
    float current_body_position_x = 0.0f;

    // Debugging frequency, 0 for no printing
    unsigned int debug_frequency = 0;

    double rotate_size;  // Size of joint angle rotation
    double maximum_error;  // Maximum error allowed for rotation

    int precision;  // Precision for use within angle calculations
    int count;  // Incremented counter for calls on process

    bool random_act = false;  // Should the worm take random actions?

    int next_rotation = 0;  // Rotation to take in future iteration
    unsigned int next_action = 0;  // Action to take in future iteration
    unsigned int next_joint = 0;  // Joint to consider in future iteration
};

#endif  // Q_LEARNING_BRAIN_HPP

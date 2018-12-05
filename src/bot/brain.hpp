#ifndef Q_LEARNING_BRAIN_HPP
#define Q_LEARNING_BRAIN_HPP

#include "body.hpp"
#include "qlearning.hpp"
#include "Box2D/Box2D.h"

///**
// * Abstract class Brain: represents the brains of bots.
// */
//class BotBrain {
// public:
//    /**
//     * BotBrain constructor.
//     * Needs a body to control and a Q learning object to calculate optimal
//     * steps with.
//     * @param body controlled bot body
//     * @param qLearning queried Q learning object
//     */
//    BotBrain(
//       BotBody* body_,
//       QLearning* qLearning_
//    ) {
//       body = body_;
//       qLearning = qLearning_;
//    }
//
//    /** Virtual destructor for showcasing abstractness of class. */
//    virtual ~BotBrain() = default;
//
//    /**
//     * This is the method called each time the brain should "think".
//     * The method queries the Q learning object for advice on how to move the
//     * body.
//     */
//    virtual void process() = 0;
//
// protected:
//    BotBody* body;  // Bot body object
//    QLearning* qLearning;  // Q learning object
//};

/**
 * Class WormBrain: represents the brains of our first movable creature, the
 * worm.
 *
 * Extends the virtual/abstract class BotBrain.
 */
//class WormBrain : BotBrain {  // TODO(cookie): check if superclass is needed
class WormBrain {
 public:
    /**
     * WormBrain constructor.
     * Needs a body to control and a Q learning object to query.
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

    WormBrain(
            int precision,
            b2World* world,
            float max_error = 3,
            unsigned int bone_amount = 3);

    ~WormBrain();

    void process();

    const b2Vec2 getBodyCoordinatesVector() const;
    const std::tuple<float, float> getBodyCoordinatesTuple() const;

    const std::tuple<float, float> getBodyBoneDimensions() const;

    std::vector<b2Body*> getBodyBones() const;
    std::vector<b2Joint*> getBodyJoints() const;

    /**
     * Getter for private count variable.
     * @return count value
     */
    int getCount();

 private:
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

    static constexpr float rotation_speed = 0.5f;
};

#endif  // Q_LEARNING_BRAIN_HPP

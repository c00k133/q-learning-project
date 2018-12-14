#ifndef Q_LEARNING_BODY_HPP
#define Q_LEARNING_BODY_HPP

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <SFML/Graphics.hpp>

#include "Box2D/Box2D.h"

#define WORMBODY_DEFAULT_BONE_COLOR sf::Color(255, 102, 102)
#define WORMBODY_DEFAULT_OUTLINE_COLOR sf::Color::Black
#define WORMBODY_DEFAULT_BONE_WIDTH 10.f
#define WORMBODY_DEFAULT_BONE_LENGTH 2.f
#define WORMBODY_DEFAULT_MAX_MOTOR_TORQUE 100000.f
#define WORMBODY_DEFAULT_MOTOR_SPEED 0.5f


class WormBody {
 public:
    /**
     * WormBody constructor without initialization.
     * Needs to be initialized by calling method `createBodyParts()`.
     * @param bone_amount amount of bones in this worm, minimum 1, default 3
     */
    explicit WormBody(unsigned int bone_amount = 3);

    /**
     * WormBody constructor with initialization.
     * @param world the world in which this body exists
     * @param bone_amount amount of bones in this worm, minimum 1, default 3
     */
    explicit WormBody(b2World& world, unsigned int bone_amount = 3);

    /**
     * Getter for amount of bones in this WormBody.
     * @return amount of bones
     */
    unsigned int getBoneAmount() const;
    /**
     * Getter for amount of joints in this WormBody.
     * @return amount of joints
     */
     unsigned int getJointAmount() const;

    /**
     * Getter for all bones in this WormBody.
     * A bone represents a Box2D section of the WormBody.
     * @return std::vector with pointers to bones
     */
    std::vector<b2Body*> getBones() const;
    /**
     * Getter for all joints in this WormBody.
     * A joint connect two bones and works as the motor for moving.
     * @return std::vector with pointers to joints
     */
    std::vector<b2Joint*> getJoints() const;

    /**
     * Getter for the body bone color.
     * @return SFML color for bones
     */
    sf::Color getBodyColor() const;
    /**
     * Getter for the outline bone color.
     * @return SFML color bone outlines
     */
    sf::Color getBodyOutlineColor() const;

    /**
     * Getter for certain body joint.
     * @param index index for which joint
     * @return const pointer to the wanted joint
     */
    const b2Joint* getJoint(unsigned int index) const;
    /**
     * Getter for body joint angle.
     * @param index which joint angle
     * @return joint angle
     */
    float32 getJointAngle(unsigned int index) const;

    /**
     * Set a new angle for a certain body joint.
     * @param index which joint to affect
     * @param angle the target angle
     */
    void setJointAngle(unsigned int index, float angle);

    /**
     * Setter for the body bone color.
     * @param new_color new color for bones
     */
    void setBodyColor(sf::Color new_color);
    /**
     * Setter for the body bone outline color.
     * @param new_color new color for outline
     */
    void setBodyOutlineColor(sf::Color new_color);

    /**
     * Getter for coordinates of this WormBody.
     * This is calculated by taking the average of each bone coordinate.
     * @return std::tuple consisting of x and y coordinates respectively
     */
    const std::tuple<float, float> getCoordinatesTuple() const;
    /**
     * Getter for coordinates of this WormBody.
     * This is calculated by taking the average of each bone coordinate.
     * @return b2Vec2 consisting of x and y coordinates respectively
     */
    const b2Vec2 getCoordinatesVector() const;

    /**
     * Getter for dimensions of body bones, used mainly in drawing.
     * @return a std::tuple consisting of width and length respectively
     */
    const std::tuple<float, float> getBoneDimensions() const;

    /**
     * Method for changing the maximum motor torque for each joint.
     * Has to stay within bounds of [1.f, 1000000.f].
     * @param motor_torque_change change in maximum motor torque
     */
    void alterMaxMotorTorque(float motor_torque_change);

    /**
     * Method for resetting the maximum motor torque for each joint to the
     * default.
     */
    void resetMaxMotorTorque();

    /**
     * Method for changing the motor speed for each joint.
     * Has to stay within bounds of [0.01f, 100.f].
     * @param motor_speed_change change in motor speed
     */
    void alterMotorSpeed(float motor_speed_change);

    /** Method for resetting the motor speed of joint to the default value. */
    void resetMotorSpeed();

    /**
     * Method for creating all body parts of this WormBody object.
     * Includes the creation of all bones and connecting joints.
     * @param world world in which these body parts exist
     */
    void createBodyParts(b2World& world);

 private:
    /**
     * Common initialization method for all WormBody constructors.
     * @param bone_amount amount of bones in this worm
     */
    void init(unsigned int bone_amount);

    /**
     * Helper method for creating a Box2D body definition for bones.
     * @return body definition for a bone
     */
    b2BodyDef createBodyDef() const;
    /**
     * Helper method for creating a Box2D body shape for bones.
     * The shape is a rectangle.
     * @return body shape for a bone
     */
    b2PolygonShape createBodyShape() const;
    /**
     * Helper method for creating a Box2D body fixture based on a body shape.
     * @param shape input body shape used to create this fixture
     * @return fixture derived from input shape
     */
    b2FixtureDef createBodyFixtureDef(const b2PolygonShape* shape) const;
    /**
     * Helper method for creating a connecting joint between two bones.
     * @param index index of bone in bones vector, must be minimum of 1
     * @return joint connecting two bones
     */
    b2RevoluteJointDef createJoint(unsigned int index) const;

    /**
     * Helper method for calculating distances between bones.
     * @param index multiplier for each body
     * @param offset offset from origin of whole body
     * @return calculated distance
     */
    inline float32 calculateDistance(
        unsigned int index, float offset = 0) const;

    /**
     * Method for checking if this worm body has been initialized.
     * Throws an exception otherwise.
     * @param message string message to be passed to the exception
     */
    void checkInitialization(std::string message) const;

    // Initialization variable for this worm body
    // A worm is initialized when all Box2D body parts have been created
    bool initialized = false;

    // Vector with pointers to each joint
    std::vector<b2Joint*> joints;
    // Vector with pointers to each bone
    std::vector<b2Body*> bones;

    // Total amount of bones in this body
    unsigned int bone_amount;

    // Color of all bones in this body
    sf::Color body_color = WORMBODY_DEFAULT_BONE_COLOR;
    // Outline color of all bones in this body
    sf::Color body_outline_color = WORMBODY_DEFAULT_OUTLINE_COLOR;

    // Box2D maximum motor torque
    float max_motor_torque = WORMBODY_DEFAULT_MAX_MOTOR_TORQUE;
    // Box2D motor speed for each joint motor
    float motor_speed = WORMBODY_DEFAULT_MOTOR_SPEED;

    /* Static const values common for all worm bodies. */
    // Width of each bone
    static constexpr float bone_width = WORMBODY_DEFAULT_BONE_WIDTH;
    // Length of each bone
    static constexpr float bone_length = WORMBODY_DEFAULT_BONE_LENGTH;

    /* Static const values for Box2D usage. */
    static constexpr float density = 1.f;  // Box2D density for each bone
    static constexpr float friction = 0.3f;  // Box2D friction for each bone
    // Box2D linear damping for each joint motor
    static constexpr float linear_damping = 0.f;
    // Box2D angular damping for each joint motor
    static constexpr float angular_damping = 0.01f;
    // Y offset for Box2D body definitions
    static constexpr float y_distance = 0.f;
    // Initial x position of Box2D body definitions
    static constexpr float x_position = -15.f;
    // Box2D collision category bits
    static constexpr int category_bits = 0x1;
    // Box2D collision mask bits
    static constexpr int mask_bits = 0x2;
};

#endif

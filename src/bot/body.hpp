#ifndef Q_LEARNING_BODY_HPP
#define Q_LEARNING_BODY_HPP

#include <iostream>
#include <vector>
#include <tuple>

#include "Box2D/Box2D.h"


//class BotBody {
// public:
//    ~BotBody() = default;
//};

//class WormBody : public BotBody {
class WormBody {
 public:
    /**
     * WormBody constructor.
     * @param bone_amount amount of bones in this worm, minimum 1
     */
    explicit WormBody(unsigned int bone_amount = 3);
    explicit WormBody(b2World* world, unsigned int bone_amount = 3);

    unsigned int getBoneAmount() const;
    std::vector<b2Body*> getBones() const;
    std::vector<b2Joint*> getJoints() const;

    const b2Joint* getJoint(unsigned int index) const;
    float32 getJointAngle(unsigned int index) const;

    void setJointAngle(unsigned int index, float angle);

    const b2Vec2 getCoordinatesVector() const;
    const std::tuple<float, float> getCoordinatesTuple() const;

    const std::tuple<float, float> getBoneDimensions() const;

    void createBodyParts(b2World* world);

 private:
    void init(unsigned int bone_amount);

    b2BodyDef createBodyDef() const;
    b2PolygonShape createBodyShape() const;
    b2FixtureDef createBodyFixtureDef(const b2PolygonShape* shape) const;
    b2RevoluteJointDef createJoint(unsigned int index) const;

    inline int calculateDistance(
        unsigned int index,
        unsigned int offset = 0) const;

    void checkInitialization(std::string message) const;
    bool initialized = false;

    std::vector<b2Joint*> joints;
    std::vector<b2Body*> bones;

    unsigned int bone_amount;

    // TODO(Cookie): check if these need to be changed later on
    static constexpr float bone_width = 10.f;//2.f;
    static constexpr float bone_length = 2.f;//10.f;
    static constexpr float density = 1.f;
    static constexpr float friction = 0.3f;
    static constexpr float linear_damping = 0.f;
    static constexpr float angular_damping = 0.01f;
    static constexpr float motor_speed = 0.5f;
    static constexpr float y_distance = -60.f;//-70.f;
};

#endif

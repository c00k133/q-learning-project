#ifndef Q_LEARNING_BODY_HPP
#define Q_LEARNING_BODY_HPP

#include <iostream>
#include <vector>

#include "Box2D/Box2D.h"


class BotBody {
 public:
    ~BotBody() = default;
};

class WormBody : public BotBody {
 public:
    /**
     * WormBody constructor.
     * @param bone_amount amount of bones in this worm, minimum 1
     */
    explicit WormBody(unsigned int bone_amount = 3);
    WormBody(b2World* world, unsigned int bone_amount = 3);

    unsigned int getBoneAmount() const;
    unsigned int getCount() const;

    /* Used for testing purposes */
    int getAngleChange() const;

    void createBodyParts(b2World* world);

 private:
    void init(unsigned int bone_amount);
    b2Body* createBone(b2World* world) const;

    std::vector<b2Joint*> joints;
    std::vector<b2Body*> bones;

    unsigned int bone_amount;
    unsigned int count = 0;

    static constexpr float bone_width = 0.5f;
    static constexpr float bone_length = 2.0f;
    static constexpr int angle_change = 10;
};

#endif

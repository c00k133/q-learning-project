#ifndef Q_LEARNING_BODY_HPP
#define Q_LEARNING_BODY_HPP

#include <iostream>
#include <vector>

#include "Box2D/Box2D.h"


class BotBody {
 public:
    ~BotBody() = default;
    virtual b2Body* createB2Body(b2World* world) const = 0;
};

class WormBody : public BotBody {
 public:
    /**
     * WormBody constructor.
     * Take a list of angles and the length between joints for the worm as
     * parameters.
     * @param list list of angles
     * @param len length between joint
     */
    explicit WormBody(std::vector<int> list, unsigned int len = 1);

    b2Body* createB2Body(b2World* world) const override;

    unsigned int get_len() const;
    int get_angle(unsigned int num) const;
    unsigned long get_joint_amount() const;
    unsigned int get_count() const;

    /* Used for testing purposes */
    int getAngleChange() const;

    const std::vector<int> get_all_angles() const;

    void increase_angle(int num);
    void decrease_angle(int num);

 private:
    b2Body* createBone(b2World* world) const;
    void change_angle(int num, int change);

    std::vector<int> angles;
    unsigned int len;
    unsigned int count = 0;

    static constexpr float bone_width = 0.5f;
    static constexpr float bone_length = 2.0f;
    static constexpr int angle_change = 10;
};

#endif

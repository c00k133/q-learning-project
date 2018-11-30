#ifndef Q_LEARNING_BODY_HPP
#define Q_LEARNING_BODY_HPP

#include <iostream>
#include <list>

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
    WormBody(std::list<int> list, int len = 1);

    b2Body* createB2Body(b2World* world) const override;

    int get_len() const;
    int get_angle(int num) const;
    unsigned long get_joint_amount() const;
    unsigned int get_count() const;

    const std::list<int> get_all_angles() const;

    void increase_angle(int num);
    void decrease_angle(int num);

 private:
    b2Body* createBone(b2World* world) const;

    std::list<int> angles_;
    int len_;
    unsigned int count_ = 0;

    static constexpr float bone_width = 0.5f;
    static constexpr float bone_length = 2.0f;
};

#endif

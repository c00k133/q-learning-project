#ifndef Q_LEARNING_BODY_HPP
#define Q_LEARNING_BODY_HPP

#include <iostream>
#include <list>


class BotBody {
 public:
    virtual ~BotBody() = default;
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
    WormBody(std::list<int> list, int len) : angles_(list) , len_(len) {}

    int get_len() {return len_;}

    unsigned long get_joint_amount() {return angles_.size();}
    unsigned int get_count() {return count_;}

    const std::list<int> get_all_angles() {return angles_;}

    int get_angle(int num);

    void increase_angle(int num);
    void decrease_angle(int num);

 private:
    std::list<int> angles_;
    int len_ = 1;
    unsigned int count_ = 0;
};

#endif

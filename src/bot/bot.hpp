#include <iostream>
#include <map>
#include <list>



class Bot {
public:
    
};

class Worm : public Bot{
public:
    Worm(std::list<int> list) : angles_(list) {}
    
    int get_angle(int num) {
        auto it = angles_.begin();
        for (int i = 0; i < num; i ++) {it++;}
        return *it;
    }
    
    void increase_angle(int num) {
        auto it = angles_.begin();
        for (int i = 0; i < num; i ++) {it++;}
        *it += 10;
    }
    
    void decrease_angle(int num) {
        auto it = angles_.begin();
        for (int i = 0; i < num; i ++) {it++;}
        *it -= 10;
    }
    
private:
    std::list<int> angles_;
};
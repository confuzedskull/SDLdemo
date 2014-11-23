#ifndef CONTROLS_H
#define CONTROLS_H
#include <map>

namespace controls
{
    extern std::map<char,void (*)()> key_bindings;
    extern std::map<std::string,bool> special_keys;
    void move_up();
    void move_down();
    void move_left();
    void move_right();
    void initialize();
    void process_keys();
    void process_mouse();
};

#endif // CONTROLS_H

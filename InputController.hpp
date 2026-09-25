#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

enum class Direction {
    Up,
    Down, 
    Left, 
    Right,
    Invalid
};


class InputController {
public:
    Direction GetCommand();
};

#endif

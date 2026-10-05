#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

enum class Commands {
    Up,
    Down, 
    Left, 
    Right,
    Invalid
};


class InputController {
public:
    Commands GetCommand();
};

#endif

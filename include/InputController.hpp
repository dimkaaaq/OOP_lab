#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

enum class Commands {
    Up,
    Down, 
    Left, 
    Right,
    Ability1,
    Ability2,
    Ability3,
    Ability4,
    Invalid
};


class InputController {
public:
    Commands GetCommand();
};

#endif

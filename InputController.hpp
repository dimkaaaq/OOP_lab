#include <iostream>

enum InputCommand {
    top,
    left,
    right,
    down

};


class InputController {
public:
    InputController();

    InputCommand getCommand();
private:
    std::string getPressedKey(); // or char
}


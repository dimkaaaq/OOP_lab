#include "InputController.hpp"

#include <iostream>

Direction InputController::GetCommand() {
    char input;
    std::cin >> input;

    switch (input) { 
        case 'w': case 'W': return Direction::Up;
        case 's': case 'S': return Direction::Down;
        case 'a': case 'A': return Direction::Left;
        case 'd': case 'D': return Direction::Right;
        default: return Direction::Invalid;
    }
}

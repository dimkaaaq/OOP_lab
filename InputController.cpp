#include "InputController.hpp"

#include <iostream>
#include <string>

Commands InputController::GetCommand() {
    std::string input;
    std::cin >> input;
    if (input.size() != 1) {
        return Commands::Invalid;
    }
    switch (input[0]) { 
        case 'w': case 'W': return Commands::Up;
        case 's': case 'S': return Commands::Down;
        case 'a': case 'A': return Commands::Left;
        case 'd': case 'D': return Commands::Right;
        default: return Commands::Invalid;
    }
}

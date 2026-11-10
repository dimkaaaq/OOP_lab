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
        case '1': return Commands::Ability1; // Лечение
        case '2': return Commands::Ability2; // Удар вокруг
        case '3': return Commands::Ability3; // Дальний удар
        case '4': return Commands::Ability4; // Телепортация
        default: return Commands::Invalid;
    }
}

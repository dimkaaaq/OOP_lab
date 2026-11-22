#include "ui/Menu.hpp"
#include <iostream>

MenuChoice Menu::ShowMainMenu() const {
    std::cout << "\033[2J\033[H";

    std::cout << "=========================\n";
    std::cout << "      SYMBOL WARS 3      \n";
    std::cout << "=========================\n";
    std::cout << "1. Новая игра\n";
    std::cout << "2. Загрузить игру\n";
    std::cout << "3. Выход\n";
    std::cout << "Ваш выбор: ";

    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return MenuChoice::Invalid;
    }
    switch(choice) {
        case 1: return MenuChoice::NewGame;
        case 2: return MenuChoice::LoadGame;
        case 3: return MenuChoice::Exit;
        default: return MenuChoice::Invalid;
    }
}
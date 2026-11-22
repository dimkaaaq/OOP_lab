#include <iostream>

#include "ui/Menu.hpp"
#include "ui/Renderer.hpp"
#include "core/InputController.hpp"
#include "core/Game.hpp"
#include "levels/RandomLevelGenerator.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::unitbuf;

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(h, &mode);
    SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif

    Menu menu;

    while (true) {
        MenuChoice choice = menu.ShowMainMenu();

        if (choice == MenuChoice::Exit) {
            break;
        } 
        else if (choice == MenuChoice::NewGame) {
            RandomLevelGenerator generator(3);
            
            Renderer renderer;
            InputController input;
            
            Game<RandomLevelGenerator> game(generator, renderer, input);
            game.Run();
            

            std::cout << "\nНажмите Enter, чтобы вернуться в меню...";
            std::cin.get();
            std::cin.get();
        }
        else if (choice == MenuChoice::LoadGame) {
            std::cout << "\nЗагрузка пока не реализована. Нажмите Enter...";
            std::cin.get();
            std::cin.get();
        }
        else {
            std::cout << "\nНеверный выбор. Нажмите Enter...";
            std::cin.get();
            std::cin.get();
        }
    }

    return 0;
}
#include <iostream>
#include <vector>

#include "EntityController.hpp"
#include "Field.hpp"
#include "GameLoop.hpp"
#include "InputController.hpp"
#include "Renderer.hpp"
#include "Robot.hpp"

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

    Field field = Field::GenerateField();
    Renderer renderer;
    InputController input;

    Robot player(1, 40, 10, 100, 100, 0, 0, 2);
    Robot enemy1(2, 30, 8, 100, 100, 10, 12, 2);
    Robot enemy2(2, 30, 8, 100, 100, 19, 13, 2);
    std::vector<Robot*> enemies = { &enemy1, &enemy2 };

    GameLoop game_loop(field, player, enemies, renderer, input);
    game_loop.Start();

    return 0;
}
#include <vector>

#include "Field.hpp"
#include "GameLoop.hpp"
#include "InputController.hpp"
#include "Renderer.hpp"
#include "Robot.hpp"

#include <windows.h>

int main() {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(h, &mode);
    SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif    
    Field field(6, 6);

    field.SetObstacle(1, 1);
    field.SetObstacle(4, 1);
    field.SetObstacle(2, 2);
    field.SetObstacle(3, 3);
    field.SetObstacle(1, 4);
    field.SetObstacle(4, 4);

    Robot player("blue", 100, 10, 100, 100, 0, 0);

    Robot enemy1("red", 80, 8, 100, 100, 5, 5);
    Robot enemy2("red", 80, 8, 100, 100, 5, 0);
    Robot enemy3("red", 80, 8, 100, 100, 0, 5);
    std::vector<Robot*> enemies = { &enemy1, &enemy2, &enemy3 };

    Renderer renderer;
    InputController input;

    GameLoop game_loop(field, player, enemies, renderer, input);
    game_loop.Start();

    return 0;
}
#include <iostream>
#include <vector>

#include "Field.hpp"
#include "GameLoop.hpp"
#include "InputController.hpp"
#include "Renderer.hpp"
#include "Robot.hpp"
#include "World.hpp"

#include "abilities/HealAbility.hpp"
#include "abilities/MeleeAbility.hpp"
#include "abilities/RangeAbility.hpp"
#include "abilities/TeleportAbility.hpp"

#include "statuses/BurnStatus.hpp"
#include "statuses/ShieldStatus.hpp"
#include "statuses/SlowStatus.hpp"
#include "statuses/OverloadStatus.hpp"

#include <random>

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
    
    Robot player(1, 40, 10, 100, 100, 2);
    Robot enemy1(2, 30, 8, 100, 100, 2);
    Robot enemy2(2, 30, 8, 100, 100, 2);

    World world(field);
    world.AddPlayer(player, 0, 0);
    world.AddEnemy(enemy1, 10, 12);
    world.AddEnemy(enemy2, 19, 13);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);

    for (Robot* enemy : world.GetEnemies()) {
        if (dist(gen) == 0) {
            enemy->AddAbility(std::make_shared<HealAbility>());
        } else {
            enemy->AddAbility(std::make_shared<TeleportAbility>(world));
        }
    }

    Renderer renderer;
    InputController input;

    GameLoop game_loop(world, renderer, input);
    game_loop.Start();

    return 0;
}
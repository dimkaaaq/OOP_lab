#include <vector>

#include "EntityController.hpp"
#include "Field.hpp"
#include "GameLoop.hpp"
#include "InputController.hpp"
#include "Renderer.hpp"
#include "Robot.hpp"

int main() {
    Field field = field.GenerateField();
    Renderer renderer;
    InputController input;
    
    Robot player("blue", 40, 10, 100, 100, 0, 0);
    Robot enemy1("red", 30, 8, 100, 100, 10, 12);
    Robot enemy2("red", 30, 8, 100, 100, 19, 13);
    std::vector<Robot*> enemies = { &enemy1, &enemy2 };
    GameLoop game_loop(field, player, enemies, renderer, input);
    game_loop.Start();

    return 0;
}
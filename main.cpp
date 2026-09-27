#include <vector>

#include "Field.hpp"
#include "GameLoop.hpp"
#include "InputController.hpp"
#include "Renderer.hpp"
#include "Robot.hpp"

int main() {

    Field field(30, 18);

    // Верхняя стена с проходами по краям
    for (int x = 6; x <= 23; ++x) {
        field.SetObstacle(x, 13);
    }

    // Левая вертикальная стена
    for (int y = 5; y <= 12; ++y) {
        field.SetObstacle(5, y);
    }

    // Правая вертикальная стена
    for (int y = 5; y <= 12; ++y) {
        field.SetObstacle(23, y);
    }

    // Нижняя стена с проходом в центре
    for (int x = 6; x <= 13; ++x) {
        field.SetObstacle(x, 4);
    }
    for (int x = 16; x <= 22; ++x) {
        field.SetObstacle(x, 4);
    }

    // Игрок в левом нижнем углу
    Robot player("blue", 100, 10, 100, 100, 0, 0);

    // Три врага: два сверху по углам, один внутри крепости
    Robot enemy1("red", 40, 8, 100, 100, 0, 17);
    Robot enemy2("red", 40, 8, 100, 100, 29, 17);
    Robot enemy3("red", 40, 8, 100, 100, 14, 9);
    std::vector<Robot*> enemies = { &enemy1, &enemy2, &enemy3 };

    Renderer renderer;
    InputController input;

    GameLoop game_loop(field, player, enemies, renderer, input);
    game_loop.Start();

    return 0;
}
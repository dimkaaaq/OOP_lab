#include "field.hpp"
#include "robot.hpp"
#include <vector>
#include <iostream>

int main() {
    system("chcp 65001 > nul");
    // Создаем поле 5 на 5
    Field my_field(5, 5);

    // Ставим непроходимую стену на клетку (1, 0)
    my_field.set_obstacle(1, 0);

    // Создаем двух роботов
    // Аргументы: команда, max_hp, current_hp, exp, req_exp, damage
    Robot wall_e("Autobots", 100, 100, 0, 100, 20);
    Robot t800("Decepticons", 150, 150, 0, 100, 35);

    // Задаем им стартовые позиции
    wall_e.x = 0; wall_e.y = 0; // Начинает в верхнем левом углу
    t800.x = 2;  t800.y = 0;   // На две клетки правее

    // Создаем общий список (вектор) роботов, чтобы они знали друг о друге
    std::vector<Robot*> game_robots = { &wall_e, &t800 };

    std::cout << "--- Наш мир ---\n";
    my_field.print_field();
    std::cout << "WALL-E в позиции (" << wall_e.x << ", " << wall_e.y << ")\n";
    std::cout << "T-800 в позиции (" << t800.x << ", " << t800.y << ")\n\n";

    // ТЕСТ 1: WALL-E пытается пойти вправо, но там стена (1,0)
    std::cout << "1. WALL-E пытается пойти направо на стену:\n";
    wall_e.move(my_field, "right", game_robots); 

    // ТЕСТ 2: WALL-E обходит стену снизу
    std::cout << "\n2. WALL-E обходит стену через низ:\n";
    wall_e.move(my_field, "down", game_robots);  // в (0, 1)
    wall_e.move(my_field, "right", game_robots); // в (1, 1)
    wall_e.move(my_field, "right", game_robots); // в (2, 1)
    wall_e.move(my_field, "up", game_robots);    // пытается встать в (2, 0)

    return 0;
}
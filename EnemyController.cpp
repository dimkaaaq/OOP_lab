#include "EnemyController.hpp"

void EnemyController::TryMove(Robot& robot, Commands cmd) {
    if (cmd == Commands::Invalid) return;

    int new_x = robot.GetX();
    int new_y = robot.GetY();

    switch(cmd) {
        case Commands::Up: new_y += robot.GetSpeed(); break;
        case Commands::Down: new_y -= robot.GetSpeed(); break;
        case Commands::Left: new_x--; break;
        case Commands::Right: new_x++; break;
        case Commands::Invalid: return;
    }
    if (!field_.IsValidPosition(new_x, new_y)) {
        return;
    }
    if (!field_.CanMoveTo(new_x, new_y)) {
        return;
    }
    if (&robot != &player_ && player_.IsAlive() && player_.GetX() == new_x && player_.GetY() == new_y) {
        robot.Interact(player_, heal_amount);
        return;
    }
    for (Robot* enemy : enemies_) {
        if (enemy == &robot) continue; 
        if (!enemy->IsAlive()) continue;
        if (enemy->GetX() != new_x || enemy->GetY() != new_y) continue; 
        robot.Interact(*enemy, heal_amount);
        return;
    }
    robot.MoveTo(new_x, new_y);
};

int EnemyController::PlayerTurn() {
    Commands cmd = input_.GetCommand();
    if (cmd == Commands::Invalid) {
        return 0;
    }
    TryMove(player_, cmd);
    return 1;
};

void EnemyController::EnemyTurn() {
    for (Robot* enemy : enemies_) {
        if (enemy->IsAlive()) {
            Commands cmd = GetRandomCommand();
            TryMove(*enemy, cmd);
        }
    }
}
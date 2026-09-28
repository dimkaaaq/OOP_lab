#include "EntityController.hpp"

#include <random>

EntityController::EntityController(Field& field, Robot& player,
                                   std::vector<Robot*>& enemies,
                                   InputController& input)
    : field_(field), player_(player), enemies_(enemies), input_(input),
      rng_(std::random_device{}()) {}

int EntityController::PlayerTurn() {
    Commands dir = input_.GetCommand();
    if (dir == Commands::Invalid) {
        return 0;
    }
    if (TryMove(player_, dir) == 1) {
        return 1;
    }
    return 0;
}

void EntityController::EnemyTurn() {
    for (Robot* enemy : enemies_) {
        if (enemy->IsAlive()) {
            Commands dir = GetRandomDirection();
            TryMove(*enemy, dir);
        }
    }
}

void EntityController::RestoreEnergy() {
    if (player_.IsAlive()) {
        player_.RestoreEnergy(kEnergyRestoreAmount);
    }
    for (Robot* enemy : enemies_) {
        if (enemy->IsAlive()) {
            enemy->RestoreEnergy(kEnergyRestoreAmount);
        }
    }
}

bool EntityController::IsPlayerWin() const {
    for (Robot* enemy : enemies_) {
        if (enemy->IsAlive()) {
            return false;
        }
    }
    return true;
}

bool EntityController::IsGameOver() const {
    return !player_.IsAlive() || IsPlayerWin();
}

Commands EntityController::GetRandomDirection() {
    std::uniform_int_distribution<> dist(0, 3);
    int value = dist(rng_);

    switch (value) {
        case 0: return Commands::Up;
        case 1: return Commands::Down;
        case 2: return Commands::Left;
        case 3: return Commands::Right;
    }
    return Commands::Invalid;
}

int EntityController::TryMove(Robot& robot, Commands dir) {
    if (dir == Commands::Invalid) return 0;

    int start_x = robot.GetX();
    int start_y = robot.GetY();
    int current_x = robot.GetX();
    int current_y = robot.GetY();

    int steps_left = robot.GetSpeed();
    while (steps_left > 0) {
        int next_x = current_x;
        int next_y = current_y;

        switch (dir) {
            case Commands::Up:    ++next_y; break;
            case Commands::Down:  --next_y; break;
            case Commands::Left:  --next_x; break;
            case Commands::Right: ++next_x; break;
            case Commands::Invalid: return 0;
        }

        if (!field_.IsValidPosition(next_x, next_y)) break;
        if (!field_.CanMoveTo(next_x, next_y)) break;

        if (&robot != &player_ && player_.IsAlive()
            && player_.GetX() == next_x && player_.GetY() == next_y) {
            robot.Interact(player_, kHealAmount);
            return 1;
        }

        for (Robot* enemy : enemies_) {
            if (enemy == &robot) continue;
            if (!enemy->IsAlive()) continue;
            if (enemy->GetX() != next_x || enemy->GetY() != next_y) continue;

            robot.Interact(*enemy, kHealAmount);
            return 1;
        }

        robot.MoveTo(next_x, next_y);

        current_x = next_x;
        current_y = next_y;

        steps_left -= field_.GetCellPassability(next_x, next_y);
    }
    
    if (robot.GetX() != start_x || robot.GetY() != start_y) {
        return 1;
    }
    return 0;
}
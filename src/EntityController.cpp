#include "EntityController.hpp"

#include <random>

#include "Field.hpp"
#include "Robot.hpp"
#include "World.hpp"
#include "iostream"

EntityController::EntityController(World& world, InputController& input)
    : world_(world), input_(input),
      vision_(world.GetField().GetWidth(), world.GetField().GetHeight()),
      rng_(std::random_device{}())
{
    UpdateVision();
}

void EntityController::UpdateVision() {
    Robot& player = world_.GetPlayer();
    if (player.IsAlive()) {
        vision_.Update(world_.GetX(&player), world_.GetY(&player), player.GetVision());
    }
}

int EntityController::PlayerTurn() {
    Commands cmd = input_.GetCommand();
    if (cmd == Commands::Invalid) {
        return 0;
    }
    if (cmd == Commands::Ability1) {
        bool used = world_.GetPlayer().UseAbility(0);
        return used ? 1 : 0;
    }
    if (cmd == Commands::Ability2) {
        bool used = world_.GetPlayer().UseAbility(1);
        return used ? 1 : 0;
    }
    if (cmd == Commands::Ability3 || cmd == Commands::Ability4) {
        int tx, ty;
        if (cmd == Commands::Ability4) {
            std::cout << "Введите координаты точки телепортации\n";
            std::cin >> tx >> ty;
            bool used = world_.GetPlayer().UseAbility(3, tx, ty);
            return used ? 1 : 0;
        }
        std::cout << "Введите координаты цели\n";
        std::cin >> tx >> ty;
        bool used = world_.GetPlayer().UseAbility(2, tx, ty);
        return used ? 1 : 0;
    }

    return TryMove(world_.GetPlayer(), cmd);
}

void EntityController::EnemyTurn() {
    for (Robot* enemy : world_.GetEnemies()) {
        if (enemy->IsAlive()) {
            Commands dir = GetRandomDirection();
            TryMove(*enemy, dir);
        }
    }
}

void EntityController::RestoreEnergy() {
    Robot& player = world_.GetPlayer();
    if (player.IsAlive()) {
        player.RestoreEnergy(kEnergyRestoreAmount);
    }
    for (Robot* enemy : world_.GetEnemies()) {
        if (enemy->IsAlive()) {
            enemy->RestoreEnergy(kEnergyRestoreAmount);
        }
    }
}

bool EntityController::IsPlayerWin() const {
    for (Robot* enemy : world_.GetEnemies()) {
        if (enemy->IsAlive()) {
            return false;
        }
    }
    return true;
}

bool EntityController::IsGameOver() const {
    return !world_.GetPlayer().IsAlive() || IsPlayerWin();
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

bool EntityController::GetDelta(Commands dir, int& dx, int& dy) {
    dx = 0;
    dy = 0;
    switch (dir) {
        case Commands::Up:      dy = 1;  return true;
        case Commands::Down:    dy = -1; return true;
        case Commands::Left:    dx = -1; return true;
        case Commands::Right:   dx = 1;  return true;

        case Commands::Ability1: return false; 
        case Commands::Ability2: return false;
        case Commands::Ability3: return false;
        case Commands::Ability4: return false;
        case Commands::Invalid: return false;
    }
    return false;
}

bool EntityController::CanStep(const Field& field, int x, int y, int steps_left, int& cost) const {
    if (!field.IsValidPosition(x, y)) return false;
    if (!field.CanMoveTo(x, y)) return false;
    
    cost = field.GetCellPassability(x, y);
    if (cost > steps_left) return false;
    
    return true;
}

EntityController::StepResult EntityController::ApplyStep(Robot& robot, int x, int y, int cost, int& steps_left) {
    Robot* target = world_.GetRobotAt(x, y);
    if (target != nullptr && target != &robot) {
        robot.Interact(*target, kHealAmount);
        return StepResult::Interacted;
    }

    world_.MoveRobot(&robot, x, y);
    steps_left -= cost;
    return StepResult::Moved;
}

int EntityController::TryMove(Robot& robot, Commands dir) {
    int dx = 0;
    int dy = 0;
    if (!GetDelta(dir, dx, dy)) return 0;

    int start_x = world_.GetX(&robot);
    int start_y = world_.GetY(&robot);
    int current_x = start_x;
    int current_y = start_y;
    int steps_left = robot.GetSpeed();

    const Field& field = world_.GetField();

    while (steps_left > 0) {
        int next_x = current_x + dx;
        int next_y = current_y + dy;

        int cost = 0;
        if (!CanStep(field, next_x, next_y, steps_left, cost)) {
            break;
        }

        StepResult result = ApplyStep(robot, next_x, next_y, cost, steps_left);
        
        if (result == StepResult::Interacted) {
            return 1;
        }

        current_x = next_x;
        current_y = next_y;
    }

    if (world_.GetX(&robot) != start_x || world_.GetY(&robot) != start_y) {
        return 1;
    }
    return 0;
}
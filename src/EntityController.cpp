#include "EntityController.hpp"

#include <random>
#include "iostream"

#include "Field.hpp"
#include "Robot.hpp"
#include "World.hpp"
#include "Cell.hpp"

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
    Robot& player = world_.GetPlayer();
    player.ProcessStatusesStart(); 

    Commands cmd = input_.GetCommand();
    int result = 0;

    if (cmd == Commands::ToggleView) {
        return -1;
    }
    if (cmd == Commands::Inventory) {
        Robot& p = world_.GetPlayer();
        if (p.GetInventorySize() == 0) {
            std::cout << "\n[!] Инвентарь пуст!\n";
            return 0;
        }

        std::cout << "\n Введите номер предмета для использования (1 - " << p.GetInventorySize() << "):";

        int choice;
        std::cin >> choice;

        if (choice > 0 && choice <= p.GetInventorySize()) {
            p.UseItem(choice - 1);
            return 1;
        }
        return 0;
    }
    if (cmd == Commands::Ability1) {
        int idx = player.FindAbilityIndex("Heal");
        if (idx != -1) result = player.UseAbility(idx) ? 1 : 0;
    }
    else if (cmd == Commands::Ability2) {
        int idx = player.FindAbilityIndex("Melee Strike");
        if (idx != -1) result = player.UseAbility(idx) ? 1 : 0;
    }
    else if (cmd == Commands::Ability3) {
        int idx = player.FindAbilityIndex("Range Attack");
        if (idx != -1) {
            int tx, ty;
            std::cout << "Введите смещение для выстрела (X Y): \n";
            std::cin >> tx >> ty;
            result = player.UseAbility(idx, tx, ty) ? 1 : 0;
        }
    }
    else if (cmd == Commands::Ability4) {
        int idx = player.FindAbilityIndex("Teleportation");
        if (idx != -1) {
            int tx, ty;
            std::cout << "Введите смещение для телепорта (X Y): \n";
            std::cin >> tx >> ty;
            result = player.UseAbility(idx, tx, ty) ? 1 : 0;
            if (result == 0) std::cout << "Телепорт не удался (стена, занято или далеко)!\n";
        } else {
            std::cout << "У вас нет этой способности!\n";
        }
    }
    else if (cmd != Commands::Invalid) {
        result = TryMove(player, cmd);
    }

    player.ProcessStatusesEnd();
    return result;
}

void EntityController::EnemyTurn() {
    std::uniform_int_distribution<> chance_dist(0, 9);

    for (Robot* enemy : world_.GetEnemies()) {
        if (!enemy->IsAlive()) continue;
        
        if (chance_dist(rng_) <= 2 && enemy->GetAbilityCount() > 0) {
            std::string ability_name = enemy->GetAbilityName(0);
            bool used = false;
            
            if (ability_name == "Heal") {
                if (enemy->GetHealth() < enemy->GetMaxHealth()) {
                    used = enemy->UseAbility(0);
                }
            }
            else if (ability_name == "Teleportation") {
                std::uniform_int_distribution<> offset_dist(-3, 3);

                int dx = offset_dist(rng_);
                int dy = offset_dist(rng_);

                used = enemy->UseAbility(0, dx, dy);
            }
            if (used) { 
                continue;
            }
        }
        Commands dir = GetRandomDirection();
        TryMove(*enemy, dir);
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
        case Commands::ToggleView: return false;
        case Commands::Inventory: return false;
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

    Cell& cell = world_.GetField().GetCellRef(x, y);
    auto cell_statuses = cell.GetStatuses();
    if (!cell_statuses.empty()) {
        std::cout << "\n[!] ВЫ НАСТУПИЛИ НА ЛОВУШКУ!\n";
        for (const auto& status : cell_statuses) {
            robot.AddStatus(status->Clone());
    }
    cell.RemoveRandomStatus();
}
    
    return StepResult::Moved;
}

int EntityController::TryMove(Robot& robot, Commands dir) {
    if (robot.HasStatus("Slow")) return 0;

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
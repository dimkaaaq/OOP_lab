#include "World.hpp"
#include "Field.hpp"
#include "Robot.hpp"
#include <stdexcept>

World::World(Field& field) : field_(field) {}

void World::AddPlayer(Robot& player, int x, int y) {
    if (!field_.IsValidPosition(x, y)) {
        throw std::invalid_argument("Player coordinates out of bounds");
    }
    if (!field_.CanMoveTo(x, y)) {
        throw std::invalid_argument("Player cannot spawn on an obstacle");
    }
    if (GetRobotAt(x, y) != nullptr) {
        throw std::invalid_argument("Cell is already occupied");
    }
    player_ = &player;
    positions_[&player] = {x, y};
}

void World::AddEnemy(Robot& enemy, int x, int y) {
    if (!field_.IsValidPosition(x, y)) {
        throw std::invalid_argument("Enemy coordinates out of bounds");
    }
    if (!field_.CanMoveTo(x, y)) {
        throw std::invalid_argument("Enemy cannot spawn on an obstacle");
    }
    if (GetRobotAt(x, y) != nullptr) {
        throw std::invalid_argument("Cell is already occupied");
    }
    enemies_.push_back(&enemy);
    positions_[&enemy] = {x, y};
}

int World::GetX(const Robot* robot) const {
    auto it = positions_.find(robot);
    return (it != positions_.end()) ? it->second.first : -1;
}

int World::GetY(const Robot* robot) const {
    auto it = positions_.find(robot);
    return (it != positions_.end()) ? it->second.second : -1;
}

void World::MoveRobot(Robot* robot, int x, int y) {
    auto it = positions_.find(robot);
    if (it != positions_.end()) {
        it->second.first = x;
        it->second.second = y;
    }
}

Robot* World::GetRobotAt(int x, int y) const {
    if (player_ != nullptr && player_->IsAlive() && GetX(player_) == x && GetY(player_) == y) {
        return player_;
    }
    for (Robot* enemy : enemies_) {
        if (enemy->IsAlive() && GetX(enemy) == x && GetY(enemy) == y) {
            return enemy;
        }
    }
    return nullptr;
}
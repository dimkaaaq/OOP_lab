#include "GameLoop.hpp"

#include <random>
#include <iostream>

GameLoop::GameLoop(Field& field, Robot& player, std::vector<Robot*> enemies, Renderer& renderer, InputController& input)
    : field_(field), player_(player), enemies_(enemies), renderer_(renderer), input_(input), rng_(std::random_device{}()) {} 

void GameLoop::RestoreEnergy() {
    if (player_.IsAlive()) {
        player_.RestoreEnergy(energy_restore_amount);
    }
    for (Robot* enemy : enemies_) {
        if (enemy->IsAlive()) {
            enemy->RestoreEnergy(energy_restore_amount);
        }
    }
}

bool GameLoop::IsPlayerWin() const {
    for (Robot* enemy : enemies_) {
        if (enemy->IsAlive()) { 
            return false;
        }
    }
    return true;
}

bool GameLoop::IsGameOver() const {
    return !player_.IsAlive() || IsPlayerWin();
}

Direction GameLoop::GetRandomDirection() {
    std::uniform_int_distribution<int> dist(0, 3);
    int value = dist(rng_);

    switch (value) {
        case 0: return Direction::Up;
        case 1: return Direction::Down;
        case 2: return Direction::Left;
        case 3: return Direction::Right;
    }
    return Direction::Invalid;
}

void GameLoop::TryMove(Robot& robot, Direction dir) {
    if (dir == Direction::Invalid) return;

    int new_x = robot.GetX();
    int new_y = robot.GetY();

    switch(dir) {
        case Direction::Up: new_y++; break;
        case Direction::Down: new_y--; break;
        case Direction::Left: new_x--; break;
        case Direction::Right: new_x++; break;
        case Direction::Invalid: return;
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
}

void GameLoop::PlayerTurn() {
    Direction dir = input_.GetCommand();
    TryMove(player_, dir);
}

void GameLoop::EnemyTurn() {
    for (Robot* enemy : enemies_) {
        if (enemy->IsAlive()) {
            Direction dir = GetRandomDirection();
            TryMove(*enemy, dir);
        }
    }
}

void GameLoop::Start() {
    while (!IsGameOver()) {
        renderer_.Render(field_, player_, enemies_);
        PlayerTurn();
        renderer_.Render(field_, player_, enemies_);
        if (IsGameOver()) break;
        EnemyTurn();
        RestoreEnergy();
        turn_++;
    }
    renderer_.RenderResult(player_.IsAlive());
}

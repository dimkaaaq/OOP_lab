#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <vector>
#include <random>

#include "Robot.hpp"
#include "Field.hpp"
#include "InputController.hpp"
#include "Renderer.hpp"

class GameLoop {
public:
    GameLoop(Field& field, Robot& player, std::vector<Robot*> enemies, Renderer& renderer, InputController& input);

    void Start();
private:
    static const int energy_restore_amount = 10;
    static const int heal_amount = 10;

    void PlayerTurn();
    void EnemyTurn();
    void TryMove(Robot& robot, Direction dir);
    void RestoreEnergy();
    bool IsGameOver() const;
    bool IsPlayerWin() const;
    Direction GetRandomDirection();

    Field& field_;
    Robot& player_;
    std::vector<Robot*> enemies_;
    Renderer& renderer_;
    InputController& input_;
    std::mt19937 rng_;

    int turn_ = 0;
    bool is_game_over_ = false;
};

#endif
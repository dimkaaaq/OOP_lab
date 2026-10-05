#ifndef ENTITY_CONTROLLER_HPP
#define ENTITY_CONTROLLER_HPP

#include <random>
#include <vector>

#include "Field.hpp"
#include "InputController.hpp"
#include "Robot.hpp"

class EntityController {
public:
    EntityController(Field& field, Robot& player,
                     std::vector<Robot*>& enemies,
                     InputController& input);

    int PlayerTurn();
    void EnemyTurn();
    void RestoreEnergy();
    bool IsGameOver() const;
    bool IsPlayerWin() const;

private:
    int TryMove(Robot& robot, Commands dir);
    Commands GetRandomDirection();

    static constexpr int kEnergyRestoreAmount = 10;
    static constexpr int kHealAmount = 10;

    Field& field_;
    Robot& player_;
    std::vector<Robot*>& enemies_;
    InputController& input_;
    std::mt19937 rng_;
};

#endif
#ifndef ENTITY_CONTROLLER_HPP
#define ENTITY_CONTROLLER_HPP

#include <random>
#include <vector>

#include "Field.hpp"
#include "InputController.hpp"
#include "Robot.hpp"
#include "Vision.hpp"

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
    const Vision& GetVision() const { return vision_; }
    void UpdateVision();

private:
    int TryMove(Robot& robot, Commands dir);
    Commands GetRandomDirection();

    static const int kEnergyRestoreAmount = 10;
    static const int kHealAmount = 10;

    Field& field_;
    Robot& player_;
    std::vector<Robot*>& enemies_;
    InputController& input_;
    Vision vision_;
    std::mt19937 rng_;
};

#endif
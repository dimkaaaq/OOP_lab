#ifndef ENTITY_CONTROLLER_HPP
#define ENTITY_CONTROLLER_HPP

#include <random>
#include <vector>

#include "InputController.hpp"
#include "Vision.hpp"

class World;
class Robot;
class Field;

class EntityController {
public:
    EntityController(World& world, InputController& input);

    int PlayerTurn();
    void EnemyTurn();
    void RestoreEnergy();
    bool IsGameOver() const;
    bool IsPlayerWin() const;
    const Vision& GetVision() const { return vision_; }
    void UpdateVision();

private:
    enum class StepResult {
        Blocked,
        Moved,
        Interacted
    };

    int TryMove(Robot& robot, Commands dir);
    Commands GetRandomDirection();
    
    static bool GetDelta(Commands dir, int& dx, int& dy);
    bool CanStep(const Field& field, int x, int y, int steps_left, int& cost) const;
    StepResult ApplyStep(Robot& robot, int x, int y, int cost, int& steps_left);

    static const int kEnergyRestoreAmount = 10;
    static const int kHealAmount = 10;

    World& world_;
    InputController& input_;
    Vision vision_;
    std::mt19937 rng_;
};

#endif
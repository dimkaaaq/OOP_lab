#include "TeleportAbility.hpp"
#include "World.hpp"
#include "Robot.hpp"
#include "Field.hpp"
#include <cmath>

TeleportAbility::TeleportAbility(World& world) : world_(world) {}


bool TeleportAbility::Use(Robot& caster, int target_x, int target_y) {
    if (caster.GetEnergy() < GetEnergyCost()) {
        return false;
    }

    int cx = world_.GetX(&caster);
    int cy = world_.GetY(&caster);

    int dx = cx + target_x;
    int dy = cy + target_y;

    double dist = std::sqrt(std::pow(target_x, 2) + std::pow(target_y, 2));
    if (dist > 5.0) {
        return false;
    }
    
    const Field& field = world_.GetField();
    if (!field.CanMoveTo(dx, dy)) {
        return false;
    }
    
    if (world_.GetRobotAt(dx, dy) != nullptr) {
        return false;
    }

    caster.SpendEnergy(GetEnergyCost());
    world_.MoveRobot(&caster, dx, dy);
    return true;
}

std::string TeleportAbility::GetName() const {
    return "Teleportation";
}
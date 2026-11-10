#include "RangeAbility.hpp"
#include "World.hpp"
#include "Robot.hpp"
#include <cmath>
#include "statuses/BurnStatus.hpp"

RangeAbility::RangeAbility(World& world) : world_(world) {}

bool RangeAbility::Use(Robot& caster, int target_x, int target_y) {
    if (caster.GetEnergy() < GetEnergyCost()) return false;

    int cx = world_.GetX(&caster);
    int cy = world_.GetY(&caster);

    int dx = cx + target_x;
    int dy = cy + target_y;

    double dist = std::sqrt(std::pow(dx - cx, 2) + std::pow(dy - cy, 2));
    if (dist > 3.0) return false;
    
    
    Robot* target = world_.GetRobotAt(dx, dy);

    if (target == nullptr || target->GetTeam() == caster.GetTeam()) return true;

    caster.SpendEnergy(GetEnergyCost());
    target->TakeDamage(caster.GetDamage() + damage_);
    target->AddStatus(std::make_shared<BurnStatus>(3, 5));

    return true;
}

int RangeAbility::GetEnergyCost() const {
    return 20;
}

std::string RangeAbility::GetName() const {
    return "Range Attack";
}
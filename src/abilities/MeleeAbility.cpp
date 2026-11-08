#include "MeleeAbility.hpp"
#include "Robot.hpp"
#include "World.hpp"
#include "math.h"

MeleeAbility::MeleeAbility(World& world) : world_(world) {}

bool MeleeAbility::Use(Robot& caster, int, int) {
    if (caster.GetEnergy() < GetEnergyCost()) {
        return false;
    }

    caster.SpendEnergy(GetEnergyCost());

    int cx = world_.GetX(&caster);
    int cy = world_.GetY(&caster);

    for (Robot* enemy : world_.GetEnemies()) {
        if (!enemy->IsAlive()) continue;

        int ex = world_.GetX(enemy);
        int ey = world_.GetY(enemy);

        if (std::abs(ex - cx) <= 1 && std::abs(ey - cy) <= 1) { 
            enemy->TakeDamage(caster.GetDamage());
        }
    }
    return true;
}

int MeleeAbility::GetEnergyCost() const {
    return 20;  
}

std::string MeleeAbility::GetName() const {
    return "Melee Strike";
}
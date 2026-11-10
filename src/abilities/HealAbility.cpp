#include "HealAbility.hpp"
#include "Robot.hpp"

bool HealAbility::Use(Robot& caster, int, int) {
    if (caster.GetEnergy() < GetEnergyCost()) {
        return false;
    }

    caster.SpendEnergy(GetEnergyCost());
    caster.TakeHeal(heal_amount_);
    return true;
    
}

int HealAbility::GetEnergyCost() const {
    return 15;
}

std::string HealAbility::GetName() const {
    return "Heal";
}
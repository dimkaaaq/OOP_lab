#include "HealAbility.hpp"
#include "Robot.hpp"
#include "statuses/ShieldStatus.hpp"

bool HealAbility::Use(Robot& caster, int, int) {
    if (caster.GetEnergy() < GetEnergyCost()) {
        return false;
    }

    caster.SpendEnergy(GetEnergyCost());
    if ((caster.GetHealth() + heal_amount_) > caster.GetMaxHealth()) {
        int shield_hp = (caster.GetHealth() + heal_amount_) - caster.GetMaxHealth();
        caster.TakeHeal(caster.GetMaxHealth());
        caster.AddStatus(std::make_shared<ShieldStatus>(shield_hp)); 
    } else {
        caster.TakeHeal(heal_amount_);
    }
    return true;
    
}

int HealAbility::GetEnergyCost() const {
    return 15;
}

std::string HealAbility::GetName() const {
    return "Heal";
}
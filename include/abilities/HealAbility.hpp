#ifndef HEAL_ABILITY_HPP
#define HEAL_ABILITY_HPP

#include "IAbility.hpp"

class HealAbility : public IAbility {
public:
    bool Use(Robot& caster, int target_x = -1, int target_y = -1) override;
    
    int GetEnergyCost() const override;
    std::string GetName() const override;
};

#endif
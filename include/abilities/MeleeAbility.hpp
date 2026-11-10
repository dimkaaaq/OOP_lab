#ifndef MELEE_ABILITY_HPP
#define MELEE_ABILITY_HPP

#include "IAbility.hpp"

class World;

class MeleeAbility : public IAbility {
public:
    explicit MeleeAbility(World& world);

    bool Use(Robot& caster, int target_x = -1, int target_y = -1) override;
    
    int GetEnergyCost() const override;
    std::string GetName() const override;
    void Upgrade() override { range_ += 2; }
    int GetLevel() const override { return level_; }
private:
    World& world_;
    int level_ = 1;
    int range_ = 5;
};

#endif
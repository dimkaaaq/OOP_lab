#ifndef TELEPORT_ABILITY_HPP
#define TELEPORT_ABILITY_HPP

#include "IAbility.hpp"

class World;

class TeleportAbility : public IAbility {
public:
    explicit TeleportAbility(World& world);
    bool Use(Robot& caster, int target_x = -1, int target_y = -1) override;
    int GetEnergyCost() const override { return 30 - energy_consumption_reduction_; }
    std::string GetName() const override;
    void Upgrade() override { energy_consumption_reduction_ += 5; level_++; }
    int GetLevel() const override { return level_; }
private:
    World& world_;
    int level_ = 1;
    int energy_consumption_reduction_ = 0;
};

#endif
#ifndef TELEPORT_ABILITY_HPP
#define TELEPORT_ABILITY_HPP

#include "IAbility.hpp"

class World;

class TeleportAbility : public IAbility {
public:
    explicit TeleportAbility(World& world);
    bool Use(Robot& caster, int target_x = -1, int target_y = -1) override;
    int GetEnergyCost() const override;
    std::string GetName() const override;

private:
    World& world_;
};

#endif
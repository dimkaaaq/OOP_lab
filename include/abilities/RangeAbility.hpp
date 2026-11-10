#ifndef RANGE_ABILITY_HPP
#define RANGE_ABILITY_HPP

#include "IAbility.hpp"

class World;

class RangeAbility : public IAbility {
public:
    explicit RangeAbility(World& world);

    bool Use(Robot& caster, int target_x = -1, int target_y = -1) override;
    
    int GetEnergyCost() const override;
    std::string GetName() const override;
    void Upgrade() override { damage_ += 10; level_++; }
    int GetLevel() const override { return level_; }
private:
    World& world_;
    int level_ = 1;
    int damage_ = 0;
};

#endif
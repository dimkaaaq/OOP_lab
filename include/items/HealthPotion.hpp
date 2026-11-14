#ifndef HEALTH_POTION_HPP
#define HEALTH_POTION_HPP

#include "items/IItem.hpp"

class HealthPotion : public IItem {
public:
    void Use(Robot& target) override;
    std::string GetName() const override { return "Health_Potion"; }
};

#endif


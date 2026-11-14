#ifndef ENERGY_POTION_HPP
#define ENERGY_POTION_HPP

#include "items/IItem.hpp"

class EnergyPotion : public IItem {
public:
    void Use(Robot& target) override;
    std::string GetName() const override { return "Energy_Potion"; }
};

#endif


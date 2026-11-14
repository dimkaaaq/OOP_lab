#ifndef ATTACK_POTION_HPP
#define ATTACK_POTION_HPP

#include "items/IItem.hpp"

class AttackPotion : public IItem {
public:
    void Use(Robot& target) override;
    std::string GetName() const override { return "Attack_Potion"; }

};

#endif

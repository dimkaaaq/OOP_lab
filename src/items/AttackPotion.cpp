#include "items/AttackPotion.hpp"
#include "Robot.hpp"
#include "statuses/AttackBoostStatus.hpp"
#include <iostream>
#include <memory>

void AttackPotion::Use(Robot& target) {
    target.AddStatus(std::make_shared<AttackBoostStatus>(3));
    std::cout << "\n[+] Вы выпили зелье атаки! Ваш урон временно повышен.\n";
}
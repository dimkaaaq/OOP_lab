#include "items/EnergyPotion.hpp"
#include "core/Robot.hpp"
#include <iostream>

void EnergyPotion::Use(Robot& target) {
    target.RestoreEnergy(40);
    std::cout << "\n[+] Вы выпили зелье энергии и восстановили 40 энергии!\n";
}
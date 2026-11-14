#include "items/HealthPotion.hpp"
#include "Robot.hpp"
#include <iostream>

void HealthPotion::Use(Robot& target) {
    target.TakeHeal(30);
    std::cout << "\n[+] Вы выпили зелье здоровья и восстановили 30 HP!\n";
}
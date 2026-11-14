#include "statuses/LootStatus.hpp"
#include "Robot.hpp"

#include <iostream>
#include <random>
#include <memory>

#include "items/HealthPotion.hpp"
#include "items/EnergyPotion.hpp"
#include "items/AttackPotion.hpp"

void LootStatus::Apply(Robot& target) {
    if (target.GetTeam() != 1) {
        return;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>dist(0, 2);

    int item_type = dist(gen);
    std::shared_ptr<IItem> item;

    if (item_type == 0) {
        item = std::make_shared<HealthPotion>();
    } else if (item_type == 1) {
        item = std::make_shared<EnergyPotion>();
    } else if (item_type == 2) {
        item = std::make_shared<AttackPotion>();
    }
    
    target.AddItem(item);
    std::cout << "\n Вы нашли предмет: " << item->GetName() << "!\n";

}
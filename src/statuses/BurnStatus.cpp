#include "statuses/BurnStatus.hpp"
#include "Robot.hpp"
#include <iostream>

void BurnStatus::OnTurnStart(Robot& target) {
    target.TakeDamage(damage_);
}

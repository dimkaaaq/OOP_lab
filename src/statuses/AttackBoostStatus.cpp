#include "statuses/AttackBoostStatus.hpp"
#include "Robot.hpp"

void AttackBoostStatus::Apply(Robot& target) {
    target.IncreaseDamage(15);

}

void AttackBoostStatus::OnTurnEnd(Robot& target) {
    duration_--;
    if (duration_ == 0) {
        target.DecreaseDamage(15);
    }
}
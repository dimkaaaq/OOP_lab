#include "Robot.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "statuses/ShieldStatus.hpp"

Robot::Robot(int team, int max_health, int damage, int max_energy,
             int required_exp, int speed)
    : team_(team),
      max_health_(max_health),
      current_health_(max_health),
      damage_(damage),
      max_energy_(max_energy),
      current_energy_(max_energy),
      current_exp_(0),
      required_exp_(required_exp),
      rank_(1),
      speed_(speed) 
{
    if (max_health <= 0) throw std::invalid_argument("Max health must be positive");
    if (damage < 0) throw std::invalid_argument("Damage cannot be negative");
    if (max_energy < 0) throw std::invalid_argument("Max energy cannot be negative");
    if (required_exp <= 0) throw std::invalid_argument("Required exp must be positive");
    if (speed <= 0) throw std::invalid_argument("Speed must be at least 1");
}

void Robot::TakeDamage(int value) {
    int remaining_damage = value;
    
    for (auto& status: statuses_) {
        remaining_damage = status->AbsorbDamage(remaining_damage);
        if (remaining_damage <= 0) break;
    }
    current_health_ -= remaining_damage;
    if (current_health_ < 0) {
        current_health_ = 0;
    }
}

void Robot::TakeHeal(int value) {
    current_health_ += value;
    if (current_health_ > max_health_) {
        current_health_ = max_health_;
    }
}

void Robot::RestoreEnergy(int value) {
    current_energy_ += value;
    if (current_energy_ > max_energy_) {
        current_energy_ = max_energy_;
    }
}

void Robot::SpendEnergy(int value) {
    current_energy_ -= value;
    if (current_energy_ < 0) {
        current_energy_ = 0;
    }
}

void Robot::GainExp(int value) {
    if (value > 0) {
        current_exp_ += value;
        TryRankUp();
    }
}

void Robot::IncreaseMaxHealth(int new_max_health) {
    if (new_max_health > max_health_) {
        max_health_ = new_max_health;
        if (current_health_ > max_health_) {
            current_health_ = max_health_;
        }
    }
}

void Robot::IncreaseDamage(int value) {
    if (value > 0) {
        damage_ += value;
    }
}

void Robot::IncreaseSpeed(int value) {
    if (value > 0) {
        speed_ += value;
    }
}

void Robot::Interact(Robot& target, int heal_value) {
    if (&target == this || !target.IsAlive()) {
        return;
    }
    if (target.GetTeam() == team_) {
        target.TakeHeal(heal_value);
    } else {
        target.TakeDamage(damage_);
        if (!target.IsAlive()) {
            GainExp(100);
        }
    }
}

void Robot::TryRankUp() {
    while (current_exp_ >= required_exp_) {
        current_exp_ -= required_exp_;
        required_exp_ = required_exp_ * 13 / 10;
        ++rank_;
        ++pending_rank_ups_;
        IncreaseMaxHealth(max_health_ + 20);
        IncreaseDamage(5);
    }
}

void Robot::AddAbility(std::shared_ptr<IAbility> ability) {
    if (ability) {
        abilities_.push_back(ability);
    }
}

bool Robot::UseAbility(int index, int target_x, int target_y) {
    if (this->HasStatus("Overload")) {
        this->RemoveStatus("Overload");
        std::cout << "Перегрузка! Способность заблокирована.\n";
        return false;
    }
    if (index >= 0 && index < static_cast<int>(abilities_.size())) {
    return abilities_[index]->Use(*this, target_x, target_y);        
    }
    return false;
}

void Robot::AddStatus(std::shared_ptr<IStatus> status) {
    if (!status) return;
    std::string name = status->GetName();

    for (auto& existing : statuses_) {
        if (existing->GetName() == name) {
            if (name == "Shield") {
                statuses_.push_back(status);
                return;
            } else if (name == "Overload") {
                return;
            } else if (name == "Burn" || name == "Slow") {
                statuses_.push_back(status);
                return;
            }
        }
    }
    status->Apply(*this);
    statuses_.push_back(status);
}

void Robot::RemoveStatus(const std::string& name) {
    statuses_.erase(
        std::remove_if(statuses_.begin(), statuses_.end(),
            [&name](const std::shared_ptr<IStatus>& s) { return s->GetName() == name; }),
        statuses_.end()
    );
}

void Robot::ProcessStatusesStart() {
    for (auto& status : statuses_) {
        status->OnTurnStart(*this);
    }
}

void Robot::ProcessStatusesEnd() {
    for (auto& status : statuses_) {
        status->OnTurnEnd(*this);
    }

    statuses_.erase(
        std::remove_if(statuses_.begin(), statuses_.end(),
            [](const std::shared_ptr<IStatus>& s) { 
                return s->IsExpired(); 
            }),
        statuses_.end()
    );
}

bool Robot::HasStatus(const std::string& name) const {
    for (const auto& status : statuses_) {
        if (status->GetName() == name) return true;
    }
    return false;
}

void Robot::UpgradeAbility(int idx) {
    if (idx >= 0 && idx < static_cast<int>(abilities_.size())) {
        abilities_[idx]->Upgrade();
    }
}

int Robot::FindAbilityIndex(const std::string& name) const {
    for (int i = 0; i < static_cast<int>(abilities_.size()); ++i) {
        if (abilities_[i]->GetName() == name) {
            return i; 
        }
    }
    return -1;
}

int Robot::GetAbilityLevel(int index) const {
    if (index >= 0 && index < static_cast<int>(abilities_.size())) {
        return abilities_[index]->GetLevel();
    }
    return 0;
}

std::string Robot::GetAbilityName(int index) const {
    if (index >= 0 && index < static_cast<int>(abilities_.size())) {
        return abilities_[index]->GetName();
    }
    return "None";
}

int Robot::GetShieldAmount() const {
    for (const auto& status : statuses_) {
        if (status->GetName() == "Shield") {
            auto shield = std::dynamic_pointer_cast<ShieldStatus>(status);
            if (shield) {
                return shield->GetAmount();
            }
        }
    }
    return 0;
}

void Robot::AddItem(std::shared_ptr<IItem> item) {
    if (item) {
        return inventory_.push_back(item);
    }
}

bool Robot::UseItem(int index) {
    if (index >= 0 && index < static_cast<int>(inventory_.size())) {
        inventory_[index]->Use(*this);
        inventory_.erase(inventory_.begin() + index);
        return true;
    }
    return false;
}

int Robot::GetInventorySize() const {
    return inventory_.size();
}

std::string Robot::GetItemName(int index) const {
    if (index >= 0 && index < static_cast<int>(inventory_.size())) {
        return inventory_[index]->GetName();
    }
    return "None";
}

void Robot::DecreaseDamage(int value) {
    damage_ -= value;
    if (damage_ < 0) damage_ = 0;
}
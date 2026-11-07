#include "Robot.hpp"
#include <stdexcept>

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
    current_health_ -= value;
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
    }
}

void Robot::TryRankUp() {
    while (current_exp_ >= required_exp_) {
        current_exp_ -= required_exp_;
        required_exp_ = required_exp_ * 13 / 10;
        ++rank_;
        IncreaseMaxHealth(max_health_ + 20);
        IncreaseDamage(5);
    }
}
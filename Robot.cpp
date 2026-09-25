#include "Robot.hpp"

#include <stdexcept>

Robot::Robot(std::string team, int max_health, int damage, int max_energy,
             int required_exp, int x, int y)
    : team_(team),
      x_(x),
      y_(y),
      max_health_(max_health),
      current_health_(max_health),
      damage_(damage),
      max_energy_(max_energy),
      current_energy_(max_energy),
      current_exp_(0),
      required_exp_(required_exp),
      rank_(1),
      speed_(1) {}

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
    current_exp_ += value;
    TryRankUp();
}

void Robot::IncreaseMaxHealth(int new_max_health) {
    max_health_ = new_max_health;
}

void Robot::IncreaseDamage(int value) {
    damage_ += value;
}

void Robot::IncreaseSpeed(int value) {
    speed_ += value;
}

void Robot::Interact(Robot& target, int heal_value) {
    if (&target == this) {
        return;
    }
    if (target.GetTeam() == team_) {
        target.TakeHeal(heal_value);
    } else {
        target.TakeDamage(damage_);
    }
}

void Robot::MoveTo(int x, int y) {
    if (x < 0 || y < 0) {
        throw std::invalid_argument("Coordinates must be non-negative");
    }
    x_ = x;
    y_ = y;
}

void Robot::TryRankUp() {
    while (current_exp_ >= required_exp_) {
        current_exp_ -= required_exp_;
        required_exp_ = required_exp_ * 13 / 10;
        ++rank_;
        max_health_ += 20;
        damage_ += 5;
    }
}
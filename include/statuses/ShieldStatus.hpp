#ifndef SHIELD_STATUS_HPP
#define SHIELD_STATUS_HPP

#include "statuses/IStatus.hpp"
#include <algorithm>

class ShieldStatus : public IStatus {
public:
    ShieldStatus(int amount) : amount_(amount) {}
    void Apply(Robot&) override {}
    void OnTurnStart(Robot&) override {}
    void OnTurnEnd(Robot&) override { amount_--; }
    bool IsExpired() const override { return amount_ <= 0; }
    std::string GetName() const override { return "Shield"; }
    int GetAmount() const { return amount_; }
    void ReduceAmount(int amount) { amount_ -= amount; if (amount_ < 0) amount_ = 0; }
    std::shared_ptr<IStatus> Clone() const override {
        return std::make_shared<ShieldStatus>(amount_);
    }
    int AbsorbDamage(int damage) override {
        if (amount_ <= 0) return damage;
        int absorbed = std::min(damage, amount_);
        amount_ -= absorbed;
        return damage - absorbed;
    }
private:
    int amount_;
};

#endif  
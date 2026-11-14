#ifndef LOOT_STATUS_HPP
#define LOOT_STATUS_HPP

#include "statuses/IStatus.hpp"


class LootStatus : public IStatus {
public:
    LootStatus() = default;

    void Apply(Robot& target) override;

    void OnTurnStart(Robot&) override {}
    void OnTurnEnd(Robot&) override {}

    bool IsExpired() const override {return true; }
    std::string GetName() const override {return "Loot"; }
        std::shared_ptr<IStatus> Clone() const override {
        return std::make_shared<LootStatus>();
    }

    int AbsorbDamage(int damage) override {return damage; }
};

#endif
#ifndef BURN_STATUS_HPP
#define BURN_STATUS_HPP

#include "statuses/IStatus.hpp"

class BurnStatus : public IStatus {
public:
    BurnStatus(int duration, int damage) : duration_(duration), damage_(damage) {}
    void Apply(Robot&) override {}
    void OnTurnStart(Robot&) override; 
    void OnTurnEnd(Robot&) override { duration_--; }
    bool IsExpired() const override { return duration_ <= 0; }
    std::string GetName() const override { return "Burn"; }
        std::shared_ptr<IStatus> Clone() const override {
        return std::make_shared<BurnStatus>(duration_, damage_);
    }
private:
    int duration_;
    int damage_;
};

#endif
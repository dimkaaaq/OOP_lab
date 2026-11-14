#ifndef ATTACK_BOOST_STATUS_HPP
#define ATTACK_BOOST_STATUS_HPP

#include "statuses/IStatus.hpp"

class AttackBoostStatus : public IStatus {
public:
    AttackBoostStatus(int duration) : duration_(duration) {}
    
    void Apply(Robot& target) override; 
    void OnTurnStart(Robot&) override {}
    void OnTurnEnd(Robot& target) override;
    bool IsExpired() const override { return duration_ <= 0; }
    std::string GetName() const override { return "Attack Boost"; }
    int AbsorbDamage(int damage) override { return damage; }
    std::shared_ptr<IStatus> Clone() const override { return std::make_shared<AttackBoostStatus>(duration_); }
private:
    int duration_;
};

#endif
#ifndef SLOW_STATUS_HPP
#define SLOW_STATUS_HPP

#include "IStatus.hpp"

class SlowStatus : public IStatus {
public:
    SlowStatus(int duration) : duration_(duration) {}
    void Apply(Robot& target) override {}
    void OnTurnStart(Robot& target) override {}
    void OnTurnEnd(Robot& target) override { duration_--; }
    bool IsExpired() const override { return duration_ <= 0; }
    std::string GetName() const override { return "Slow"; }
private:
    int duration_;
};

#endif
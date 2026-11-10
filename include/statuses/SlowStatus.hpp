#ifndef SLOW_STATUS_HPP
#define SLOW_STATUS_HPP

#include "statuses/IStatus.hpp"

class SlowStatus : public IStatus {
public:
    SlowStatus(int duration) : duration_(duration) {}
    void Apply(Robot&) override {}
    void OnTurnStart(Robot&) override {}
    void OnTurnEnd(Robot&) override { duration_--; }
    bool IsExpired() const override { return duration_ <= 0; }
    std::string GetName() const override { return "Slow"; }
    std::shared_ptr<IStatus> Clone() const override {
        return std::make_shared<SlowStatus>(duration_);
    }
private:
    int duration_;
};

#endif
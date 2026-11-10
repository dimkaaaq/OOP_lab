#ifndef OVERLOAD_STATUS_HPP
#define OVERLOAD_STATUS_HPP

#include "statuses/IStatus.hpp"

class OverloadStatus : public IStatus {
public:
    void Apply(Robot&) override {}
    void OnTurnStart(Robot&) override {}
    void OnTurnEnd(Robot&) override {}
    bool IsExpired() const override { return false; }
    std::string GetName() const override { return "Overload"; }
        std::shared_ptr<IStatus> Clone() const override {
        return std::make_shared<OverloadStatus>();
    }
};

#endif
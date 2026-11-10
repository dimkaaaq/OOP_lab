#ifndef ISTATUS_HPP
#define ISTATUS_HPP

#include <string>

class Robot;

class IStatus {
public:
    virtual ~IStatus() = default;

    virtual void Apply(Robot& target);
    virtual void OnTurnStart(Robot& target);
    virtual void OnTurnEnd(Robot& target) = 0;
    virtual bool IsExpired() const = 0;
    virtual std::string GetName() const = 0;
};    

#endif
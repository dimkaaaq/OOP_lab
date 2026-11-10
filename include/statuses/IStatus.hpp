#ifndef ISTATUS_HPP
#define ISTATUS_HPP

#include <string>
#include <memory>

class Robot;

class IStatus {
public:
    virtual ~IStatus() = default;

    virtual void Apply(Robot&) = 0;
    virtual void OnTurnStart(Robot&) = 0;
    virtual void OnTurnEnd(Robot&) = 0;
    virtual bool IsExpired() const = 0;
    virtual std::string GetName() const = 0;
    virtual std::shared_ptr<IStatus> Clone() const = 0;
    virtual int AbsorbDamage(int damage) { return damage; }
};

#endif
#ifndef IABILITY_HPP
#define IABILITY_HPP


#include <string>

class Robot;

class IAbility {
public:
    virtual ~IAbility() = default;

    virtual bool Use(Robot& caster, int target_x = -1, int target_y = -1) = 0;
    virtual int GetEnergyCost() const = 0;
    virtual std::string GetName() const = 0;
};

#endif

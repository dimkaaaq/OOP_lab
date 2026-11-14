#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Robot;

class IItem {
public:
    virtual ~IItem() = default;
    virtual void Use(Robot& target) = 0;
    virtual std::string GetName() const = 0;
};

#endif
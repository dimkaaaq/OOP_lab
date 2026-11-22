#ifndef LEVEL_GENERATOR_HPP
#define LEVEL_GENERATOR_HPP

#include <vector>

class Robot;
class Field;

class ILevelGenerator {
public:
    virtual ~ILevelGenerator() = default;

    virtual bool HasNextLevel() const = 0;
    virtual void GenerateLevel(Field& field, std::vector<Robot*>& enemies) = 0;
    virtual int GetCurrentLevelIndex() const = 0;

};

#endif
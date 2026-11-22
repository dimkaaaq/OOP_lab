#ifndef RANDOM_LEVEL_GENERATOR_HPP
#define RANDOM_LEVEL_GENERATOR_HPP

#include "ILevelGenerator.hpp"

class RandomLevelGenerator : public ILevelGenerator {
public:

    RandomLevelGenerator(int maxLevels);
    bool HasNextLevel() const override;
    void GenerateLevel(Field& field, std::vector<Robot*>& enemies) override;
    int GetCurrentLevelIndex() const override;
private:

    int maxLevels_;
    int currentLevel_;
};

#endif
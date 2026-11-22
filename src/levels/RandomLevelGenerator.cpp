#include "levels/RandomLevelGenerator.hpp"
#include "core/Field.hpp"
#include "core/Robot.hpp"

RandomLevelGenerator::RandomLevelGenerator(int maxLevels) 
    : maxLevels_(maxLevels), currentLevel_(0) {}

bool RandomLevelGenerator::HasNextLevel() const {
    return currentLevel_ < maxLevels_;
}

void RandomLevelGenerator::GenerateLevel(Field& field, std::vector<Robot*>& enemies) {
    currentLevel_++;

    field = Field::GenerateField();

    enemies.clear();

    for (int i = 0; i < currentLevel_ + 1; ++i) {
        Robot* enemy = new Robot(2, 30, 8, 100, 100, 2);
        enemies.push_back(enemy);
    }
}

int RandomLevelGenerator::GetCurrentLevelIndex() const {
    return currentLevel_;
}
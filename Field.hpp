#ifndef BATTLE_FIELD_
#define BATTLE_FIELD_

#include <vector>

#include "Cell.hpp"

class Field {
public:
    Field(int width, int height);

    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
    
    bool CanMoveTo(int x, int y) const;
    bool IsValidPosition(int x, int y) const;
    void SetObstacle(int x, int y);
    void RemoveObstacle(int x, int y);

private:
    static const int MIN_SIZE = 3;
    static const int MAX_SIZE = 100;

    int width_;
    int height_;
    std::vector<std::vector<Cell>> grid_;

};

#endif
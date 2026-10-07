#ifndef BATTLE_FIELD_
#define BATTLE_FIELD_

#include <vector>

#include "Cell.hpp"

class Field {
public:
    Field(int width, int height);
    const Cell& GetCell(int x, int y) const;
    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
    
    bool CanMoveTo(int x, int y) const;
    bool IsValidPosition(int x, int y) const;
    void SetObstacle(int x, int y);
    void RemoveObstacle(int x, int y);
    int GetCellPassability(int x, int y) const;  
    void SetPassability(int x, int y, int value);
    static Field GenerateField();

private:
    static const int kMinSize = 3;
    static const int kMaxSize = 100;

    int width_;
    int height_;
    std::vector<std::vector<Cell>> grid_;

};

#endif
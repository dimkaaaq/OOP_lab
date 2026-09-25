#include "Field.hpp"

Field::Field(int width, int height {
    if (width > MAX_SIZE) width_ = MAX_SIZE;
    else if (width < MIN_SIZE) width_ = MIN_SIZE;
    else width_ = width;

    if (height > MAX_SIZE) height_ = MAX_SIZE;
    else if (height < MIN_SIZE) height_ = MIN_SIZE;
    else height_ = height;

    grid_.resize(height_, std::vector<Cell>(width_)); 
}

bool Field::IsValidPosition(int x, int y) const {
    return (x >= 0 && y >= 0 && x < width_ && y < height_);
}

void Field::SetObstacle(int x, int y) {
    if (IsValidPosition(x, y)) grid_[y][x].SetPassable(false);
}

void Field::RemoveObstacle(int x, int y) {
    if (IsValidPosition(x, y)) grid_[y][x].SetPassable(true);
}

bool Field::CanMoveTo(int x, int y) const {
    return IsValidPosition(x, y) && grid_[y][x].IsPassable();
}

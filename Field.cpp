#include "Field.hpp"
#include "Robot.hpp"

Field::Field(int width, int height){
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

Field Field::GenerateField() {
    Field field = Field(20, 14);
    for (int x = 2; x <= 6; ++x)  field.SetObstacle(x, 12);
    for (int x = 13; x <= 17; ++x) field.SetObstacle(x, 12);

    for (int y = 9; y <= 11; ++y) field.SetObstacle(9, y);


    for (int x = 3; x <= 7; ++x)  field.SetObstacle(x, 8);
    for (int x = 12; x <= 16; ++x) field.SetObstacle(x, 8);

    for (int y = 4; y <= 6; ++y) {
        field.SetObstacle(3, y);
        field.SetObstacle(16, y);
    }
    for (int x = 7; x <= 12; ++x) field.SetObstacle(x, 2);

    return field;
}

int Field::GetCellPassability(int x, int y) const {
    if (!IsValidPosition(x, y)) {
        return 1;
    }
    return grid_[y][x].GetPassability();
}

void Field::SetPassability(int x, int y, int value) {
    if (IsValidPosition(x, y)) {
        grid_[y][x].SetPassability(value);
    }
}
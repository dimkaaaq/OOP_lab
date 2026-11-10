#include "Field.hpp"
#include <random>
#include "statuses/BurnStatus.hpp"
#include "statuses/SlowStatus.hpp"
#include "statuses/ShieldStatus.hpp"
#include "statuses/OverloadStatus.hpp"

Field::Field(int width, int height){
    if (width > kMaxSize) width_ = kMaxSize;
    else if (width < kMinSize) width_ = kMinSize;
    else width_ = width;

    if (height > kMaxSize) height_ = kMaxSize;
    else if (height < kMinSize) height_ = kMinSize;
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

    for (int x = 2; x <= 6; ++x)   field.SetObstacle(x, 12);
    for (int x = 13; x <= 17; ++x) field.SetObstacle(x, 12);

    for (int y = 9; y <= 11; ++y)  field.SetObstacle(9, y);

    for (int x = 3; x <= 7; ++x)   field.SetObstacle(x, 8);
    for (int x = 12; x <= 16; ++x) field.SetObstacle(x, 8);

    for (int y = 4; y <= 6; ++y) {
        field.SetObstacle(3, y);
        field.SetObstacle(16, y);
    }
    for (int x = 7; x <= 12; ++x)  field.SetObstacle(x, 2);

    for (int x = 1; x <= 4; ++x)   field.SetPassability(x, 5, 2);
    for (int x = 1; x <= 4; ++x)   field.SetPassability(x, 6, 2);

    for (int x = 14; x <= 18; ++x) field.SetPassability(x, 9,  2);
    for (int x = 14; x <= 18; ++x) field.SetPassability(x, 10, 2);

    field.SetPassability(10, 6, 2);
    field.SetPassability(10, 5, 2);

    for (int x = 1; x <= 4; ++x)   field.SetPassability(x, 1, 3);
    for (int x = 1; x <= 4; ++x)   field.SetPassability(x, 2, 3);

    for (int x = 15; x <= 18; ++x) field.SetPassability(x, 3, 3);
    for (int x = 15; x <= 18; ++x) field.SetPassability(x, 4, 3);

    field.SetPassability(11, 10, 3);
    field.SetPassability(12, 10, 3);
    field.SetPassability(11, 11, 3);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> chance(0, 99);
    std::uniform_int_distribution<> type_dist(0, 3);

    for (int  y = 0; y < field.GetHeight(); ++y) {
        for (int  x = 0; x < field.GetWidth(); ++x) {
            if (!field.CanMoveTo(x, y) || (x == 0 && y == 0)) continue;
            
            int roll = chance(gen);
            int num_statuses;

            if (roll < 10) num_statuses = 1;
            else if (roll < 12) num_statuses = 2;
            for (int i = 0; i < num_statuses; ++i) {
                int type = chance(gen);
                std::shared_ptr<IStatus> status;

                if (type == 0) status = std::make_shared<BurnStatus>(3, 5);
                else if (type == 1) status = std::make_shared<SlowStatus>(2);
                else if (type == 2) status = std::make_shared<ShieldStatus>(10);
                else status = std::make_shared<OverloadStatus>();

                field.GetCellRef(x, y).AddStatus(status);
            }
        }
    }
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

const Cell& Field::GetCell(int x, int y) const {
    return grid_[y][x];
}

Cell& Field::GetCellRef(int x, int y) {
    return grid_[y][x];
}
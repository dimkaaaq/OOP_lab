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
    Field field = Field(30, 20);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> chance(0, 99);

    for (int y = 0; y < field.GetHeight(); ++y) {
        for (int x = 0; x < field.GetWidth(); ++x) {
            int roll = chance(gen);
            if (roll < 15) {
                field.SetObstacle(x, y);
            } else if (roll < 25) {
                field.SetPassability(x, y, 2);
            } else if (roll < 30) {
                field.SetPassability(x, y, 3);
            }
        }
    }

    field.RemoveObstacle(0, 0);
    field.SetPassability(0, 0, 1);
    field.RemoveObstacle(10, 12);
    field.SetPassability(10, 12, 1);
    field.RemoveObstacle(19, 13);
    field.SetPassability(19, 13, 1);
    field.RemoveObstacle(10, 13);
    field.SetPassability(10, 13, 1);

    std::uniform_int_distribution<> type_dist(0, 3);
    for (int y = 0; y < field.GetHeight(); ++y) {
        for (int x = 0; x < field.GetWidth(); ++x) {
            if (!field.CanMoveTo(x, y) || (x == 0 && y == 0)) continue;
            
            int roll = chance(gen);
            int num_statuses = 0;
            
            if (roll < 5) num_statuses = 1;       
            else if (roll < 6) num_statuses = 2;  

            for (int i = 0; i < num_statuses; ++i) {
                int type = type_dist(gen);
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
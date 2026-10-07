#include "Vision.hpp"

Vision::Vision(int width, int height)
 : width_(width), height_(height), visible_(height, std::vector<bool>(width, false)),
    explored_(height, std::vector<bool>(width, false)){}

void Vision::Update(const Field& field, int px, int py, int radius) {
    for (int y = 0; y < height_; ++y){
        for (int x = 0; x < width_; ++x){
            visible_[y][x] = false;
        }
    }

    int r2 = radius * radius;
    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            if (dx * dx + dy * dy > r2) continue;
            int x = px + dx;
            int y = py + dy;
            if (!field.IsValidPosition(x, y)) continue;
            visible_[y][x] = true;
            explored_[y][x] = true;
        }
    }
}

bool Vision::IsVisible(int x, int y) const {
    if (x < 0 || y < 0 || x >= width_ || y >= height_) return false;
    return visible_[y][x];
}

bool Vision::IsExplored(int x, int y) const {
    if (x < 0 || y < 0 || x >= width_ || y >= height_) return false;
    return explored_[y][x];
}
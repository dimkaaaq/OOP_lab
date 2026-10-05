#include "vision.hpp"

Vision::Vision(int width, int height)
 : width_(width), height_(height), visible_(width, std::vector<bool>(height, false)),
    explored_(width, std::vector<bool>(height, false)){}

void Vision::Update(const Field& field, int px, int py, int radius) {
    for (int y = 0; y < height_; ++y){
        for (int x = 0; x < width_; ++x){
            visible_[x][y] = false;
        }
    }

    int r2 = radius * radius;
    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            if (dx * dx + dy * dy > r2) continue;
            int x = px + dx;
            int y = py + dy;
            if (!field.IsValidPosition(x, y)) continue;
            visible_[x][y] = true;
            explored_[x][y] = true;
        }
    }
}

bool Vision::IsVisible(int x, int y) const {
    if (x < 0 || y < 0 || x >= width_ || y >= height_) return false;
    return visible_[x][y];
}

bool Vision::IsExplored(int x, int y) const {
    if (x < 0 || y < 0 || x >= width_ || y >= height_) return false;
    return explored_[x][y];
}
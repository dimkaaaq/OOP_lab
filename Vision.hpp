#ifndef VISION_HPP
#define VISION_HPP

#include <vector>
#include "Field.hpp"

class Vision {
public:
    Vision(int width, int height);
    void Update(const Field& Field, int px, int py, int radius);

    bool IsVisible(int x, int y) const;
    bool IsExplored(int x, int y) const;
private:
    int width_;
    int height_;
    std::vector<std::vector<bool>> visible_;
    std::vector<std::vector<bool>> explored_;
};

#endif
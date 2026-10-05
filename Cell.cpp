#include "Cell.hpp"
#include "Field.hpp"

Cell::Cell(bool passable, int passability)
    : passable_(passable), passability_(passability) {}

const Cell& Field::GetCell(int x, int y) const {
    return grid_[y][x];
}
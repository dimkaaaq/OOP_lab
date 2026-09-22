#include "field.hpp"
#include <iostream>

Cell::Cell(bool passable) : passable(passable){}

Field::Field(int width, int height){
    if (width > MAX_SIZE) m_width = MAX_SIZE;
    else if (width < MIN_SIZE) m_width = MIN_SIZE;
    else m_width = width;

    if (height > MAX_SIZE) m_height = MAX_SIZE;
    else if (height < MIN_SIZE) m_height = MIN_SIZE;
    else m_height = height;

    m_grid.resize(m_height, std::vector<Cell>(m_width)); 
}

bool Field::validate(int x, int y){
    return (x >= 0 && y >= 0 && x < m_width && y < m_height);
}

void Field::set_obstacle(int x, int y){
    if (validate(x, y)) m_grid[y][x].passable = false;
}

void Field::remove_obstacle(int x, int y){
    if (validate(x, y)) m_grid[y][x].passable = true;
}

bool Field::can_move_to(int x, int y){
    if (validate(x, y)){
        return m_grid[y][x].passable;
    } else {
        return false;
    }
}

void Field::print_field(){
    for (int y=m_height - 1; y >= 0; y){
        for (int x=0; x < m_width; x++){
            if (m_grid[y][x].passable){
                std::cout << ". ";
            } else {
                std::cout << "# ";
            }
        }
        std::cout << "\n";
    }
}
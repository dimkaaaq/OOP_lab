#include <iostream>
#include <vector>
#ifndef FIELD
#define FIELD
class Cell{
public:
    bool passable = true;
    int passability;
    Cell() = default;
    Cell(bool passable);
};

class Field{
private:
    int m_width;
    int m_height;
    std::vector<std::vector<Cell>> m_grid;

    static const int MIN_SIZE = 3;
    static const int MAX_SIZE = 100;
public:
    Field(int width, int height);

    void set_obstacle(int x, int y);
    void remove_obstacle(int x, int y);
    bool can_move_to(int x, int y);
    void print_field();
    bool validate_position(int x, int y);
};

#endif
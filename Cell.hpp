#ifndef GAME_CELL_HPP
#define GAME_CELL_HPP

class Cell {
public:
    Cell(bool passable = true, int passability = 1);
    bool IsPassable() const { return passable_; } 
    int GetPassability() const { return passability_; }
    void SetPassable(bool value) { passable_ = value; }
    void SetPassability(int value) { passability_ = value; }
private:
    bool passable_;
    int passability_ = 1;
};

#endif
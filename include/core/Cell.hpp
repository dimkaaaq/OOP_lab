#ifndef GAME_CELL_HPP
#define GAME_CELL_HPP

#include <vector>
#include <memory>
#include "statuses/IStatus.hpp"

class Cell {
public:
    Cell(bool passable = true, int passability = 1);
    
    bool IsPassable() const { return passable_; } 
    int GetPassability() const { return passability_; }
    void SetPassable(bool value) { passable_ = value; }
    void SetPassability(int value) { if (value >= 1) passability_ = value; }

    void AddStatus(std::shared_ptr<IStatus> status);
    const std::vector<std::shared_ptr<IStatus>>& GetStatuses() const;
    void RemoveRandomStatus();

private:
    bool passable_;
    int passability_ = 1;
    std::vector<std::shared_ptr<IStatus>> statuses_;
};

#endif
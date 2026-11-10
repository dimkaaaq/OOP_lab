#include "Cell.hpp"
#include <cstdlib>

Cell::Cell(bool passable, int passability)
    : passable_(passable), passability_(passability) {}

void Cell::AddStatus(std::shared_ptr<IStatus> status) {
    if (status) {
        statuses_.push_back(status);
    }
}

const std::vector<std::shared_ptr<IStatus>>& Cell::GetStatuses() const {
    return statuses_;
}

void Cell::RemoveRandomStatus() {
    if (statuses_.empty()) return;
    
    int random_index = std::rand() % statuses_.size();
    statuses_.erase(statuses_.begin() + random_index);
}
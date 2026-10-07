#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP

#include <vector>

#include "EntityController.hpp"
#include "Field.hpp"
#include "InputController.hpp"
#include "Renderer.hpp"
#include "Robot.hpp"

class GameLoop {
public:
    GameLoop(Field& field,
             Robot& player,
             std::vector<Robot*> enemies,
             Renderer& renderer,
             InputController& input);

    void Start();

private:
    Field& field_;
    Robot& player_;
    std::vector<Robot*> enemies_;
    Renderer& renderer_;
    InputController& input_;
    EntityController entity_controller_;

    int turn_ = 0;
};

#endif
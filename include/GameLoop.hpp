#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP

#include "EntityController.hpp"

class World;
class Renderer;
class InputController;

class GameLoop {
public:
    GameLoop(World& world, Renderer& renderer, InputController& input);

    void Start();

private:
    World& world_;
    Renderer& renderer_;
    InputController& input_;
    EntityController entity_controller_;

    int turn_ = 0;
};

#endif
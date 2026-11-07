#include "GameLoop.hpp"

#include "InputController.hpp"
#include "Renderer.hpp"
#include "Robot.hpp"
#include "World.hpp"

GameLoop::GameLoop(World& world, Renderer& renderer, InputController& input)
    : world_(world),
      renderer_(renderer),
      input_(input),
      entity_controller_(world, input) {}

void GameLoop::Start() {
    entity_controller_.UpdateVision();
    renderer_.ClearScreen();
    renderer_.Render(world_, entity_controller_.GetVision());

    while (!entity_controller_.IsGameOver()) {
        if (entity_controller_.PlayerTurn() == 0) {
            renderer_.ClearScreen();
            renderer_.Render(world_, entity_controller_.GetVision());
            continue;
        }

        entity_controller_.EnemyTurn();
        entity_controller_.RestoreEnergy();
        ++turn_;
        entity_controller_.UpdateVision();

        renderer_.ClearScreen();
        renderer_.Render(world_, entity_controller_.GetVision());
    }

    renderer_.ClearScreen();
    renderer_.Render(world_, entity_controller_.GetVision());
    renderer_.RenderResult(world_.GetPlayer().IsAlive());
}
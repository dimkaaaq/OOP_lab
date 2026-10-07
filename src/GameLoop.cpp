#include "GameLoop.hpp"

GameLoop::GameLoop(Field& field, Robot& player, std::vector<Robot*> enemies,
                   Renderer& renderer, InputController& input)
    : field_(field),
      player_(player),
      enemies_(enemies),
      renderer_(renderer),
      input_(input),
      entity_controller_(field, player, enemies_, input) {}

void GameLoop::Start() {
    entity_controller_.UpdateVision();
    renderer_.ClearScreen();
    renderer_.Render(field_, player_, enemies_,
                     entity_controller_.GetVision());

    while (!entity_controller_.IsGameOver()) {
        if (entity_controller_.PlayerTurn() == 0) {
            renderer_.ClearScreen();
            renderer_.Render(field_, player_, enemies_,
                             entity_controller_.GetVision());
            continue;
        }

        entity_controller_.EnemyTurn();
        entity_controller_.RestoreEnergy();
        ++turn_;
        entity_controller_.UpdateVision();

        renderer_.ClearScreen();
        renderer_.Render(field_, player_, enemies_,
                         entity_controller_.GetVision());
    }

    renderer_.ClearScreen();
    renderer_.Render(field_, player_, enemies_,
                     entity_controller_.GetVision());
    renderer_.RenderResult(player_.IsAlive());
}
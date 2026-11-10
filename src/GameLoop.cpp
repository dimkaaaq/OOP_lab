#include "GameLoop.hpp"

#include "InputController.hpp"
#include "Renderer.hpp"
#include "Robot.hpp"
#include "World.hpp"

#include "abilities/HealAbility.hpp"
#include "abilities/MeleeAbility.hpp"
#include "abilities/RangeAbility.hpp"
#include "abilities/TeleportAbility.hpp"

#include <iostream>

GameLoop::GameLoop(World& world, Renderer& renderer, InputController& input)
    : world_(world),
      renderer_(renderer),
      input_(input),
      entity_controller_(world, input) {}

void GameLoop::Start() {
    entity_controller_.UpdateVision();
    renderer_.ClearScreen();
    renderer_.Render(world_, entity_controller_.GetVision(), current_view_mode_);

    while (!entity_controller_.IsGameOver()) {
        int result = entity_controller_.PlayerTurn();

        if (result == -1) {
            int mode = static_cast<int>(current_view_mode_);
            mode = (mode + 1) % 4;
            current_view_mode_ = static_cast<ViewMode>(mode);
            
            renderer_.ClearScreen();
            renderer_.Render(world_, entity_controller_.GetVision(), current_view_mode_);
            continue;
        }

        if (result == 0) {
            renderer_.ClearScreen();
            renderer_.Render(world_, entity_controller_.GetVision(), current_view_mode_);
            continue;
        }

        if (world_.GetPlayer().GetPendingRankUps() > 0) {
            renderer_.ClearScreen();
            renderer_.Render(world_, entity_controller_.GetVision(), current_view_mode_);
            HandleRankUp();
        }   

        entity_controller_.EnemyTurn();
        entity_controller_.RestoreEnergy();
        ++turn_;
        entity_controller_.UpdateVision();

        renderer_.ClearScreen();
        renderer_.Render(world_, entity_controller_.GetVision(), current_view_mode_);
    }

    renderer_.ClearScreen();
    renderer_.Render(world_, entity_controller_.GetVision(), current_view_mode_);
    renderer_.RenderResult(world_.GetPlayer().IsAlive());
}

void GameLoop::HandleRankUp() {
    Robot& player = world_.GetPlayer();

    while (player.GetPendingRankUps() > 0) {
        std::cout << "\n====| ПОВЫШЕНИЕ РАНГА! |====\n\n";
        std::cout << "0. Получить новую способность\n";

        for (int i = 0; i < player.GetAbilityCount(); ++i) {
            std::cout << i + 1 << ". Улучшить способность: " << player.GetAbilityName(i) << " (Lvl " << player.GetAbilityLevel(i) << ")\n";
        }

        int choice;
        std::cout << "Ваш выбор: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 0) {
            if (player.GetAbilityCount() >= 4) {
                std::cout << "У вас получены все способности. Выберите улучшение\n";
                continue;
            }
            
            std::cout << "Выберите новую: 1 - Лечение, 2 - Ближний удар, 3 - Дальний удар, 4 - Телепортация: ";
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }
            if (choice == 1) player.AddAbility(std::make_shared<HealAbility>());
            else if (choice == 2) player.AddAbility(std::make_shared<MeleeAbility>(world_));
            else if (choice == 3) player.AddAbility(std::make_shared<RangeAbility>(world_));
            else if (choice == 4) player.AddAbility(std::make_shared<TeleportAbility>(world_));
            else {
                std::cout << "Неверный выбор!\n";
                continue;
            }
        } else {
            if (choice > 0 && choice <= player.GetAbilityCount()) {
                player.UpgradeAbility(choice - 1);
                std::cout << "Способность улучшена!\n";
            } else {
                std::cout << "Неверный номер способности!\n";
                continue;
            }
        }

        player.DecreasePendingRankUps();
        renderer_.ClearScreen();
    }
}
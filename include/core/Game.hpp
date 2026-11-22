#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "Field.hpp"
#include "Robot.hpp"
#include "World.hpp"
#include "EntityController.hpp"
#include "Renderer.hpp"
#include "InputController.hpp"

#include "abilities/HealAbility.hpp"
#include "abilities/MeleeAbility.hpp"
#include "abilities/RangeAbility.hpp"
#include "abilities/TeleportAbility.hpp"

#include <iostream>

template <typename LevelGenerator>
class Game {
public:
    Game(LevelGenerator& generator, Renderer& renderer, InputController& input)
        : generator_(generator), renderer_(renderer), input_(input),
        field_(30, 20),
        player_(1, 40, 10, 100, 100, 2),
        world_(field_),
        controller_(world_, input_) {} 
    void Run() {
        NextLevel();

        while (true) {
            renderer_.ClearScreen();
            renderer_.Render(world_, controller_.GetVision(), ViewMode::Standard);

            int result = controller_.PlayerTurn();
            if (result == -1) continue;

            if (world_.GetPlayer().GetPendingRankUps() > 0) {
                HandleRankUp();
            }

            if (result == 1) {
                controller_.EnemyTurn();
                controller_.RestoreEnergy();
                controller_.UpdateVision();
            }

            if (!player_.IsAlive()) {
                renderer_.ClearScreen();
                renderer_.RenderResult(false);
                break;
            }

            if (controller_.IsPlayerWin()) {
                if (generator_.HasNextLevel()) {
                    NextLevel();
                } else {
                    renderer_.ClearScreen();
                    renderer_.RenderResult(true);
                    break;
                }
            }
        }
    }

    void NextLevel() {
        for (Robot* enemy : enemies_) {
            delete enemy;
        }
        enemies_.clear();
        world_.ClearEnemies();

        generator_.GenerateLevel(field_, enemies_);
        field_.RemoveObstacle(0, 0); 
        world_.AddPlayer(player_, 0, 0);
        controller_.UpdateVision();
        
        for (Robot* enemy : enemies_) {
            int spawn_x, spawn_y;
            bool found = false;
            
            for (int tries = 0; tries < 100; ++tries) {
                spawn_x = rand() % field_.GetWidth();
                spawn_y = rand() % field_.GetHeight();
                
                if (field_.CanMoveTo(spawn_x, spawn_y) && world_.GetRobotAt(spawn_x, spawn_y) == nullptr) {
                    found = true;
                    break;
                }
            }
            
            if (found) {
                world_.AddEnemy(*enemy, spawn_x, spawn_y);
            }
        }
        
        player_.RestoreEnergy(player_.GetMaxEnergy());
        player_.ClearStatuses();
        world_.MoveRobot(&player_, 0, 0);
    }

    void HandleRankUp() {
        Robot& player = world_.GetPlayer();

        while (player.GetPendingRankUps() > 0) {
            std::cout << "\n====| ПОВЫШЕНИЕ РАНГА! |====\n\n";
            std::cout << "0. Получить новую способность\n";

            for (int i = 0; i < player.GetAbilityCount(); ++i) {
                std::cout << i + 1 << ". Улучшить: " << player.GetAbilityName(i) << " (Lvl " << player.GetAbilityLevel(i) << ")\n";
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
                    std::cout << "У вас уже есть все способности. Выберите улучшение\n";
                    continue;
                }
                std::cout << "Выберите новую: 1-Heal, 2-Melee, 3-Range, 4-Teleport: ";
                if (!(std::cin >> choice)) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    continue;
                }
                if (choice == 1) player.AddAbility(std::make_shared<HealAbility>());
                else if (choice == 2) player.AddAbility(std::make_shared<MeleeAbility>(world_));
                else if (choice == 3) player.AddAbility(std::make_shared<RangeAbility>(world_));
                else if (choice == 4) player.AddAbility(std::make_shared<TeleportAbility>(world_));
            } else {
                if (choice > 0 && choice <= player.GetAbilityCount()) {
                    player.UpgradeAbility(choice - 1);
                    std::cout << "Способность улучшена!\n";
                }
            }
            player.DecreasePendingRankUps();
        }
    }
private:
    LevelGenerator& generator_;
    Renderer& renderer_;
    InputController& input_;
    Field field_;
    Robot player_;
    std::vector<Robot*> enemies_;
    World world_;
    EntityController controller_;
};

#endif

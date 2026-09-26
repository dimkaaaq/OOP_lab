#include "Renderer.hpp"

#include <iostream>

void Renderer::Render(const Field& field, const Robot& player, const std::vector<Robot*>& enemies) {
    ClearScreen();
    for (int y = field.GetHeight() - 1; y >= 0; y--) {
        for (int x = 0; x < field.GetWidth(); x++) {
            char symbol;
            bool has_enemy  = false;
                for (const Robot* enemy : enemies) {
                    if (enemy->GetX() == x && enemy->GetY() == y && enemy->IsAlive()) {
                        has_enemy = true;
                        break;

                    }
                }
            if (player.GetX() == x && player.GetY() == y) {
                symbol = 'P';
            } else if(has_enemy) {
                symbol = 'E';
            } else if (field.CanMoveTo(x, y)){
                symbol = '.';
            } else {
                symbol = '#';
            }
            std::cout << symbol << ' ';       
        }
        std::cout << '\n';
    }
}

void Renderer::RenderResult(bool player_won) {
    if (player_won) {
        std::cout << "Victory!\n";
    }  else {
        std::cout << "Defeat!\n";
    }
}

void Renderer::ClearScreen() {
    std::cout << "\033[2J\033[H";
}
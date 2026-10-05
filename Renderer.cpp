#include "Renderer.hpp"
#include <iostream>
#include <cstdlib>

void Renderer::Render(const Field& field, const Robot& player, const std::vector<Robot*>& enemies) {
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
            if (player.GetX() == x && player.GetY() == y && player.IsAlive()) {
                symbol = 'P';
            } else if(has_enemy) {
                symbol = 'E';
            } else if (field.CanMoveTo(x, y)){
                int passability = field.GetCellPassability(x, y);
                if (passability == 1) symbol = '.';
                if (passability == 2) symbol = '~';
                if (passability == 3) symbol = '&';
            } else {
                symbol = '#';
            }
            std::cout << symbol << ' ';       
        }
        std::cout << '\n';
    }
    std::cout << '\n' << "PLAYER STATS:" << '\n';
    std::cout << '\n' << "Health " << player.GetHealth() << " HP" << '\n';
    std::cout << '\n' << "Damage "<< player.GetDamage() << " DMG" << '\n';
    std::cout << '\n' << "Rank " << player.GetRank() << " LVL" << '\n';
    std::cout << '\n' << "Experience " << player.GetExp() << " / " << player.GetRequiredExp() << " EXP" << '\n' << '\n';

}

void Renderer::RenderResult(bool player_won) {
    if (player_won) {
        std::cout << "Victory!\n";
    }  else {
        std::cout << "Defeat!\n";
    }
}

void Renderer::ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

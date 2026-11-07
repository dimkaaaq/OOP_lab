#include "Renderer.hpp"

#include <iostream>

#include "Field.hpp"
#include "Robot.hpp"
#include "Vision.hpp"
#include "World.hpp"

char Renderer::CellSymbol(const Field& field, int x, int y) {
    if (!field.CanMoveTo(x, y)) return '#';
    char symbol = '.';
    int passability = field.GetCellPassability(x, y);
    if (passability == 2) symbol = '~';
    else if (passability == 3) symbol = '&';
    return symbol;
}

void Renderer::Render(const World& world, const Vision& vision) {
    const Field& field = world.GetField();
    const Robot& player = world.GetPlayer();
    const std::vector<Robot*>& enemies = world.GetEnemies();

    std::cout << "+";
    for (int x = 0; x < field.GetWidth(); x++) {
        std::cout << "--";
    }
    std::cout << "+\n";

    for (int y = field.GetHeight() - 1; y >= 0; y--) {
        std::cout << "|";
        for (int x = 0; x < field.GetWidth(); x++) {
            char symbol;
            if (!vision.IsExplored(x, y)) {
                symbol = ' ';
            } else if (!vision.IsVisible(x, y)) {
                symbol = CellSymbol(field, x, y);
            } else {
                bool has_enemy = false;
                for (const Robot* enemy : enemies) {
                    if (world.GetX(enemy) == x && world.GetY(enemy) == y && enemy->IsAlive()) {
                        has_enemy = true;
                        break;
                    }
                }

                if (world.GetX(&player) == x && world.GetY(&player) == y && player.IsAlive()) {
                    symbol = 'P';
                } else if (has_enemy) {
                    symbol = 'E';
                } else {
                    symbol = CellSymbol(field, x, y);
                }
            }
            std::cout << symbol << ' ';
        }
        std::cout << "|\n";
    }

    std::cout << "+";
    for (int x = 0; x < field.GetWidth(); x++) {
        std::cout << "--";
    }
    std::cout << "+\n";

    std::cout << '\n' << "PLAYER STATS:" << '\n';
    std::cout << '\n' << "Health " << player.GetHealth() << " HP" << '\n';
    std::cout << '\n' << "Damage " << player.GetDamage() << " DMG" << '\n';
    std::cout << '\n' << "Rank " << player.GetRank() << " LVL" << '\n';
    std::cout << '\n' << "Experience " << player.GetExp() << " / " << player.GetRequiredExp() << " EXP" << '\n' << '\n';
}

void Renderer::RenderResult(bool player_won) {
    if (player_won) {
        std::cout << "Victory!\n";
    } else {
        std::cout << "Defeat!\n";
    }
}

void Renderer::ClearScreen() {
    std::cout << "\033[H";
}
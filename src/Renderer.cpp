#include "Renderer.hpp"

#include <iostream>

#include "Field.hpp"
#include "Robot.hpp"
#include "Vision.hpp"
#include "World.hpp"
#include "Cell.hpp"
#include "statuses/IStatus.hpp"

std::string Renderer::CellSymbol(const Field& field, int x, int y) {
    const Cell& cell = field.GetCell(x, y);
    for (const auto& status : cell.GetStatuses()) {
        //std::string name = status->GetName();
        //if (name == "Shield")   return "S ";
        //if (name == "Burn")     return "! ";
        //if (name == "Slow")     return "% ";
        //if (name == "Overload") return "? ";
        return "? ";
    }

    if (!field.CanMoveTo(x, y)) return "# "; // Стена
    
    int passability = field.GetCellPassability(x, y);
    if (passability == 2) return "~ "; // Песок
    if (passability == 3) return "& "; // Болото
    
    return ". "; // Обычная клетка
}

void Renderer::Render(const World& world, const Vision& vision, ViewMode mode) {
    const Field& field = world.GetField();
    const Robot& player = world.GetPlayer();
    const std::vector<Robot*>& enemies = world.GetEnemies();

    int pad_width = 4;
    std::string pad(pad_width, ' ');

    std::string reset = "\033[0m";
    std::string default_color = "";

    std::cout << "+";
    for (int x = 0; x < field.GetWidth(); x++) std::cout << "--";
    std::cout << "+" << pad << "=== PLAYER STATS ===\n";

    for (int y = field.GetHeight() - 1; y >= 0; y--) {
        std::cout << "|";
        for (int x = 0; x < field.GetWidth(); x++) {
            std::string symbol = "  ";
            bool is_wall = !field.CanMoveTo(x, y);
            bool has_enemy = false;
            bool has_status = !field.GetCell(x, y).GetStatuses().empty();
            if (!vision.IsExplored(x, y)) {
                symbol = "  ";
            } else if (!vision.IsVisible(x, y)) {
                symbol = CellSymbol(field, x, y); 
            } else {
                for (const Robot* enemy : enemies) {
                    if (world.GetX(enemy) == x && world.GetY(enemy) == y && enemy->IsAlive()) {
                        has_enemy = true;
                        break;
                    }
                }

                if (world.GetX(&player) == x && world.GetY(&player) == y && player.IsAlive()) {
                    symbol = "P ";
                } else if (has_enemy) {
                    symbol = "E ";
                } else {
                    symbol = CellSymbol(field, x, y);
                }
            }
            std::string color = default_color;
            if (mode == ViewMode::HighlightEnemies && has_enemy) {
                color = "\033[91m";
            } else if (mode == ViewMode::HighlightObstacles && is_wall && vision.IsExplored(x, y)) {
                color = "\033[34m";
            } else if (mode == ViewMode::HighlightStatuses && has_status && vision.IsExplored(x, y)) {
                color = "\033[35m";
            }
            else if (mode == ViewMode::Standard) {
                if (symbol == "P ") color = "\033[32m"; // Игрок - зеленый
                else if (symbol == "E ") color = "\033[31m"; // Враг - красный
                else if (symbol == "# ") color = "\033[90m"; // Стена - серый
                else if (symbol == "! " || symbol == "S " || symbol == "% " || symbol == "? ") color = "\033[33m"; // Ловушки - желтый
            }
            std::cout << color << symbol << reset;
        }
        std::cout << "|" << pad;

        int row_index = field.GetHeight() - 1 - y;
        
        if (row_index == 0) {
            std::cout << "Health:   " << player.GetHealth() << " / " << player.GetMaxHealth() << " HP";
        } else if (row_index == 1) {
            std::cout << "Damage:   " << player.GetDamage() << " DMG";
        } else if (row_index == 2) {
            std::cout << "Rank:     " << player.GetRank() << " LVL";
        } else if (row_index == 3) {
            std::cout << "Exp:      " << player.GetExp() << " / " << player.GetRequiredExp();
        } else if (row_index == 4) {
            std::cout << "Energy:   " << player.GetEnergy() << " / " << player.GetMaxEnergy();
        } else if (row_index == 5) {
            std::cout << "Statuses: ";
            bool has_status = false;
            if (player.HasStatus("Burn"))     { std::cout << "ГОРЕНИЕ "; has_status = true; }
            if (player.HasStatus("Slow"))     { std::cout << "ЗАМЕДЛЕНИЕ "; has_status = true; }
            if (player.HasStatus("Shield"))   { std::cout << "ЩИТ " << player.GetShieldAmount() << " HP "; has_status = true; }
            if (player.HasStatus("Overload")) { std::cout << "ПЕРЕГРУЗКА "; has_status = true; }
            if (!has_status) std::cout << "None";
        } else if (row_index == 6) {
            std::cout << "Controls: WASD-move, 1-4-abilities";
        } else if (row_index == 7) {
            if (mode == ViewMode::HighlightEnemies) std::cout << "Interface: Подсветка врагов";
            else if (mode == ViewMode::HighlightObstacles) std::cout << "Interface: Подсветка стен";
            else if (mode == ViewMode::HighlightStatuses) std::cout << "Interface: Подсветка Статусов";
            else if (mode == ViewMode::Standard) std::cout << "Interface: Стандартная подсветка";
            else std::cout << "Interface: Монохром";
            
        }

        std::cout << "\n";
    }

    std::cout << "+";
    for (int x = 0; x < field.GetWidth(); x++) std::cout << "--";
    std::cout << "+\n\n";
}

void Renderer::RenderResult(bool player_won) {
    if (player_won) {
        std::cout << "Victory!\n";
    } else {
        std::cout << "Defeat!\n";
    }
}

void Renderer::ClearScreen() {
    std::cout << "\033[2J\033[H";
}
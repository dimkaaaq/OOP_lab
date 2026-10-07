#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include "Field.hpp"
#include "Robot.hpp"
#include "Cell.hpp"
#include "Vision.hpp"

class Renderer {
public:
    void Render(const Field& field, const Robot& player, const std::vector<Robot*>& enemies, const Vision& vision);
    void RenderResult(bool player_won);
    void ClearScreen();
    char CellSymbol(const Field& field, int x, int y);
};

#endif




#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include "Field.hpp"
#include "Robot.hpp"

class Renderer {
public:
    void Render(const Field& field, const Robot& player, const std::vector<Robot*>& enemies);
    void RenderResult(bool player_won);
private:
    void ClearScreen();
};

#endif




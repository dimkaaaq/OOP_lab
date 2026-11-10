#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>
#include <vector>

class World;
class Field;
class Vision;

enum class ViewMode {
    Standard,
    HighlightEnemies,
    HighlightObstacles,
    HighlightStatuses
};

class Renderer {
public:
    void Render(const World& world, const Vision& vision, ViewMode mode);
    void RenderResult(bool player_won);
    void ClearScreen();
    std::string CellSymbol(const Field& field, int x, int y);
};

#endif
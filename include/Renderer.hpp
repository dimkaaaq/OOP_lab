#ifndef RENDERER_HPP
#define RENDERER_HPP

class World;
class Field;
class Vision;

class Renderer {
public:
    void Render(const World& world, const Vision& vision);
    void RenderResult(bool player_won);
    void ClearScreen();
    char CellSymbol(const Field& field, int x, int y);
};

#endif
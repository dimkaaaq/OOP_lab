#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <map>
#include <utility>

class Field;
class Robot;

class World {
public:
    explicit World(Field& field);

    // Вместо конструктора с роботами — методы добавления
    void AddPlayer(Robot& player, int x, int y);
    void AddEnemy(Robot& enemy, int x, int y);

    Field& GetField() const { return field_; }
    Robot& GetPlayer() const { return *player_; }
    const std::vector<Robot*>& GetEnemies() const { return enemies_; }

    // Новые методы для работы с координатами
    int GetX(const Robot* robot) const;
    int GetY(const Robot* robot) const;
    void MoveRobot(Robot* robot, int x, int y);

    Robot* GetRobotAt(int x, int y) const;

private:
    Field& field_;
    Robot* player_ = nullptr;
    std::vector<Robot*> enemies_;
    std::map<const Robot*, std::pair<int, int>> positions_; // Хранилище координат
};

#endif
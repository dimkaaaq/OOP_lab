#include <iostream>
#include <vector>
#include <string>
#include "Robot.hpp"
#include "Field.hpp"
#include <random>

class GameLoop{
public:
    GameLoop(Field& field, Robot& player,
    const std::vector<Robot*>& enemies);

    void start();
private:
    static const int energy_consumption = 10;

    Field& field;
    Robot& player;
    
    std::vector<Robot*> enemies;
    std::vector<Robot*> allRobots;

    int turn = 0;
    bool GameOver = false;

    void playerturn();
    void enemyturn();


}
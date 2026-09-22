#include <string>
#include <vector>
#ifndef ROBOT
#define ROBOT

class Field;

class Robot{
private:

    std::string team;
    int max_health;
    int current_health;
    int current_exp;
    int required_exp = 100;
    int damage;
    int rank = 1;

public:

    int x = 0;
    int y = 0;

    Robot (std::string team, int max_health, int current_health, int current_exp, int required_exp, int damage);

    void expand_max_health(int new_max_health);
    void get_damage(int value);
    void get_heal(int value);
    void get_exp(int value);
    void increase_damage(int value);
    void decrease_damage(int value);        
    void action(Robot& hero, int value);
    void RankUp();

    void move(Field& field, const std::string& direction, std::vector<Robot*>& all_robots);
};

#endif
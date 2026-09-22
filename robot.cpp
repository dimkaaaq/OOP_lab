#include "robot.hpp"
#include "field.hpp"
#include <vector>
#include <iostream>

Robot::Robot(std::string team, int max_health, int current_health, int current_exp, int required_exp, int damage)
    : team(team), max_health(max_health), current_health(current_health), current_exp(current_exp), required_exp(required_exp), damage(damage) {}
void Robot::expand_max_health(int new_max_health){
    max_health = new_max_health;
}
void Robot::get_damage(int value){
    if (value > current_health){
        current_health = 0;
    } else {
        current_health -= value;
    }
}
void Robot::get_heal(int value){
    current_health += value;
}
void Robot::get_exp(int value){
    current_exp += value;
    RankUp();
}
void Robot::increase_damage(int value){
    damage += value;
}
void Robot::decrease_damage(int value){
    if (value > damage){
        damage = 0;
    } else {
        damage -= value;
    }
}        
void Robot::action(Robot& hero, int value){
    if (hero.team == this->team){
        hero.get_heal(value);
    } else {
        hero.get_damage(this->damage);
    }
}
void Robot::RankUp()
{
    if(current_exp >= required_exp){
    rank += 1;
    max_health += 20;
    damage += 5;
    current_exp -= required_exp;
    required_exp *= 1.3;

    }
}
void Robot::move(Field& field, const std::string& direction, std::vector<Robot*>& all_robots){
    int next_x = this->x;
    int next_y = this->y;

    if (direction == "up") next_y++;
    else if (direction == "down") next_y--;
    else if (direction == "right") next_x++;
    else if (direction == "left") next_x--;

    if (!field.can_move_to(next_x, next_y)){
        std::cout << "Робот не может переместиться в (" << next_x << ", "<< next_y<<"): клетка непроходима!\n";
        return;
    }
    for (Robot* other : all_robots){
        if (other == this) continue;
        if (other->x == next_x && other->y == next_y){
            this->action(*other, 10);
            return;
        }
    }

    this->x = next_x;
    this->y = next_y;
}

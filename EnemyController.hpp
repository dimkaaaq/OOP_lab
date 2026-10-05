#include "InputController.hpp"
#include "Robot.hpp"
#include "Field.hpp"


class EnemyStrategy {
public:
    EnemyStrategy(Field& field, Robot& player, std::vector<Robot*> enemies, InputController& input);
    void TryMove(Robot& robot, Commands cmd);
private:
    void EnemyTurn();
    void PlayerTurn();


};
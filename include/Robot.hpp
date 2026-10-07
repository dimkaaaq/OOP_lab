#ifndef ROBOT_HPP
#define ROBOT_HPP

class Robot {
public:
    Robot(int team, int max_health, int damage, int max_energy,
          int required_exp, int x = 0, int y = 0, int speed = 1);

    int GetTeam() const { return team_; }
    int GetDamage() const { return damage_; }
    int GetExp() const { return current_exp_; }
    int GetRequiredExp() const { return required_exp_; }
    int GetEnergy() const { return current_energy_; }
    int GetMaxEnergy() const { return max_energy_; }
    int GetHealth() const { return current_health_; }
    int GetMaxHealth() const { return max_health_; }
    int GetRank() const { return rank_; }
    int GetSpeed() const { return speed_; }
    int GetX() const { return x_; }
    int GetY() const { return y_; }

    bool IsAlive() const { return current_health_ > 0; }

    void TakeDamage(int value);
    void TakeHeal(int value);
    void RestoreEnergy(int value);
    void SpendEnergy(int value);
    void GainExp(int value);

    void IncreaseMaxHealth(int new_max_health);
    void IncreaseDamage(int value);
    void IncreaseSpeed(int value);

    void Interact(Robot& target, int heal_value);
    void MoveTo(int x, int y);

    int  GetVision() const { return vision_; }
    void IncreaseVision(int v) { if (v > 0) vision_ += v; }

private:
    void TryRankUp();

    int team_;
    int x_;
    int y_;
    int max_health_;
    int current_health_;
    int damage_;
    int max_energy_;
    int current_energy_;
    int current_exp_;
    int required_exp_;
    int rank_;
    int speed_ = 1;
    int vision_ = 5;    
};

#endif
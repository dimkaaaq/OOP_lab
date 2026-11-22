#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <vector>
#include <memory>

#include "abilities/IAbility.hpp"
#include "statuses/IStatus.hpp"
#include "items/IItem.hpp"

class Robot {
public:
    Robot(int team, int max_health, int damage, int max_energy,
          int required_exp, int speed = 1);

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

    int GetVision() const { return vision_; }
    void IncreaseVision(int v) { if (v > 0) vision_ += v; }

    void AddAbility(std::shared_ptr<IAbility> ability);
    bool UseAbility(int index, int target_x = -1, int target_y = -1);
    int GetAbilityCount() const { return abilities_.size(); }
    std::string GetAbilityName(int index) const;

    void AddStatus(std::shared_ptr<IStatus> status);
    void RemoveStatus(const std::string& name);
    void ProcessStatusesStart();
    void ProcessStatusesEnd();
    bool HasStatus(const std::string& name) const;
    int GetShieldAmount() const;
    void TakeShieldDamage(int& damage);

    int GetPendingRankUps() const { return pending_rank_ups_; }
    void DecreasePendingRankUps() { if (pending_rank_ups_ > 0) pending_rank_ups_--; }
    void UpgradeAbility(int index);
    int FindAbilityIndex(const std::string& name) const;
    int GetAbilityLevel(int index) const;
    
    void AddItem(std::shared_ptr<IItem> item);
    bool UseItem(int index);
    int GetInventorySize() const;
    std::string GetItemName(int index) const;

    void DecreaseDamage(int value); 
private:

    void TryRankUp();

    int team_;
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

    int pending_rank_ups_ = 0;

    std::vector<std::shared_ptr<IAbility>> abilities_;
    std::vector<std::shared_ptr<IStatus>> statuses_;
    std::vector<std::shared_ptr<IItem>> inventory_;
};

#endif
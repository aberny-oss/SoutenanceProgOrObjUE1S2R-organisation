#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"

class Goblin : public Character
{
public:

    Goblin(const std::string& name, int level, int health, int healthMax, const std::string& team, double expUp, double expGain)
        : Character(name, "Goblin", level, health, healthMax, team, expUp, 0, expGain, 200, 40)
    {
        attacks = { "Simple", "Heavy" }; // toutes les attaques
        heals = { "Soin" }; // toutes les soin
    }

    std::vector<std::string>Display() const override;

    // Attaques
    void PerformAttack(int attackIndex, Character& target) override;
    int GetAttackDamage(size_t index) const override;
    void SimpleAttack(Character& Atktarget);
    void HeavyAttack(Character& Atktarget);
    /*void UltimeAttack(Character& Atktarget);*/

    //Soins
    void PerformHeals(int healsIndex, Character& target) override;
    int GetHealsPV(size_t index) const override;
    void SimpleHeal(Character& Atktarget);

};

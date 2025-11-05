#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"

class Warrior : public Character
{
public:

    Warrior(const std::string& name, int level, int health, const std::string& team)
        : Character(name, "Warrior", level, health, team)
    {
        attacks = { "Simple", "Heavy", "Ultime" }; // toutes les attaques
    }

    std::vector<std::string>Display() const override;

    void PerformAttack(int attackIndex, Character& target) override;

    int GetAttackDamage(size_t index) const;

    void SimpleAttack();

    void HeavyAttack();

    void UltimeAttack();
};


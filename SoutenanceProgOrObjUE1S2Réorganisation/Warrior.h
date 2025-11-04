#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"

class Warrior : public Character
{
public:

    Warrior(const std::string& name, const std::string& team)
        : Character(name, "Warrior", 10, 250, team)
    {
        attacks = { "Simple", "Heavy", "Ultime" }; // toutes les attaques
    }

    std::vector<std::string>Display() const override;
    void SimpleAttack();

    void HeavyAttack();

    void UltimeAttack();
};


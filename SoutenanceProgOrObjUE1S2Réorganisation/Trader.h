#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"

class Trader : public Character
{
public:
    Trader(const std::string& name, const std::string& team, double expUp, double expGain)
        : Character(name, "Trader", 99, 1000, 1000, team, expUp, 0, expGain, 99999, 0)
    {
    }

    // Implémentation de toutes les méthodes virtuelles pures !
    std::vector<std::string>Display() const override;

    int GetAttackDamage(size_t index) const override {
        // Pour Trader, renvoie toujours 0 (le trader n'attaque pas)
        return 0;
    }
    void PerformAttack(int attackIndex, Character& target) override {
        // Pas d'attaque
    }
    int GetHealsPV(size_t index) const override {
        // Le trader ne soigne pas
        return 0;
    }
    void PerformHeals(int healsIndex, Character& target) override {
        // Pas de soin
    }

    // Spécifique Trader
    void DisplayTrader() const;
    void PerformTrade(int tradeIndex, Character& target, int gold);
};

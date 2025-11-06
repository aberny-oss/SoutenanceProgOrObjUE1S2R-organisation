#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>


class Character {
protected:
    std::string name;
    std::string type;
    int level;
    int health;
    std::vector<std::string> attacks;
    std::vector<std::string> heals;
    std::string team;
    int exp;
    int expGain;

public:
    Character(const std::string& name, const std::string& type, int level, int health, const std::string& team, int exp, int expGain)
        : name(name), type(type), level(level), health(health), team(team), exp(exp), expGain(expGain) {
    }

    virtual std::vector<std::string> Display() const = 0;  // Retourne l'ASCII art ligne par ligne

    std::string GetName() const;
    std::string GetTeam() const;
    int GetHealth() const;

    // EXP
    int GetExp() const;
    int GetExpGain() const;

    // Attaques
    int GetNbAttacks() const;
    virtual int GetAttackDamage(size_t index) const = 0;
    void DisplayAttacks() const;
    void AttackByIndex(int index);
    virtual void PerformAttack(int attackIndex, Character& target) = 0;

    // Soins
    int GetNbHeals() const;
    virtual int GetHealsPV(size_t index) const = 0;
    void DisplayHeals() const;
    void HealsByIndex(int index);
    virtual void PerformHeals(int healsIndex, Character& target) = 0;

    void TakeDamage(int dmg);
    void TakeHeal(int amount);

    void Experience(int experience);
};

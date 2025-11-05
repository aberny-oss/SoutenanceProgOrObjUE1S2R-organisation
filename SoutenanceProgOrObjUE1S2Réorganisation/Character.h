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
    std::string team;

public:
    Character(const std::string& name, const std::string& type, int level, int health, const std::string& team)
        : name(name), type(type), level(level), health(health), team(team) {
    }

    virtual std::vector<std::string> Display() const = 0;  // Retourne l'ASCII art ligne par ligne

    std::string GetName() const;
    std::string GetTeam() const;
    int GetHealth() const;

    // Getter moderne
    int GetNbAttacks() const;

    virtual int GetAttackDamage(size_t index) const = 0;
    void DisplayAttacks() const;
    void AttackByIndex(int index);

    virtual void PerformAttack(int attackIndex, Character& target) = 0;

    void TakeDamage(int dmg);
    void Heal(int amount);
};

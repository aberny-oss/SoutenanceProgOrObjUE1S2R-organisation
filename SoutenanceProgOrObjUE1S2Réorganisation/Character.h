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

    // Getter moderne
    int GetNbAttacks() const;
    void DisplayAttacks() const;
    /*virtual void UseAttackByIndex(int index);*/
    void AttackByIndex(int index);

    void TakeDamage(int dmg);
    void Heal(int amount);
};

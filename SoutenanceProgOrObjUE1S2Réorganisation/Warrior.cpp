#include "Warrior.h"

std::vector<std::string> Warrior::Display() const {
    std::vector<std::string> lines;

    // Préparer le nom (max 12 caractères)
    std::string displayName = name.substr(0, 12);
    displayName += std::string(12 - displayName.length(), ' ');

    // Préparer les stats
    std::string stats = "Lv:" + std::to_string(level) + " HP:" + std::to_string(health);
    stats = stats.substr(0, 12);
    stats += std::string(12 - stats.length(), ' ');

    lines.push_back("+----------------+");
    lines.push_back("|  " + displayName + "  |");
    lines.push_back("|  " + stats + "  |");
    lines.push_back(R"(|                |)");
    lines.push_back(R"(|      .-.       |)");
    lines.push_back(R"(|    __|=|__     |)");
    lines.push_back(R"(|   (_/`-`\_)    |)");
    lines.push_back(R"(|   ||\___/||    |)");
    lines.push_back(R"(|   <>/   \<>    |)");
    lines.push_back(R"(|    \|_._|/     |)");
    lines.push_back(R"(|     <_I_>      |)");
    lines.push_back(R"(|      |||       |)");
    lines.push_back(R"(|     /_|_\      |)");
    lines.push_back(R"(+----------------+)");

    return lines;
}

void Warrior::PerformAttack(int attackIndex, Character& target)
{
    int dmg = 0;
    if (attackIndex == 0) dmg = 10;
    else if (attackIndex == 1) dmg = 30;
    else if (attackIndex == 2) dmg = 100;
    // logique d’effet
    std::cout << name << " utilise " << attacks[attackIndex] << " sur " << target.GetName() << std::endl;
    // ... applique les dégâts, affiche etc.
	target.TakeDamage(dmg);
}

int Warrior::GetAttackDamage(size_t index) const
{
    switch (index)
    {
    case 0:
    {
        int dmg = 5 + (level * 2);
        return dmg; // SimpleAttack
    }
    case 1:
    {
        int dmg = 10 + (level * 3);
        return dmg;
    }
    case 2:
    {
        int dmg = 15 + (level * 5);
        return dmg;
    }
    }
}

void Warrior::SimpleAttack()
{
    int atkdmg = GetAttackDamage(0);
    std::cout << name << " attaque avec son epee ! \n";
}

void Warrior::HeavyAttack()
{
    int atkdmg = GetAttackDamage(1);
    std::cout << name << " fait une attaque lourde ! \n";
}

void Warrior::UltimeAttack()
{
    int atkdmg = GetAttackDamage(2);
    std::cout << name << " utilise sa rage ultime ! \n";
}
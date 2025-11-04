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

void Warrior::SimpleAttack()
{
    int atkdmg = 10;
    std::cout << name << " attaque avec son epee ! \n";
}

void Warrior::HeavyAttack()
{
    int atkdmg = 15;
    std::cout << name << " fait une attaque lourde ! \n";
}

void Warrior::UltimeAttack()
{
    int atkdmg = 20;
    std::cout << name << " utilise sa rage ultime ! \n";
}
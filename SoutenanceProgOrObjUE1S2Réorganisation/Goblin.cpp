#include "Goblin.h"

std::vector<std::string> Goblin::Display() const {
    std::vector<std::string> lines;

    // Préparer le nom (max 12 caractères)
    std::string displayName = name.substr(0, 12);
    displayName += std::string(12 - displayName.length(), ' ');

    // Préparer les stats (max 12 caractères)
    std::string stats = "Lv:" + std::to_string(level) + " HP:" + std::to_string(health) + "/" + std::to_string(healthMax);
    stats = stats.substr(0, 16);
    stats += std::string(16 - stats.length(), ' ');

    // Préparer les exp
    std::string exps = "Exp:" + std::to_string(exp) + "/" + std::to_string(static_cast<int>(expUp));
    exps = exps.substr(0, 10);
    exps += std::string(10 - exps.length(), ' ');

    // Cadre et informations
    lines.push_back("+----------------+");
    lines.push_back("|  " + displayName + "  |");
    lines.push_back("|" + stats + "|");
    lines.push_back("|   " + exps + "   |");
    lines.push_back(R"(|    _____       |)");
    lines.push_back(R"(|.-,;='';_),-.   |)");
    lines.push_back(R"(| \_\(),()/_/    |)");
    lines.push_back(R"(|   (,___,)      |)");
    lines.push_back(R"(|  ,-/`~`\-,___  |)");
    lines.push_back(R"(| / /).:.('--._) |)");
    lines.push_back(R"(|{_[ (_,_)       |)");
    lines.push_back(R"(|    | Y |       |)");
    lines.push_back(R"(|   /  |  \      |)");
    lines.push_back(R"(|   """ """      |)");
    lines.push_back("+----------------+");

    return lines;
}

void Goblin::PerformAttack(int attackIndex, Character& target)
{
    if (attackIndex == 0)
    {
        SimpleAttack(target);
    }
    else if (attackIndex == 1)
    {
        HeavyAttack(target);
    }
    //else if (attackIndex == 2)
    //{
        //UltimeAttack(target);
    //}
}

int Goblin::GetAttackDamage(size_t index) const
{
    int dmg = 0;
    switch (index)
    {
    case 0:
    {
        dmg = 3 + (level * 2);
        return dmg; // SimpleAttack
    }
    case 1:
    {
        dmg = 8 + (level * 3);
        return dmg;
    }
    //case 2:
    //{
        //dmg = 12 + (level * 5);
        //return dmg;
    //}
    }
}

void Goblin::SimpleAttack(Character& Atktarget)
{
    int atkdmg = GetAttackDamage(0);
    // logique d’effet
    std::cout << name << " attaque avec sa dague ! \n" << " sur " << Atktarget.GetName() << std::endl;
    // ... applique les dégâts, affiche etc.
    Atktarget.TakeDamage(atkdmg);
}

void Goblin::HeavyAttack(Character& Atktarget)
{
    int atkdmg = GetAttackDamage(1);
    // logique d’effet
    std::cout << name << " fait un combo rapide ! \n" << " sur " << Atktarget.GetName() << std::endl;
    // ... applique les dégâts, affiche etc.
    Atktarget.TakeDamage(atkdmg);
}

//void Goblin::UltimeAttack(Character& Atktarget)
//{
//    int atkdmg = GetAttackDamage(2);
//    // logique d’effet
//    std::cout << name << " utilise sa technique ultime ! \n" << " sur " << Atktarget.GetName() << std::endl;
//    // ... applique les dégâts, affiche etc.
//    Atktarget.TakeDamage(atkdmg);
//}

//Soins

void Goblin::PerformHeals(int healsIndex, Character& target)
{
    if (healsIndex == 0)
    {
        SimpleHeal(target);
    }
    //else if (healsIndex == 1)
    //{
        //HeavyAttack(target);
    //}
    //else if (healsIndex == 2)
    //{
        //UltimeAttack(target);
    //}
}
int Goblin::GetHealsPV(size_t index) const
{
    int amount = 0;
    switch (index)
    {
    case 0:
    {
        amount = 5 + (level * 2);
        return amount; // SimpleAttack
    }
    case 1:
    {
        amount = 10 + (level * 3);
        return amount;
    }
    case 2:
    {
        amount = 15 + (level * 5);
        return amount;
    }
    }
}

void Goblin::SimpleHeal(Character& Healtarget)
{
    int healamout = GetHealsPV(0);
    // logique d’effet
    std::cout << name << " Soigne ! \n" << " sur " << Healtarget.GetName() << std::endl;
    // ... applique les soins, affiche etc.
    Healtarget.TakeHeal(healamout);
}
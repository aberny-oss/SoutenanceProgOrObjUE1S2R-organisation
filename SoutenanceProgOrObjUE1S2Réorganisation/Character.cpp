#include "Character.h"

std::string Character::GetName() const
{
    return name;
}

std::string Character::GetTeam() const
{
    return team;
}

int Character::GetHealth() const
{
    return health;
}

int Character::GetExp() const
{
    return exp;
}
int Character::GetExpGain() const
{
    return expGain;
}

// Nombre d'attaques disponibles
int Character::GetNbAttacks() const
{
    return static_cast<int>(attacks.size());
}

// Affiche la liste des attaques
void Character::DisplayAttacks() const
{
    if (attacks.empty())
    {
        std::cout << name << " n’a aucune attaque.\n";
        return;
    }
    std::cout << name << " peut utiliser les attaques suivantes :\n";
    std::cout << "Index | Attaque     | Degats\n";
    std::cout << "-------------------------------\n";
    for (size_t i = 0; i < attacks.size(); ++i)
    {
        std::cout << "  " << (i + 1) << "   | "
            << attacks[i] << std::string(12 - attacks[i].size(), ' ')
            << "|   " << GetAttackDamage(i)
            << "\n";
    }
    std::cout << std::endl;
}

void Character::AttackByIndex(int index)
{
    std::vector<std::string> attacks;
    int intInput;
    std::cout << "Sur qui ? (Entre son numero) \n" << std::endl;
    std::cin >> intInput;
    int position = 0;
    for (std::string a : attacks)
    {
        if (intInput < 1 || intInput > attacks.size())
        {
            std::cout << "Nombre trop grand ou trop petit !" << std::endl;
        }
        if (position == intInput)
        {
            std::cout << position;
            break;
        }
        position += 1;
    }
}

int Character::GetNbHeals() const
{
    return static_cast<int>(heals.size());
}

void Character::DisplayHeals() const
{
    if (heals.empty())
    {
        std::cout << name << " n’a aucun soin.\n";
        return;
    }
    std::cout << name << " peut utiliser les soins suivantes :\n";
    std::cout << "Index | Soins     | Pv\n";
    std::cout << "-------------------------------\n";
    for (size_t i = 0; i < heals.size(); ++i)
    {
        std::cout << "  " << (i + 1) << "   | "
            << heals[i] << std::string(12 - heals[i].size(), ' ')
            << "|   " << GetHealsPV(i)
            << "\n";
    }
    std::cout << std::endl;
}

void Character::HealsByIndex(int index)
{
    std::vector<std::string> heals;
    int intInput;
    std::cout << "Sur qui ? (Entre son numero) \n" << std::endl;
    std::cin >> intInput;
    int position = 0;
    for (std::string a : heals)
    {
        if (intInput < 1 || intInput > heals.size())
        {
            std::cout << "Nombre trop grand ou trop petit !" << std::endl;
        }
        if (position == intInput)
        {
            std::cout << position;
            break;
        }
        position += 1;
    }
}

void Character::TakeDamage(int dmg)
{
    // On applique les dégâts
    health -= dmg;

    // On ne veut jamais de PV négatifs
    if (health < 0)
    {
        health = 0;
    }

    // Message à l’écran
    std::cout << name << " subit " << dmg << " degats. PV restants : " << health << "\n";
}

void Character::TakeHeal(int amount)
{
    // On applique les soins
    health += amount;
	// On ne peut pas dépasser les PV max
	if (health > healthMax) 
    {
        health = healthMax;
    }

    // Message à l’écran
    std::cout << name << " se soigne de " << amount << " PV. PV actuels : " << health << "\n";
}

double calculerExpPourNiveau(int level)
{
    return 100 * pow(1.1, level - 1);
}


void Character::Experience(double experience)
{
    expUp = calculerExpPourNiveau(level);
    exp += experience;
    // Message à l’écran
    std::cout << name << " Gagne de l'exp " << experience << "Exp" << exp << "\n";
    if (exp >= expUp)
    {
        level += 1;
        exp = 0;
    }
}

int Character::GetGold() const
{
    return gold;
}

int Character::GetGoldGain() const
{
    return goldGain;
}

void Character::AddGold(int amount)
{
    gold += amount;
    // Message à l’écran
    std::cout << name << " Gagne de l'or " << amount << " pièces." << std::endl;
}

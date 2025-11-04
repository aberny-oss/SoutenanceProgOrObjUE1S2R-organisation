#include "Character.h"

std::string Character::GetName() const
{
    return name;
}

std::string Character::GetTeam() const
{
    return team;
}


// Nombre d'attaques disponibles
int Character::GetNbAttacks() const {
    return static_cast<int>(attacks.size());
}

// Affiche la liste des attaques
void Character::DisplayAttacks() const {
    if (attacks.empty()) {
        std::cout << name << " n’a aucune attaque.\n";
        return;
    }

    std::cout << name << " peut utiliser : ";
    for (size_t i = 0; i < attacks.size(); ++i) {
        std::cout << (i + 1) << ": " << attacks[i];
        if (i != attacks.size() - 1)
            std::cout << " | ";
    }
    std::cout << "\n";
}

//// Utilise une attaque selon son index
//void Character::UseAttackByIndex(int index) {
//    switch (index) {
//    case 1: SimpleAttack(); break;
//    case 2: HeavyAttack(); break;
//    case 3: UltimeAttack(); break;
//    default: std::cout << "Attaque invalide !\n"; break;
//    }
//}

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

void Character::TakeDamage(int dmg) {
    // On applique les dégâts
    health -= dmg;

    // On ne veut jamais de PV négatifs
    if (health < 0) health = 0;

    // Message à l’écran
    std::cout << name << " subit " << dmg << " dégâts. PV restants : " << health << "\n";
}

void Character::Heal(int amount) {
    // On applique les soins
    health += amount;

    // Message à l’écran
    std::cout << name << " se soigne de " << amount << " PV. PV actuels : " << health << "\n";
}


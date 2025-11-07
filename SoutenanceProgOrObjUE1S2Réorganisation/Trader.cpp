#include "Trader.h"

std::vector<std::string>Trader::Display() const
{
    std::vector<std::string> lines;

    // Préparer le nom (max 8 caractères)
    std::string displayName = name.substr(0, 8);
    displayName += std::string(8 - displayName.length(), ' ');

    lines.push_back("+--------------------------+");
    lines.push_back("|          " + displayName + "        |");
    lines.push_back("+--------------------------+");
    lines.push_back(R"(|      ////^\\\\           |)");
    lines.push_back(R"(|      | ^   ^ |           |)");
    lines.push_back(R"(|     @ (o) (o) @          |)");
    lines.push_back(R"(|      |   <   |           |)");
    lines.push_back(R"(|      |  ___  |           |)");
    lines.push_back(R"(|       \_____/            |)");
    lines.push_back(R"(|     ____|  |____         |)");
    lines.push_back(R"(|    /    \__/    \        |)");
    lines.push_back(R"(|   /              \       |)");
    lines.push_back(R"(|  /\_/|        |\_/\      |)");
    lines.push_back(R"(| / /  |        |  \ \     |)");
    lines.push_back(R"(|( <   |        |   > )    |)");
    lines.push_back(R"(| \ \  |        |  / /     |)");
    lines.push_back(R"(|  \ \ |________| / /      |)");
    lines.push_back("+--------------------------+");

    return lines;
}

// Trades
void Trader::DisplayTrader() const
{
    std::cout << "Que souhaitez-vous acheter ?" << std::endl;
    std::cout << "1. Simple Potion (50 pièces d'or)" << std::endl;
    std::cout << "2. Moyenne Potion (75 pièces d'or)" << std::endl;
    std::cout << "3. Grande Potion (100 pièces d'or)" << std::endl;
    std::cout << "4. Quitter le magasin" << std::endl;
}

void Trader::PerformTrade(int tradeIndex, Character& target, int gold)
{
    if (tradeIndex == 0)
    {
        if (gold >= 50)
        {
            std::cout << name << " Vous vend une Simple potion de soin ! \n" << std::endl;
            target.TakeHeal(50); // Soigne 50 PV
        }
        else
        {
            std::cout << "Pas assez d'or pour acheter cette potion." << std::endl;
        }
    }
    else if (tradeIndex == 1)
    {
        if (gold >= 75)
        {
            std::cout << name << " Vous vend une Moyenne potion de soin ! \n" << std::endl;
            target.TakeHeal(75); // Soigne 75 PV
        }
        else
        {
            std::cout << "Pas assez d'or pour acheter cette potion." << std::endl;
        }
    }
    else if (tradeIndex == 2)
    {
        if (gold >= 100)
        {
            std::cout << name << " Vous vend une Grande potion de soin ! \n" << std::endl;
            target.TakeHeal(100); // Soigne 100 PV
        }
        else
        {
            std::cout << "Pas assez d'or pour acheter cette potion." << std::endl;
        }
    }
}

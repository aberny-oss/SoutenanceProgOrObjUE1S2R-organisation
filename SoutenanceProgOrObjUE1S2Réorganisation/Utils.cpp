#include "Utils.h"

std::string Utils::AskStr(const std::string& msg, const std::vector<std::string>& validChoices)
{
    std::string choice;
    bool valid = false;

    do
    {
        std::cout << msg << " (";
        for (size_t i = 0; i < validChoices.size(); ++i)
        {
            std::cout << validChoices[i];
            if (i < validChoices.size() - 1)
                std::cout << " / ";
        }
        std::cout << ") : ";

        std::cin >> choice;
        valid = false;

        // Vérification sans algorithm
        for (size_t i = 0; i < validChoices.size(); ++i)
        {
            if (choice == validChoices[i])
            {
                valid = true;
                break;
            }
        }
        if (!valid)
        {
            std::cout << "Commande incorrecte ! Réessaie.\n";
        }

    } while (!valid);

    return choice;
}

int Utils::AskInt(const std::string& msg, int min, int max)
{
    int choice;
    do
    {
        std::cout << msg << std::endl;
        std::cin >> choice;

        if (choice < min || choice > max)
        {
            std::cout << "Commande Incorrecte! " << std::endl;
        }

    } while (choice < min || choice > max);

    return choice;
}

int Utils::getTerminalWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns = 80; // valeur par défaut
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return columns;
}

int Utils::getTerminalHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int rows = 25; // valeur par défaut
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return rows;
}

// Méthode statique d'initialisation du seed
void Utils::InitRandom() {
    srand(static_cast<unsigned>(time(0)));
}

// Méthode statique pour générer un nombre aléatoire
int Utils::GenerateRandomNumber(int min, int max) {
    return min + rand() % (max + 1 - min);
}

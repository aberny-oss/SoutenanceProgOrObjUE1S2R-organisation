#include "ASCIIART.h"

void ASCIIART::SetInputValue(const char& value)
{
    inputValue = value;
}

void ASCIIART::ArtConsoleMenu(int action)
{
    char displayZone = inputValue;
    switch (action) {
    case 0:
        system("cls");
        std::cout << R"(
    __________________________
   |OFFo oON                  |
   | .----------------------. |
   | |  .----------------.  | |
   | |  |    SYSTEME     |  | |
   | |))|    AB.inc      |  | |
   | |  |                |  | |
   | |  |   C. JOUER     |  | |
   | |  |   Q. QUITTER   |  | |
   | |  |                |  | |
   | |  '----------------'  | |
   | |__GAME BOY____________/ |
   |          ________        |
   |    .    (Nintendo)       |
   |  _| |_   """"""""   .-.  |
   |-[_   _]-       .-. (   ) |
   |   |_|         (   ) '-'  |
   |    '           '-'   A   |
   |                 B        |
   |          ___   ___       |
   |         (___) (___)  ,., |
   |        select start ;:;: |
   |                    ,;:;' /
   |                   ,:;:'.'
   '-----------------------`
)" << std::endl;
        break;
    case 1:
        system("cls");
        std::cout << R"(
    __________________________
   |OFFo oON                  |
   | .----------------------. |
   | |  .----------------.  | |
   | |  |    SYSTEME     |  | |
   | |))|    AB.inc      |  | |
   | |  |                |  | |
)";
        std::cout << "   | |  |       " << displayZone << "        |  | |\n";
        std::cout << "   | |  |    Erreur !    |  | |\n";
        std::cout << "   | |  |                |  | |\n";
        std::cout << "   | |  '----------------'  | |";
        std::cout << R"(
   | |__GAME BOY____________/ |
   |          ________        |
   |    .    (Nintendo)       |
   |  _| |_   """"""""   .-.  |
   |-[_   _]-       .-. (   ) |
   |   |_|         (   ) '-'  |
   |    '           '-'   A   |
   |                 B        |
   |          ___   ___       |
   |         (___) (___)  ,., |
   |        select start ;:;: |
   |                    ,;:;' /
   |                   ,:;:'.'
   '-----------------------`
)" << std::endl;
        break;
    case 2:
        system("cls");
        std::cout << R"(
    __________________________
   |OFFo oON                  |
   | .----------------------. |
   | |  .----------------.  | |
   | |  |    SYSTEME     |  | |
   | |))|    AB.inc      |  | |
   | |  |                |  | |
)";
        std::cout << "   | |  |       " << displayZone << "        |  | |\n";
        std::cout << "   | |  |   A Bientot !  |  | |\n";
        std::cout << "   | |  |                |  | |\n";
        std::cout << "   | |  '----------------'  | |";
        std::cout << R"(
   | |__GAME BOY____________/ |
   |          ________        |
   |    .    (Nintendo)       |
   |  _| |_   """"""""   .-.  |
   |-[_   _]-       .-. (   ) |
   |   |_|         (   ) '-'  |
   |    '           '-'   A   |
   |                 B        |
   |          ___   ___       |
   |         (___) (___)  ,., |
   |        select start ;:;: |
   |                    ,;:;' /
   |                   ,:;:'.'
   '-----------------------`
)" << std::endl;
        break;
    }
}

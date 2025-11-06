#include "CharacterManager.h"

void CharacterManager::AddAlly(std::unique_ptr<Character> character) {
    allies.push_back(std::move(character));
}

void CharacterManager::AddEnemy(std::unique_ptr<Character> character) {
    enemies.push_back(std::move(character));
}

// Nombre d'objets
size_t CharacterManager::SizeAlly() const
{
    return allies.size();
}

// Nombre d'objets
size_t CharacterManager::SizeEnemy() const
{
    return enemies.size();
}

Character* CharacterManager::GetAlly(int index) {
    if (index >= 0 && index < static_cast<int>(allies.size())) {
        return allies[index].get();
    }
    return nullptr;
}

Character* CharacterManager::GetEnemy(int index) {
    if (index >= 0 && index < static_cast<int>(enemies.size())) {
        return enemies[index].get();
    }
    return nullptr;
}

std::vector<Character*> CharacterManager::GetAllies() const {
    std::vector<Character*> result;
    for (const auto& ptr : allies) {
        if (ptr) result.push_back(ptr.get());
    }
    return result;
}

std::vector<Character*> CharacterManager::GetEnemies() const {
    std::vector<Character*> result;
    for (const auto& ptr : enemies) {
        if (ptr) result.push_back(ptr.get());
    }
    return result;
}

// On suppose que table2D, objects, etc. sont des membres de la classe qui gère les personnages
void CharacterManager::BuildTeamTable2D(size_t rows, size_t cols)
{
    tableRows = rows;
    tableCols = cols;
    table2D.clear();
    table2D.resize(rows, std::vector<Character*>(cols, nullptr));

    size_t r = 0, c = 0;

    // Placer d'abord les objets prioritaires
    for (auto& obj : allies) {
        if (!obj)
        {
            continue;
        }
        table2D[r][c] = obj.get(); // obj = std::unique_ptr<Character>
        ++c;
        if (c >= cols)
        {
            c = 0; ++r;
        }
        if (r >= rows)
        {
            return; // tableau plein
        }
       
    }
}

void CharacterManager::BuildEnemyTable2D(size_t rows, size_t cols)
{
    tableRows = rows;
    tableCols = cols;
    table2D.clear();
    table2D.resize(rows, std::vector<Character*>(cols, nullptr));

    size_t r = 0, c = 0;

    // Placer d'abord les objets prioritaires
    for (auto& obj : enemies) {
        if (!obj)
        {
            continue;
        }
        table2D[r][c] = obj.get(); // obj = std::unique_ptr<Character>
        ++c;
        if (c >= cols)
        {
            c = 0; ++r;
        }
        if (r >= rows)
        {
            return; // tableau plein
        }

    }
}

void CharacterManager::BuildPriorityTable2D(size_t cols)
{
    tableRows = 2; // 1 ligne pour ennemis, 1 pour alliés
    tableCols = cols;
    table2D.clear();
    table2D.resize(tableRows, std::vector<Character*>(cols, nullptr));

    // Positionne les ennemis sur la première ligne
    size_t enemyIndex = 0;
    for (size_t j = 0; j < cols; ++j) {
        if (enemyIndex < enemies.size()) {
            table2D[0][j] = enemies[enemyIndex].get();
            enemyIndex++;
        }
    }

    // Positionne les alliés sur la deuxième ligne
    size_t allyIndex = 0;
    for (size_t j = 0; j < cols; ++j) {
        if (allyIndex < allies.size()) {
            table2D[1][j] = allies[allyIndex].get();
            allyIndex++;
        }
    }
}



void CharacterManager::DisplayTable2D() const
{
    int term_width = Utils::getTerminalWidth();
    for (size_t i = 0; i < tableRows; ++i) {
        // 1. Récupère la matrice ASCII de chaque colonne pour la rangée i
        std::vector<std::vector<std::string>> allASCII;
        int maxLines = 0;
        for (size_t j = 0; j < tableCols; ++j)
        {
            if (table2D[i][j])
            {
                allASCII.push_back(table2D[i][j]->Display());
            }
            else
            {
                // Ajuste ici la largeur d’une case vide si nécessaire !
                std::vector<std::string> emptyBox = { "" };
                allASCII.push_back(emptyBox);
            }
            if (allASCII.back().size() > maxLines)
            {
                maxLines = allASCII.back().size();
            }
        }
        // 2. Affiche la rangée bloc par bloc, ligne après ligne
        for (int line = 0; line < maxLines; ++line) {
            std::string line_content;
            for (size_t j = 0; j < tableCols; ++j) {
                // Si le bloc de la colonne a cette ligne, sinon ligne vide de taille équivalente
                if (line < allASCII[j].size())
                {
                    line_content += allASCII[j][line];
                }
                else
                {
                    line_content += std::string(allASCII[j][0].size(), ' ');
                }
            }
            // 3. Calcul du padding global pour centrer la LIGNE ENTIÈRE
            int padding = (term_width - static_cast<int>(line_content.size())) / 2;
            {
                if (padding > 0) std::cout << std::string(padding, ' ');
            }
            std::cout << line_content << "\n";
        }
        // Optionnel : saut entre rangées/équipes
        std::cout << "\n";
    }
}

void CharacterManager::Attack()
{
    // Sélection du personnage actif
#undef max
    size_t maxColsCount = std::max(GetAllyCount(), GetEnemyCount());
    if (maxColsCount == 0)
    {
        maxColsCount = 1; // Pour ne jamais avoir 0 colonnes
    }
    std::vector<Character*> alliesList = GetAllies();
    if (alliesList.empty()) return;
    int idx = utils.AskInt("Choisissez un allie a jouer (1, 2, 3...) : ", 1, alliesList.size());
    Character* active = alliesList[idx - 1];

    // Affichage et sélection de l’attaque
    system("cls");
    active->Display();
    active->DisplayAttacks();
    int attackIndex = utils.AskInt("Choisissez une attaque : ", 1, active->GetNbAttacks());

    // Sélection de la cible parmi les ennemis
    system("cls");
    BuildPriorityTable2D(maxColsCount);
    DisplayTable2D();
    std::vector<Character*> enemiesList = GetEnemies();
    if (enemiesList.empty()) return;
    int targetIndex = utils.AskInt("Choisissez la cible (1, 2, 3...) : ", 1, enemiesList.size());
    Character* target = enemiesList[targetIndex - 1];

    system("cls");
    // Le personnage effectue l’attaque sur la cible
    active->PerformAttack(attackIndex - 1, *target);
    GainExp(active);
    RemoveDeadCharacters();

}

void CharacterManager::Heal()
{
    // Sélection du personnage actif
#undef max
    size_t maxColsCount = std::max(GetAllyCount(), GetEnemyCount());
    if (maxColsCount == 0)
    {
        maxColsCount = 1; // Pour ne jamais avoir 0 colonnes
    }
    BuildPriorityTable2D(maxColsCount);
    DisplayTable2D();
    std::vector<Character*> alliesList = GetAllies();
    if (alliesList.empty()) return;
    int idx = utils.AskInt("Choisissez un allie a jouer (1, 2, 3...) : ", 1, alliesList.size());
    Character* active = alliesList[idx - 1];

    // Affichage et sélection du soin
    system("cls");
    active->Display();
    active->DisplayHeals();
    int healIndex = utils.AskInt("Choisissez un soin : ", 1, active->GetNbHeals());

    // Sélection de la cible parmi les ennemis
    system("cls");
    BuildPriorityTable2D(maxColsCount);
    DisplayTable2D();
    std::vector<Character*> targetsList = GetAllies();
    int targetIndex = utils.AskInt("Choisissez la cible (1, 2, 3...) : ", 1, targetsList.size());
    Character* target = targetsList[targetIndex - 1];

    system("cls");
    // Le personnage effectue l’attaque sur la cible
    active->PerformHeals(healIndex - 1, *target);

}

int CharacterManager::GetAllyCount() const {
    return static_cast<int>(allies.size());
}

int CharacterManager::GetEnemyCount() const {
    return static_cast<int>(enemies.size());
}

void CharacterManager::RemoveDeadCharacters()
{
    // Pour les alliés
    allies.erase(
        std::remove_if(allies.begin(), allies.end(),
            [](const std::unique_ptr<Character>& c) {
                return c && c->GetHealth() <= 0 && c->GetTeam() == "Player";
            }),
        allies.end());

    // Pour les ennemis
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Character>& c) {
                return c && c->GetHealth() <= 0 && c->GetTeam() == "Ennemy";
            }),
        enemies.end());
}

bool CharacterManager::AreAllPlayersDead() const
{
    for (const auto& ally : allies) {
        if (ally && ally->GetHealth() > 0) {
            return false; // Au moins un joueur vivant
        }
    }
    return true; // Aucun joueur survivant
}

bool CharacterManager::AreAllEnemiesDead() const
{
    for (const auto& enemy : enemies) {
        if (enemy && enemy->GetHealth() > 0) {
            return false; // Au moins un ennemi vivant
        }
    }
    return true; // Aucun ennemi survivant
}

void CharacterManager::EnemyATK()
{
    std::vector<Character*> alliesList = GetAllies();

    for (const std::unique_ptr<Character>& enemyUPtr : enemies)
    {
        Character* c = enemyUPtr.get();
        if (!c || alliesList.empty()) continue;

        int attackIndex = Utils::GenerateRandomNumber(1, c->GetNbAttacks());
        int targetIndex = Utils::GenerateRandomNumber(1, alliesList.size());
        Character* target = alliesList[targetIndex - 1];
        c->PerformAttack(attackIndex - 1, *target);
        RemoveDeadCharacters();
        alliesList = GetAllies(); // Met à jour la liste en cas de mort
    }
}

void CharacterManager::GainExp(Character* target)
{
    for (const auto& enemy : enemies) {
        if (enemy && enemy->GetHealth() <= 0) {
            int gainexp = enemy->GetExpGain();



        }
    }


}




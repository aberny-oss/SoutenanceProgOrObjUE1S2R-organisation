#include "CharacterManager.h"

void CharacterManager::AddAlly(std::unique_ptr<Character> character) {
    allies.push_back(std::move(character));
}

void CharacterManager::AddEnemy(std::unique_ptr<Character> character) {
    enemies.push_back(std::move(character));
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

void CharacterManager::BuildPriorityTable2D(size_t rows, size_t cols)
{
    tableRows = rows;
    tableCols = cols;
    table2D.clear();
    table2D.resize(rows, std::vector<Character*>(cols, nullptr));

    size_t r = 0, c = 0;

    // D'abord les ennemis
    for (const std::unique_ptr<Character>& ennemi : enemies) {
        if (!ennemi)
            continue;
        table2D[r][c] = ennemi.get();
        c++;
        if (c >= cols) {
            c = 0; r++;
        }
        if (r >= rows) {
            return;
        }
    }

    // Puis les alliés
    for (const std::unique_ptr<Character>& ally : allies) {
        if (!ally)
            continue;
        table2D[r][c] = ally.get();
        c++;
        if (c >= cols) {
            c = 0; r++;
        }
        if (r >= rows) {
            return;
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
                    // Séparateur optionnel entre colonnes
                    line_content += " ";
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


void CharacterManager::RemoveAlly(int index) {
    if (index >= 0 && index < static_cast<int>(allies.size())) {
        allies.erase(allies.begin() + index);
    }
}

void CharacterManager::RemoveEnemy(int index) {
    if (index >= 0 && index < static_cast<int>(enemies.size())) {
        enemies.erase(enemies.begin() + index);
    }
}

int CharacterManager::GetAllyCount() const {
    return static_cast<int>(allies.size());
}

int CharacterManager::GetEnemyCount() const {
    return static_cast<int>(enemies.size());
}

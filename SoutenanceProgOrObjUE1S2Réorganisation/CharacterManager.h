#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Character.h"
#include "Warrior.h"
#include "Utils.h"

class CharacterManager {
private:
    std::vector<std::unique_ptr<Character>> allies;
    std::vector<std::unique_ptr<Character>> enemies;
    std::vector<std::vector<Character*>> table2D;
    size_t tableRows;
    size_t tableCols;

public:
    CharacterManager() :tableRows(0), tableCols(0) {
	}

    void AddAlly(std::unique_ptr<Character> character);
    void AddEnemy(std::unique_ptr<Character> character);

    // Nombre de character
    size_t SizeAlly() const;
    // Nombre d'objets
    size_t SizeEnemy() const;

    Character* GetAlly(int index);
    std::vector<Character*> GetAllies();
    Character* GetEnemy(int index);

    void BuildTeamTable2D(size_t rows, size_t cols);
    void BuildPriorityTable2D(size_t rows, size_t cols);
	void DisplayTable2D() const;

    void RemoveAlly(int index);
    void RemoveEnemy(int index);

    int GetAllyCount() const;
    int GetEnemyCount() const;
};

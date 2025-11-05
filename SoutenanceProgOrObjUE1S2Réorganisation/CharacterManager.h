#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Utils.h"
#include "Character.h"

class CharacterManager {
private:
    std::vector<std::unique_ptr<Character>> allies;
    std::vector<std::unique_ptr<Character>> enemies;
    std::vector<std::vector<Character*>> table2D;
    size_t tableRows;
    size_t tableCols;
    Utils utils;

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
    Character* GetEnemy(int index);

    std::vector<Character*> GetAllies()const;
    std::vector<Character*> GetEnemies() const;


    void BuildTeamTable2D(size_t rows, size_t cols);
    void BuildEnemyTable2D(size_t rows, size_t cols);
    void BuildPriorityTable2D(size_t cols);
	void DisplayTable2D() const;

    void CombatTurn();

    int GetAllyCount() const;
    int GetEnemyCount() const;

    void RemoveDeadCharacters();

    bool AreAllPlayersDead() const;
    bool AreAllEnemiesDead() const;

};

#pragma once
#include <iostream>
//#include <vector>
//#include <string>
#include <memory>
#include <limits>
#include "CharacterManager.h"
#include "InputManager.h"
#include "ItemManager.h"
#include "ASCIIART.h"
#include "Character.h"
#include "Warrior.h"
#include "Mage.h"
#include "Goblin.h"
#include "Trader.h"
#include "Utils.h"

enum class GameState {
    MENU,
    COMBAT,
    VICTORY,
    DEFEAT,
	QUIT
};

class Game {
private:
    GameState currentState;
    std::unique_ptr<CharacterManager> characterManager;
    std::unique_ptr<InputManager> inputManager;

    int turn;
    bool isRunning;
    int menuIndex;
    int combatIndex;
    ASCIIART art;
    bool firstIteration;
	Utils utils;
    int combatCount;

    //menu
    void ShowMenuPrincipal();
    void ShowMenuPerso();
	void ShowMenuWinFight();
	void ShowMenuTrader();

    void CombatTurn();

    void HandleVictory();
    void HandleDefeat();

public:
    Game() : currentState(GameState::MENU),
		turn(0),
        isRunning(true),
        menuIndex(0),
        combatIndex(0),
        characterManager(std::make_unique<CharacterManager>()),
        inputManager(std::make_unique<InputManager>()),
		art(),
        firstIteration(true),
		combatCount(1)
    {
    }

    void Init();           // Initialise une nouvelle partie
	void CreateCharacter(); // Crée un personnage
    void Run();            // Boucle principale
	void Shutdown();       // Nettoyage

    //void Display();        // Affichage
    void ChangeState(GameState newState);

};


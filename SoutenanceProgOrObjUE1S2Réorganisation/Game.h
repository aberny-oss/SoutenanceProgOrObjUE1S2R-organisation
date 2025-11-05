#pragma once
#include <iostream>
#include <memory>
#include <limits>
#include "CharacterManager.h"
#include "InputManager.h"
#include "ASCIIART.h"

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
    ASCIIART art;
    bool firstIteration;

    //menu
    void ShowMenuPrincipal();
    void ShowMenuPerso();

    void HandleCombat();
    void HandleVictory();
    void HandleDefeat();

public:
    Game() : currentState(GameState::MENU),
		turn(0),
        isRunning(true),
        menuIndex(0),
        characterManager(std::make_unique<CharacterManager>()),
        inputManager(std::make_unique<InputManager>()),
		art(),
        firstIteration(true)
    {
    }

    void Init();           // Initialise une nouvelle partie
	void CreateCharacter(); // Crée un personnage
    void Run();            // Boucle principale
	void Shutdown();       // Nettoyage

    //void Display();        // Affichage
    void ChangeState(GameState newState);
};


//// Afficher les alliés
//for (int i = 0; i < characterManager->GetAllyCount(); ++i) {
//    Character* ally = characterManager->GetAlly(i);
//    if (ally) {
//        std::cout << "Allié: " << ally->GetName() << " (PV: " << ally->GetHealth() << ")" << std::endl;
//    }
//}
//
//// Afficher les ennemis
//for (int j = 0; j < characterManager->GetEnemyCount(); ++j) {
//    Character* enemy = characterManager->GetEnemy(j);
//    if (enemy) {
//        std::cout << "Ennemi: " << enemy->GetName() << " (PV: " << enemy->GetHealth() << ")" << std::endl;
//    }
//}


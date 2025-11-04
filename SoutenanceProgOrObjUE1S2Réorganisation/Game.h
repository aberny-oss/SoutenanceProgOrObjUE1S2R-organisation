#pragma once
//#include "CharacterManager.h"
//#include "InputManager.h"  // <-- AJOUT

enum class GameState {
    MENU,
    COMBAT,
    VICTOIRE,
    DEFAITE
};

class Game {
private:
    GameState currentState;
    //CharacterManager* characterManager;
    //InputManager* inputManager;  // <-- AJOUT
    bool isRunning;

    //void handleMenu();
    //void handleCombat();
    //void handleVictoire();
    //void handleDefaite();

public:
    Game();
    ~Game();

    void run();
    void update();
    void display();
    void changeState(GameState newState);
};

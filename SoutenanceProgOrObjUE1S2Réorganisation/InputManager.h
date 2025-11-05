#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ASCIIART.h"

enum class Action {
    NONE,
    ATTACK,
    HEAL,
    MENU_PERSO,
    MENU_QUIT,
    CONTINUE,
    QUIT
};

class InputManager {
private:
    char lastKey;
    ASCIIART art; // Pour afficher les messages d'erreur

public:
    InputManager(); // <-- DÉCLARATION du constructeur

    void Update();               // Capture l'entrée clavier
    Action GetAction();          // Retourne l'action correspondante
    //char GetLastKey() const;     // Retourne la dernière touche pressée
    //bool IsKeyPressed(char key); // Vérifie si une touche spécifique est pressée

	char AskRestrictedKey(const std::vector<char>& allowedKeys); // Demande une touche parmi une liste restreinte
    char AskMenuKey(const std::vector<char>& allowedKeys); // Demande une touche parmi une liste restreinte
};

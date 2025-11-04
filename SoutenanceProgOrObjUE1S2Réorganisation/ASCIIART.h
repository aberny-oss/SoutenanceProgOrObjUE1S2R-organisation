#pragma once
#include <iostream>
#include <string>

class ASCIIART {
private:
    // Attribut pour la saisie dynamique
    char inputValue;

public:
    // Setter pour la zone dynamique
    void SetInputValue(const char& value);

    // Affiche le menu selon l'action demandée
    void ArtConsoleMenu(int action);
};

#include "InputManager.h"

InputManager::InputManager() : lastKey('\0'), art() {}

void InputManager::Update() {
    std::cin >> lastKey;

    // Conversion en minuscule
    if (lastKey >= 'A' && lastKey <= 'Z') {
        lastKey = lastKey + 32;
    }
}

Action InputManager::GetAction() {
    switch (lastKey) {
    case 'a': return Action::ATTACK;
    case 's': return Action::HEAL;
    case 'p': return Action::MENU_PERSO;
    case 'q': return Action::QUIT;
    case 'c': return Action::CONTINUE;
    default:  return Action::NONE;
    }
}

char InputManager::AskMenuKey(const std::vector<char>& allowedKeys) {
    char key;
    std::cin >> key;

    if (key >= 'A' && key <= 'Z')
    {
        key = key + 32;
    }
    lastKey = key;        // Met à jour lastKey pour la suite du code
    return key;
}

char InputManager::AskRestrictedKey(const std::vector<char>& allowedKeys) {
    char key;
    while (true) {
        std::cin >> key;

        if (key >= 'A' && key <= 'Z')
            key = key + 32;

        if (std::find(allowedKeys.begin(), allowedKeys.end(), key) != allowedKeys.end()) {
            lastKey = key;        // Met à jour lastKey pour la suite du code
            return key;
        }
        std::cout << "Touche non valide, options permises : ";
        for (char k : allowedKeys) std::cout << k << " ";
        std::cout << std::endl;
    }
}

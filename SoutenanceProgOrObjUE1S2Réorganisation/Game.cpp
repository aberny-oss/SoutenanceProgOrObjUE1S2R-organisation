#include "Game.h"

void Game::Init() {
    characterManager->AddEnemy(std::make_unique<Warrior>("Ennemy1", "Ennemy"));
    characterManager->AddEnemy(std::make_unique<Warrior>("Ennemy2", "Ennemy"));
}

void Game::CreateCharacter()
{
    std::string name, type;
    std::cout << "Veuillez entrer votre nom de personnage : ";
    std::getline(std::cin, name);
    while (true)
    {
        std::cout << "Type du personnage (Warrior / Mage / Goblin) : ";
        std::getline(std::cin, type);

        // Conversion en minuscules
        std::transform(type.begin(), type.end(), type.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (type == "warrior")
        {
            return  characterManager->AddAlly(std::make_unique<Warrior>(name, "Player"));
        }
        /*else if (type == "mage")
        {
            return  characterManager->AddAlly(std::make_unique<Mage>(name, "Player"));
        }*/
        /*else if (type == "goblin")
        {
            return  characterManager->AddAlly(std::make_unique<Goblin>(name, "Player"));
        }*/

        system("cls");
        std::cout << "Type invalide. Reessaie !" << std::endl;
    }
}

void Game::Run() {
    while (currentState != GameState::QUIT) {
        turn += 1;
        if (currentState == GameState::MENU)
        {
            switch (menuIndex)
            {
            case 0: ShowMenuPrincipal(); break;
            case 1: ShowMenuPerso(); break;
            }
        }

        switch (currentState) {
        case GameState::COMBAT: HandleCombat(); break;
        case GameState::VICTORY: HandleVictory(); break;
        case GameState::DEFEAT: HandleDefeat(); break;
        case GameState::QUIT: Shutdown(); break;
        }
    }
}

void Game::Shutdown() {
    // Nettoyage si nécessaire
    std::cout << "Nettoyage des ressources du jeu..." << std::endl;
}

//void Game::Display() {
//    std::cout << "--- Affichage de l'état du jeu ---" << std::endl;
//    // Ici, on pourrait afficher les états, la vie, etc.
//}

void Game::ShowMenuPrincipal()
{
    int action = 0;
    art.ArtConsoleMenu(action); // affiche menu initial
    while (true) {
        std::vector<char> menuKeys = { 'c', 'q' };
        char key = inputManager->AskMenuKey(menuKeys);
        // gestion selon le résultat


        // Mettre à jour l'affichage dynamique
        art.SetInputValue(key);

        if (key == 'c') {
            menuIndex = 1; // si tu utilises ce menuID autre part
            break;
        }
        else if (key == 'q')
        {
			action = 2;
            currentState = GameState::QUIT;
            break;
        }
        else {
            action = 1;
            art.ArtConsoleMenu(action);
        }
    }
}

void Game::ShowMenuPerso()
{
    if (firstIteration == true)
    {
        system("cls");
#undef max
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        CreateCharacter();
        firstIteration = false;
        /*characterManager.BuildPriorityTable2D("Ennemy", 2, 2);*/
    }
    characterManager->BuildTeamTable2D(1, 1);
    bool stay = true;
    while (stay)
    {
        system("cls");
        characterManager->DisplayTable2D();
        // Affichage des attaques de chaque allié
        for (int i = 0; i < characterManager->GetAllyCount(); ++i) {
            Character* ally = characterManager->GetAlly(i);
            if (ally) {
                ally->DisplayAttacks();
            }
        }
		std::cout << "\n" << std::endl;
        std::cout << "Que souhaite vous faire Combattre (C) ou quitter le jeu (Q)" << std::endl;
        std::vector<char> menuKeys = { 'c', 'q' };
        char key = inputManager->AskRestrictedKey(menuKeys);

        switch (key)
        {
        case'c':
            currentState = GameState::COMBAT;
            break;
        case'q':
            currentState = GameState::QUIT;
            break;
        }
        stay = false;
    }
}

void Game::HandleCombat()
{
    characterManager->BuildPriorityTable2D(2, 2);
	system("cls");
    while (true)
    {
        characterManager->DisplayTable2D();
        std::cout << "\n" << std::endl;
        std::cout << "Que souhaite vous faire Attaquer (A), vous Soigner (S) ou Quitter le jeu (Q)" << std::endl;
        std::vector<char> menuKeys = { 'a', 'c', 'q' };
        char key = inputManager->AskRestrictedKey(menuKeys);

        switch (key)
        {
        case'a':
            for (Character* c : characterManager->GetAllies()) {
                if (c) c->Attack();
            }

            break;
        case's':
            break;
        case'q':
            break;
        }
    }
}



void Game::HandleVictory() {
    std::cout << "[VICTOIRE] (c: rejouer, q: quitter)" << std::endl;
    Action action = inputManager->GetAction();

    if (action == Action::CONTINUE) {
        Init(); // Une nouvelle partie démarre
    }
    else if (action == Action::QUIT) {
        isRunning = false;
    }
}

void Game::HandleDefeat() {
    std::cout << "[DEFAITE] (c: rejouer, q: quitter)" << std::endl;
    Action action = inputManager->GetAction();

    if (action == Action::CONTINUE) {
        Init();
    }
    else if (action == Action::QUIT) {
        isRunning = false;
    }
}

void Game::ChangeState(GameState newState) {
    currentState = newState;
    std::cout << ">>> Changement d'état <<<" << std::endl;
}

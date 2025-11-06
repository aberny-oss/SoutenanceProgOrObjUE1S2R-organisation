#include "Game.h"

void Game::Init() {
    int enemyCount = 3;
    for (int i = 1; i <= enemyCount; ++i) {
        int level = Utils::GenerateRandomNumber(1, 5);
        int whealth = 120 + (level - 1) * 20;
        int mhealth = 100 + (level - 1) * 20;
        int ghealth = 80 + (level - 1) * 20;
        std::string name = "Ennemy" + std::to_string(i);

        if (i == 1) {
            characterManager->AddEnemy(std::make_unique<Warrior>(name, level, whealth, "Ennemy"));
        }
        else if (i == 2) {
            characterManager->AddEnemy(std::make_unique<Mage>(name, level, mhealth, "Ennemy"));
        }
        else if (i == 3) {
            characterManager->AddEnemy(std::make_unique<Goblin>(name, level, ghealth, "Ennemy"));
        }
        else
        {
            // Tirage aléatoire de la classe
            int type = Utils::GenerateRandomNumber(1, 3); // 1=Warrior, 2=Mage, 3=Goblin
            switch (type)
            {
            case 1:
                characterManager->AddEnemy(std::make_unique<Warrior>(name, level, whealth, "Ennemy"));
                break;
            case 2:
                characterManager->AddEnemy(std::make_unique<Mage>(name, level, mhealth, "Ennemy"));
                break;
            case 3:
                characterManager->AddEnemy(std::make_unique<Goblin>(name, level, ghealth, "Ennemy"));
                break;
            }
		}
    }
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
			int level = 8;
            int whealth = 120 + (level - 1) * 20;
            return  characterManager->AddAlly(std::make_unique<Warrior>(name, level, whealth, "Player"));
        }
        else if (type == "mage")
        {
            int level = 8;
            int mhealth = 100 + (level - 1) * 20;
            return  characterManager->AddAlly(std::make_unique<Mage>(name, level, mhealth, "Player"));
        }
        else if (type == "goblin")
        {
            int level = 8;
            int ghealth = 80 + (level - 1) * 20;
            return  characterManager->AddAlly(std::make_unique<Goblin>(name, level, ghealth, "Player"));
        }

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
			case 2: ShowMenuWinFight(); break;
            }
        }

        switch (currentState) {
            case GameState::COMBAT:
                CombatTurn();
                if (combatIndex == 1)
                {
                    characterManager->Attack();
                }
                else if (combatIndex == 2)
                {
                    characterManager->Heal();
                }
                characterManager->RemoveDeadCharacters();
                if (characterManager->AreAllPlayersDead())
                {
                    currentState = GameState::DEFEAT;
                }
                else if(characterManager->AreAllEnemiesDead())
                {
				    menuIndex = 2;
                    currentState = GameState::MENU;
			    }
                characterManager->EnemyATK();
                break;
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
        system("cls");

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

void Game::CombatTurn()
{
    // Sélection du personnage actif
#undef max
    size_t maxColsCount = std::max(characterManager->GetAllyCount(), characterManager->GetEnemyCount());
    if (maxColsCount == 0)
    {
        maxColsCount = 1; // Pour ne jamais avoir 0 colonnes
    }
    characterManager->BuildPriorityTable2D(maxColsCount);
    characterManager->DisplayTable2D();
    std::cout << "Voulez vous Attaquer (A) ou vous Soigner (S)" << std::endl;
    std::vector<char> menuKeys = { 'a', 's' };
    int key = inputManager->AskRestrictedKey(menuKeys);
    if (key == 'a')
    {
        combatIndex = 1;
    }
    else if (key == 's')
    {
        combatIndex = 2;
    }
}

void Game::ShowMenuWinFight()
{
	system("cls");
	std::cout << "\n" << std::endl;
    std::cout << R"(
+===========================+
|         VICTOIRE !        |
|   Tu as gagne le combat   |
|  Tes heros sont vaillants |
|    Qu veux-tu faire ?     |
| (c: Continuer, q: Quitter)|
+===========================+
)" << std::endl;
    std::cout << "\n" << std::endl;
    std::vector<char> menuKeys = { 'c', 'q' };
    char key = inputManager->AskMenuKey(menuKeys);
    if (key == 'c') {
		menuIndex = 1; // Retour au menu perso pour continuer le combat
    }
    else if (key == 'q') {
		currentState = GameState::QUIT;
	}

}

void Game::HandleVictory() {
    std::cout << "[VICTOIRE] (c: Rejouer, q: Quitter)" << std::endl;
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

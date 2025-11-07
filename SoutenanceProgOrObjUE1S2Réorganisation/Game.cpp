#include "Game.h"

void Game::Init()
{
    int enemyCount = 0 + combatCount; // Ennemis grandissant à chaque combat
    for (int i = 1; i <= enemyCount; ++i)
    {
        // Augmente le niveau selon la progression
        int level = Utils::GenerateRandomNumber(1 + combatCount, 5 + combatCount);
        int whealth = 120 + (level - 1) * (20 + 5 * combatCount); // Plus de PV selon le combat
        int mhealth = 100 + (level - 1) * (20 + 5 * combatCount);
        int ghealth = 80 + (level - 1) * (20 + 5 * combatCount);
        double expUp = 100 * pow(1.1 + 0.03 * combatCount, level - 1); // Plus d'XP et scaling
        int xpGain = 50 * pow(1.13, level - 1);

        std::string name = "Ennemy" + std::to_string(i + (combatCount - 1) * enemyCount);

        int type = Utils::GenerateRandomNumber(1, 3);
        switch (type) {
        case 1:
            characterManager->AddEnemy(std::make_unique<Warrior>(name, level, whealth, whealth, "Ennemy", expUp, xpGain));
            break;
        case 2:
            characterManager->AddEnemy(std::make_unique<Mage>(name, level, mhealth, mhealth, "Ennemy", expUp, xpGain));
            break;
        case 3:
            characterManager->AddEnemy(std::make_unique<Goblin>(name, level, ghealth, ghealth, "Ennemy", expUp, xpGain));
            break;
        }
    }
    characterManager->AddNeutre(std::make_unique<Trader>("Alexis", "Neutre", 0, 250));
}

void Game::CreateCharacter()
{
    for (int i = 0; i < 2; ++i)
    {
        std::string name, type;
        std::cout << "Entrez le nom du personnage allie " << (i + 1) << " : ";
        std::getline(std::cin, name);

        while (true)
        {
            std::cout << "Type du personnage (Warrior / Mage / Goblin) : ";
            std::getline(std::cin, type);

            std::transform(type.begin(), type.end(), type.begin(),
                [](unsigned char c) { return std::tolower(c); });

            int level = 1;
            double expUp = 100 * pow(1.1, level - 1);
            int xpGain = 50 * pow(1.13, level - 1);
            if (type == "warrior")
            {
                int whealth = 120 + (level - 1) * 20;
                int whealthMax = whealth;
                characterManager->AddAlly(std::make_unique<Warrior>(name, level, whealth, whealthMax, "Player", expUp, xpGain));
                system("cls");
                break; // veux créer un autre allié ou sortir
            }
            else if (type == "mage")
            {
                int mhealth = 100 + (level - 1) * 20;
                int mhealthMax = mhealth;
                characterManager->AddAlly(std::make_unique<Mage>(name, level, mhealth, mhealthMax, "Player", expUp, xpGain));
                system("cls");
                break;
            }
            else if (type == "goblin")
            {
                int ghealth = 80 + (level - 1) * 20;
                int ghealthMax = ghealth;
                characterManager->AddAlly(std::make_unique<Goblin>(name, level, ghealth, ghealthMax, "Player", expUp, xpGain));
                system("cls");
                break;
            }

            system("cls");
            std::cout << "Type invalide. Reessaie !" << std::endl;
        }
    }
}

void Game::Run() {
    while (currentState != GameState::QUIT)
    {
        turn += 1;
        if (currentState == GameState::MENU)
        {
            switch (menuIndex)
            {
            case 0: ShowMenuPrincipal(); break;
            case 1: ShowMenuPerso(); break;
			case 2: ShowMenuWinFight(); break;
			case 3: ShowMenuTrader(); break;
            }
        }

        switch (currentState)
        {
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

void Game::Shutdown()
{
    // Nettoyage si nécessaire
    std::cout << "Nettoyage des ressources du jeu..." << std::endl;
}

void Game::ShowMenuPrincipal()
{
    int action = 0;
    art.ArtConsoleMenu(action); // affiche menu initial
    while (true)
    {
        std::vector<char> menuKeys = { 'c', 'q' };
        char key = inputManager->AskMenuKey(menuKeys);
        // gestion selon le résultat

        // Mettre à jour l'affichage dynamique
        art.SetInputValue(key);

        if (key == 'c')
        {
            menuIndex = 1; // si tu utilises ce menuID autre part
            break;
        }
        else if (key == 'q')
        {
			action = 2;
            currentState = GameState::QUIT;
            break;
        }
        else
        {
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
    }

    // Récupérer la liste à jour !
    std::vector<Character*> alliesList = characterManager->GetAllies();
    size_t cols = alliesList.size();
    if (cols == 0)
    {
        cols = 1;
    }
    characterManager->BuildTeamTable2D(1, cols);

    bool stay = true;
    while (stay)
    {
        system("cls");
        characterManager->DisplayTable2D();
        for (size_t i = 0; i < alliesList.size(); ++i)
        {
            Character* ally = alliesList[i];
            if (ally)
            {
                ally->DisplayAttacks();
            }
        }
        std::cout << "\n" << std::endl;
        std::cout << "Que souhaitez-vous faire : Combattre (C), Trader (T), ou quitter le jeu (Q) ?" << std::endl;
        std::vector<char> menuKeys = { 'c', 't', 'q' };
        char key = inputManager->AskRestrictedKey(menuKeys);
        system("cls");

        switch (key)
        {
        case 'c':
            currentState = GameState::COMBAT;
            break;
        case 't':
            menuIndex = 3;
            currentState = GameState::MENU;
            break;
        case 'q':
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
    combatCount += 1;
	system("cls");
	std::cout << "\n" << std::endl;
    std::cout << R"(
+===========================+
|         VICTOIRE !        |
|   Tu as gagne le combat   |
|  Tes heros sont vaillants |
|    Que veux-tu faire ?    |
| (c: Continuer, q: Quitter)|
+===========================+
)" << std::endl;
    std::cout << "\n" << std::endl;
    std::vector<char> menuKeys = { 'c', 'q' };
    char key = inputManager->AskMenuKey(menuKeys);
    if (key == 'c')
    {
		menuIndex = 1; // Retour au menu perso pour continuer le combat
    }
    else if (key == 'q')
    {
		currentState = GameState::QUIT;
	}
}

void Game::ShowMenuTrader()
{
    std::cout << "\n" << std::endl;
    std::cout << R"(
+===========================+
|          TRADER !        |
+===========================+
|  Bienvenue chez le Trader |
+===========================+
)" << std::endl;

    Character* trader = characterManager->GetNeutre(0);

    if (!trader)
    {
        std::cout << "Aucun trader trouvé !" << std::endl;
        return; // Sort proprement si pas de trader
    }

    bool achat = true;
    while (achat)
    {
        std::vector<std::string> lignes = trader->Display();
        for (const auto& ligne : lignes)
        {
            std::cout << ligne << std::endl;
        }

        std::cout << "Voulez-vous acheter une potion de soin ? (O: Oui, N: Non) : " << std::endl;
        std::vector<char> menuKeys = { 'o', 'n' };
        char targetIndexchar = inputManager->AskRestrictedKey(menuKeys);
        system("cls");

        Trader* realTrader = dynamic_cast<Trader*>(trader);
        if (!realTrader)
        {
            std::cout << "Erreur : Ce personnage neutre n'est pas un Trader." << std::endl;
            achat = false;
            break;
        }

        if (targetIndexchar == 'o')
        {
            realTrader->DisplayTrader();
            int targetIndexint = utils.AskInt("Faite votre choix ->", 1, 4);
            switch (targetIndexint)
            {
            case 1:
            {
                Character* ally = characterManager->GetAlly(0);
                if (ally)
                {
                    realTrader->PerformTrade(0, *ally, realTrader->GetGold());
                }
                else
                {
                    std::cout << "Aucun allié trouvé !" << std::endl;
                }
            }
            break;
            case 2:
            {
                Character* ally = characterManager->GetAlly(0);
                if (ally)
                {
                    realTrader->PerformTrade(1, *ally, realTrader->GetGold());
                }
                else
                {
                    std::cout << "Aucun allié trouvé !" << std::endl;
                }
            }
            break;
            case 3:
            {
                Character* ally = characterManager->GetAlly(0);
                if (ally)
                {
                    realTrader->PerformTrade(2, *ally, realTrader->GetGold());
                }
                else
                {
                    std::cout << "Aucun allié trouvé !" << std::endl;
                }
            }
            break;
            case 4:
                menuIndex = 1; // Retour au menu perso
                achat = false;
                break;
            }
        }
        if (targetIndexchar == 'n')
        {
            menuIndex = 1; // Retour au menu perso
            achat = false;
			currentState = GameState::MENU;
		}
    }
}

void Game::HandleVictory()
{
    std::cout << "[VICTOIRE] (c: Rejouer, q: Quitter)" << std::endl;
    Action action = inputManager->GetAction();

    if (action == Action::CONTINUE)
    {
        Init(); // Une nouvelle partie démarre
    }
    else if (action == Action::QUIT)
    {
        isRunning = false;
    }
}

void Game::HandleDefeat()
{
    std::cout << "[DEFAITE] (c: rejouer, q: quitter)" << std::endl;
    Action action = inputManager->GetAction();

    if (action == Action::CONTINUE)
    {
        Init();
    }
    else if (action == Action::QUIT)
    {
        isRunning = false;
    }
}

void Game::ChangeState(GameState newState)
{
    currentState = newState;
    std::cout << ">>> Changement d'état <<<" << std::endl;
}

#include "Game.h"

int main() {
	Utils::InitRandom();
    Game game;
    game.Init();
    game.Run();
    game.Shutdown();
    return 0;
}
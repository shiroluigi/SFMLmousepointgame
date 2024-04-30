#include "Game.h"

int main()
{
    Game game(900, 900, "Documentation");
    while (game.isRunning)
    {
        game.run();
    }
    return 0;
}
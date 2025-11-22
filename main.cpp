#include "Game.h"

int main()
{
    Game game(900, 900, "Super Amazing Game");
    while (game.isRunning)
    {
        game.run();
    }
    return 0;
}
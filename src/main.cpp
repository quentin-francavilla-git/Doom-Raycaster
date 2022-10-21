#include "../include/lib.hpp"
#include "../include/Game.hpp"

int main()
{
    Game game;

    while (game.running())
    {
        // Update
        game.update();
        // Render
        game.render();
    }

    return 0;
}
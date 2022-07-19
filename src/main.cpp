#include "../include/lib.hpp"
#include "../include/Game.hpp"

int main()
{
  Game game;

  cout << game.getPlayer(0).getName() << endl;

  while (game.running())
  {
    // Update
    game.update();
    // Render
    game.render();
  }

  return 0;
}
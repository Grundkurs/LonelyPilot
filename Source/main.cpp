#include "Game.h"


int main()
    {
	Game game; 
	if (game.Initialize())
		{
		return game.Run(); 
		}
    }

#include "Game.h"
int main()
	{
	//   1024   x  768 Window Resolution
	Game game( ( 768 * 12/9 ), 768);
	if( game.Initialize() )
		{
		return game.Run();
		}
	return 1;
	}

#include "Game.h"
#include "tinyxml2.h"
#include "StringUtilities.h"

#include <iostream>


int main()
    {

    Game game;

    if(game.Initialize())
        {
        return game.Run();
        }
    }

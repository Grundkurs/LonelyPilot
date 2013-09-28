#include "Game.h"
#include "tinyxml2.h"
#include <iostream>

#include "XML.h"

int main()
	{

    if(!XML::Init_XML_File("config.xml"))
        {
		std::cout << "could not open Config-File. Terminate now."; 
		return 1; 
        }
    int height = XML::LoadContentInt("WINDOW", "HEIGHT");
    float ratio = ((float)XML::LoadContentInt("WINDOW", "RATIO")) / 9;
    Game game(height * ratio, height);

    if(game.Initialize())
        {
        return game.Run();
        }
    }

#include "Game.h"
#include "tinyxml2.h"
#include "StringUtilities.h"

#include <iostream>

#include "XML.h"

int main()
	{
	string file("../Resources/Scripts/config.xml");
	if(!XML::Init_XML_File(ToPlatformPath(file)))
		{
		std::cout << "could not open Config-File. Terminate now.";
		return 1;
		}
	int height = XML::LoadContentInt("WINDOW", "HEIGHT");
	float ratio = ((float)XML::LoadContentInt("WINDOW", "RATIO")) / 9;
	Game game;

	if(game.Initialize())
		{
		return game.Run();
		}
	}

#include "Game.h"
#include "tinyxml2.h"
#include <iostream>
#include "XML_Loader.h"
#include "StringUtilities.h"
#include "ConfigLoader.h"

#include "XML_Loader.h"

int main()
	{
	string file("../Resources/Scripts/config.xml");
	tinyxml2::XMLDocument doc;
	if(!XML::Init_XML_File(doc, ToPlatformPath(file)))
		{
		std::cout << "could not open Config-File. Terminate now.";
		return 1;
		}
	int height = XML::LoadContentInt(doc, "WINDOW", "HEIGHT");
	float ratio = ((float)XML::LoadContentInt(doc, "WINDOW", "RATIO")) / 9;

	//   1024   x  768 Window Resolution
	Game game( height * ratio, height);
	if( game.Initialize() )
		{
		return game.Run();
		}
	return 1;
	}

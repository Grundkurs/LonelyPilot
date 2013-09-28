#include "ConfigLoader.h"

#include "tinyxml2.h"
using namespace tinyxml2;

#include <iostream>
using std::cout;
#include <exception>
#include <stdexcept>

ConfigLoader::ConfigLoader()
	:
	mScreenWidth(800),
	mScreenHeight(600),
	mWindowTitle("SFML Game."),
	mPlayerSpeedX(10),
	mPlayerSpeedY(5)
	{

	}

ConfigLoader::ConfigLoader(const string & file)
	:
	ConfigLoader()
	{
	if ( !LoadFromFile(file) )
		throw std::invalid_argument("Can't parse xml file");
	}

bool ConfigLoader::LoadFromFile(const string &file)
	{
	XMLDocument doc;
	XMLError error = doc.LoadFile( file.c_str() );
	switch(error)
		{
		case(tinyxml2::XML_NO_ERROR):
			{
			cout << "XML-File loaded successful\n";
			break;
			}
		case(tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED):
			{
			cout << "could not open file\n";
			return false;
			}
		case(tinyxml2::XML_ERROR_FILE_NOT_FOUND):
			{
			cout << "file not found\n";
			return false;
			}
		default:
			{
			cout << "unknown error\n";
			return false;
			}
		} // End of Switch

	XMLElement * pGameSettings = doc.FirstChildElement("settings");

	if ( !pGameSettings )
		return false;

	if ( pGameSettings->QueryIntAttribute("screenWidth", &mScreenWidth) )
		{
		return false;
		}

	if ( pGameSettings->QueryIntAttribute("screenHeight", &mScreenHeight) )
		{
		return false;
		}

	mWindowTitle = pGameSettings->Attribute("windowTitle");

	XMLElement * pPlayerSettings = doc.FirstChildElement("player");
	if ( !pPlayerSettings )
		{
		return false;
		}

	if ( pPlayerSettings->QueryFloatAttribute("playerSpeedX", &mPlayerSpeedX) )
		{
		return false;
		}

	if ( pPlayerSettings->QueryFloatAttribute("playerSpeedY", &mPlayerSpeedY) )
		{
		return false;
		}

	return true;
	}

int ConfigLoader::GetScreenWidth() const
	{
	return mScreenWidth;
	}

int ConfigLoader::GetScreenHeight() const
	{
	return mScreenHeight;
	}

const std::string & ConfigLoader::GetWindowTitle() const
	{
	return mWindowTitle;
	}

float ConfigLoader::GetPlayerSpeedX() const
	{
	return mPlayerSpeedX;
	}

float ConfigLoader::GetPlayerSpeedY() const
	{
	return mPlayerSpeedY;
	}

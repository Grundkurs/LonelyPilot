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

    //Game Settings
	XMLElement * pGameSettings = doc.FirstChildElement("settings");

	if ( !pGameSettings )
        {
        std::cout << "no Settings in XML-File";
		return false;
        }

    mWindowTitle = pGameSettings->FirstChildElement("windowTitle")->GetText();



    if( pGameSettings->FirstChildElement("screenWidth")->QueryIntText(&mScreenWidth) )
        {
        cout << "could not load screen Width";
        return false;
        }


    if( pGameSettings->FirstChildElement("screenHeight")->QueryIntText(&mScreenHeight) )
        {
        return false;
        }


    // Player Settings
	XMLElement * pPlayerSettings = doc.FirstChildElement("player");
	if ( !pPlayerSettings )
		{
		return false;
		}

    mPlayerTexPath = pPlayerSettings->FirstChildElement("texturePath")->GetText();
    mPlayerTexFrontPath = pPlayerSettings->FirstChildElement("textureFrontPath")->GetText();
    mTextureLasersPath = pPlayerSettings->FirstChildElement("textureLasersPath")->GetText();

    if ( pPlayerSettings->FirstChildElement("speedX")->QueryFloatText(&mPlayerSpeedX) )
		{
		return false;
		}

    if ( pPlayerSettings->FirstChildElement("speedY")->QueryFloatText(&mPlayerSpeedY) )
        {
        return false;
        }

    if ( pPlayerSettings->FirstChildElement("collisionBumper")->QueryFloatText(&mPlayerCollisionBumper) )
        {
        return false;
        }

    if ( pPlayerSettings->FirstChildElement("maxSpeed")->QueryFloatText(&mPlayerMaxSpeed) )
        {
        return false;
        }


    if ( pPlayerSettings->FirstChildElement("damageBoost")->QueryIntText(&mPlayerDamageBoost) )
        {
        return false;
        }

    XMLElement* pStarSettings = doc.FirstChildElement("star");
    if( !pStarSettings  )
        {
        return false;
        }

    if(pStarSettings->FirstChildElement("amountOfStars")->QueryIntText(&mStarAmount ))
        {
        return false;
        }

    mStarTexPath = pStarSettings->FirstChildElement("texturePath")->GetText();
	XMLElement * pEnemiesSettings = doc.FirstChildElement("enemies");

	if (!pEnemiesSettings) return false;

	mBaldusTexPath = pEnemiesSettings->FirstChildElement("BaldusTexturePath")->GetText(); 

	XMLElement* pHUDSettings = doc.FirstChildElement("HUD"); 
	
	if (!pHUDSettings) return false; 

	HUDLivesTexPath = pHUDSettings->FirstChildElement("LivesTexturePath")->GetText(); 
	HUDHealthBarPath = pHUDSettings->FirstChildElement("HealthBarTexturePath")->GetText();

	return true;
    } //end of Initialize();


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


//player
float& ConfigLoader::GetPlayerSpeedX()
	{
	return mPlayerSpeedX;
	}

float& ConfigLoader::GetPlayerSpeedY()
	{
	return mPlayerSpeedY;
	}

float& ConfigLoader::GetPlayerCollisionBumper()
    {
    return mPlayerCollisionBumper;
    }
float& ConfigLoader::GetPlayerMaxSpeed()
    {
    return mPlayerMaxSpeed;
    }
int& ConfigLoader::GetPlayerDamageBoost()
    {
    if(mPlayerDamageBoost < 0 || mPlayerDamageBoost > 4)
        {
        mPlayerDamageBoost = 0;
        }
    return mPlayerDamageBoost;
    }
sf::Vector2f ConfigLoader::GetPlayerSpeed()
    {
    return sf::Vector2f(mPlayerSpeedX, mPlayerSpeedY);
    }

std::string& ConfigLoader::GetPlayerTexPath()
    {
    return mPlayerTexPath;
    }
std::string& ConfigLoader::GetPlayerTexFrontPath()
    {
    return mPlayerTexFrontPath;
    }

std::string& ConfigLoader::GetTextureLasersPath()
    {
     return mTextureLasersPath;
    }

//Star

int& ConfigLoader::GetStarAmount()
    {
    return mStarAmount;
    }
string& ConfigLoader::GetStarTexPath()
    {
    return mStarTexPath;
    }


string& ConfigLoader::GetBaldusTexPath(){ return mBaldusTexPath; }

string& ConfigLoader::GetHUDLivesBarTexPath(){ return HUDLivesTexPath; }

string& ConfigLoader::GetHUDHealthBarPath(){ return HUDHealthBarPath; }
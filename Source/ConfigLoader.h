#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <string>
#include <SFML/Graphics.hpp>


using std::string;

class ConfigLoader
{
public:
	ConfigLoader();
	ConfigLoader(const string & file);

	bool LoadFromFile( const string & file );

	// Game Settings
	int GetScreenWidth() const;
	int GetScreenHeight() const;
	const string & GetWindowTitle() const;

	// Player Settings
    float& GetPlayerSpeedX() ;
    float& GetPlayerSpeedY() ;
    float& GetPlayerCollisionBumper();
    float& GetPlayerMaxSpeed();
    int&   GetPlayerDamageBoost();
    sf::Vector2f GetPlayerSpeed();
	string& GetPlayerTexPath();
	string& GetPlayerTexFrontPath();
    string& GetTextureLasersPath();

    //Star Settings
    int& GetStarAmount();
    string& GetStarTexPath();

	//enemies Settings
	string& GetBaldusTexPath();

	//HUD
	string& GetHUDLivesTexPath(); 

private:
	// Game Settings
	int mScreenWidth;
	int mScreenHeight;
	string mWindowTitle;

	// Player Settings
	float mPlayerSpeedX;
	float mPlayerSpeedY;
    float mPlayerMaxSpeed;
    string mPlayerTexPath;
    string mPlayerTexFrontPath;
    string mTextureLasersPath;
    float mPlayerCollisionBumper;
    int mPlayerDamageBoost;

    // Star Settings
    int mStarAmount;
	string mStarTexPath;

	// Enemy Settings
	string mBaldusTexPath; 

	//HUD Settings
	string HUDLivesTexPath; 
	
};

#endif // CONFIGLOADER_H

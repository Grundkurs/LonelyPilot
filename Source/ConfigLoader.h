#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <string>
#include <SFML/Graphics.hpp>


using std::string;

// STEFAN don't look at this class until you've made your own.
// For learning purposes.

// TODO: Should probably make data private and write getters
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
    std::string& GetPlayerTexPath();
    std::string& GetPlayerTexFrontPath();
    std::string& GetTextureLasersPath();

    //Star Settings
    int& GetStarAmount();
    std::string& GetStarTexPath();

	//enemies Settings
	std::string& GetBaldusTexPath();

private:
	// Game Settings
	int mScreenWidth;
	int mScreenHeight;
	string mWindowTitle;

	// Player Settings
	float mPlayerSpeedX;
	float mPlayerSpeedY;
    float mPlayerMaxSpeed;
    std::string mPlayerTexPath;
    std::string mPlayerTexFrontPath;
    std::string mTextureLasersPath;
    float mPlayerCollisionBumper;
    int mPlayerDamageBoost;

    // Star Settings
    int mStarAmount;
    std::string mStarTexPath;

	// Enemy Settings
	std::string mBaldusTexPath; 
	
};

#endif // CONFIGLOADER_H

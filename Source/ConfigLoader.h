#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <string>
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
	float GetPlayerSpeedX() const;
	float GetPlayerSpeedY() const;

private:
	// Game Settings
	int mScreenWidth;
	int mScreenHeight;
	string mWindowTitle;

	// Player Settings
	float mPlayerSpeedX;
	float mPlayerSpeedY;
};

#endif // CONFIGLOADER_H

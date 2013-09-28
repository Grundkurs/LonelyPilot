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

	int GetScreenWidth();
	int GetScreenHeight();

	const string & GetWindowTitle();
private:
	int mScreenWidth;
	int mScreenHeight;

	string mWindowTitle;
};

#endif // CONFIGLOADER_H

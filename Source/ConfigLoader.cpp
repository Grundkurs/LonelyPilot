#include "ConfigLoader.h"

#include "tinyxml2.h"
using namespace tinyxml2;
#include <exception>
#include <stdexcept>

ConfigLoader::ConfigLoader()
	:
	mScreenWidth(800),
	mScreenHeight(600),
	mWindowTitle("SFML Game.")
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
	if ( error != XML_NO_ERROR )
		{
		return false;
		}

	XMLElement * pSettings = doc.FirstChildElement();

	if ( !pSettings )
		return false;


	// this way will over write the fields with 0 if there
	// was error on parse and/or conversion.
//	mScreenWidth = pSettings->IntAttribute("screenWidth");
//	mScreenHeight = pSettings->IntAttribute("screenHeight");
//	mWindowTitle = pSettings->Attribute("windowTitle");

	// this way has better error detection,
	// if an error happened the fields value is not changed
	// so the defaults are still contained.
	// this code doesn't need to throw since the values
	// have been set to default in ctor.
	if ( pSettings->QueryIntAttribute("screenWidth", &mScreenWidth) )
		{
		return false;
		}

	if ( pSettings->QueryIntAttribute("screenHeight", &mScreenHeight) )
		{
		return false;
		}

	mWindowTitle = pSettings->Attribute("windowTitle");
	return true;
	}

int ConfigLoader::GetScreenWidth()
	{
	return mScreenWidth;
	}

int ConfigLoader::GetScreenHeight()
	{
	return mScreenHeight;
	}

const std::string & ConfigLoader::GetWindowTitle()
	{
	return mWindowTitle;
	}

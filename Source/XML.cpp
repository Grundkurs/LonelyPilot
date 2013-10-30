#include "XML.h"
#include <iostream>

tinyxml2::XMLDocument XML::doc;

bool XML::Init_XML_File(const std::string& fileName)
	{
	using namespace::std;
		tinyxml2::XMLError errLoading = doc.LoadFile(fileName.c_str());

		switch(errLoading)
			{
			case(tinyxml2::XML_NO_ERROR):{
										cout << "XML-File loaded successful\n";
										 return true;
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

		}

	std::string XML::LoadContentString(const std::string& Entity, const std::string& Attribute)
		{
		 std::string str(doc.FirstChildElement( Entity.c_str() )->FirstChildElement( Attribute.c_str() )->GetText());

		// Pseudo-Code for
		// "texture.loadFromFile(path);
		  // cout << "Loading: " << str << endl;
		return str;
		}

		 int XML::LoadContentInt(const std::string& Entity, const std::string& Attribute)
			{
			 const char * str = doc.FirstChildElement( Entity.c_str() )->FirstChildElement( Attribute.c_str())->GetText();

			//std::size_t lastChr;
			int number = 0;
			number = std::atoi(str);
			return number;
			}

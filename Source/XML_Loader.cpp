#include "XML_Loader.h"
#include <iostream>


namespace XML
	{
	bool Init_XML_File(tinyxml2::XMLDocument& document, const std::string& fileName)
		{
		using namespace::std;
		tinyxml2::XMLError errLoading = document.LoadFile(fileName.c_str());

		switch(errLoading)
			{

			case(tinyxml2::XML_NO_ERROR):{
										cout << "loading successful\n";
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


	void LoadContentString(tinyxml2::XMLDocument& doc, const std::string& Entity, const std::string& Attribute)
		{
			std::string str(doc.FirstChildElement( Entity.c_str() )->FirstChildElement( Attribute.c_str() )->GetText());

		// Pseudo-Code for
		// "texture.loadFromFile(path);
		// cout << "Loading: " << str << endl;
		}

	int LoadContentInt(tinyxml2::XMLDocument& doc, const std::string& Entity, const std::string& Attribute)
		{
			const char * str = doc.FirstChildElement( Entity.c_str() )->FirstChildElement( Attribute.c_str())->GetText();

		std::size_t lastChr;
		int number = 0;
		number = std::atoi(str);
		return number;
		}

	//TODO: Write String to Float converter
//    float LoadContentFloat(tinyxml2::XMLDocument& doc, const std::string& Entity, const std::string& Attribute)
//		{
//			std::string str( doc.FirstChildElement(Entity.c_str())->FirstChildElement(Attribute.c_str())->GetText() );

//			std::size_t lastChar;
//			float number;
//			number = std::stof(str, &lastChar);
//			return number;
//		}

}


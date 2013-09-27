#include "Game.h"
#include "tinyxml2.h"
#include <iostream>
namespace LOAD_XML{
    bool Init_XML_File(tinyxml2::XMLDocument& document, const string& fileName)
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
            string str(doc.FirstChildElement( Entity.c_str() )->FirstChildElement( Attribute.c_str() )->GetText());

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
   /* float LoadContentFloat(tinyxml2::XMLDocument& doc, const std::string& Entity, const std::string& Attribute)
        {
            std::string str( doc.FirstChildElement(Entity.c_str())->FirstChildElement(Attribute.c_str())->GetText() );

            std::size_t lastChar;
            float number;
            number = std::stof(str, &lastChar);
            return number;
        }*/
}

int main()
	{
    tinyxml2::XMLDocument doc;
    if(!LOAD_XML::Init_XML_File(doc, "config.xml"))
	{
		std::cout << "could not open Config-File. Terminate now."; 
		return 1; 
	}
    int height = LOAD_XML::LoadContentInt(doc, "WINDOW", "HEIGHT");
    float ratio = ((float)LOAD_XML::LoadContentInt(doc, "WINDOW", "RATIO")) / 9;

    //   1024   x  768 Window Resolution
    Game game( ( height * ratio ), height);
	if( game.Initialize() )
		{
		return game.Run();
		}
	return 1;
	}

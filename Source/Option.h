#ifndef OPTION_H
#define OPTION_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

enum class OptionName
{
    NEW,
    RESUME,
    OPTIONS,
    EXIT,
    SAVE,
    LOAD,
    BACK
};
class Option
{
public:
                            Option(OptionName option, sf::Vector2f pos, sf::Color color);
							~Option();
		sf::Text			mText;
		sf::Font			mFont;
		sf::Color			mColor;
		std::string			mString;
        OptionName          mOptionName;
		Option*				mpFront;
		Option*				mpNext;


		void				ConnectFront( Option* option );
		void				ConnectNext( Option* option );
		Option*				GoFront();
		Option*				GoNext();

};

#endif //OPTION_H

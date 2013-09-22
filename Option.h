#ifndef OPTION_H
#define OPTION_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

class Option
{
public:
							Option(std::string name, sf::Vector2f pos, sf::Color color); 
							~Option();
		sf::Text			mText; 
		sf::Font			mFont; 
		sf::Color			mColor; 
		std::string			mString;
		
		Option*				mpFront; 
		Option*				mpNext; 


		void				ConnectFront( Option* option );
		void				ConnectNext( Option* option );
		Option*				GoFront(); 
		Option*				GoNext();
	
	
	 
		
};

#endif //OPTION_H
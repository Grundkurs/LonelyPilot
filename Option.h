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
	sf::Text _text; 
	sf::Font _font; 
	sf::Color _color; 
	void ConnectFront( Option* option );
	void ConnectNext( Option* option );
	Option* GoFront(); 
	Option* GoNext();



	std::string _string; 
	
	Option* _front; 
	Option* _next; 
};

#endif //OPTION_H
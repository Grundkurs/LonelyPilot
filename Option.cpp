#include "Option.h"

Option::Option( std::string name, sf::Vector2f pos, sf::Color color ) : 
	_string( name ), 
	_front( nullptr ), 
	_next( nullptr ),
	_color( color )
{
	if( !_font.loadFromFile( "..\\Art\\Fonts\\Acme.ttf" ) )
	{
		std::cout << "could not load font!\n"; 
	}
	_text.setPosition( pos );
	_text.setFont( _font ); 
	_text.setColor( color ); 
	_text.setString( _string ); 
}




Option::~Option(){std::cout << "deleting: " << _string << std::endl; }



void Option::ConnectFront( Option* option )
{
	if( _front )
	{
		std::cout << "error, already connected to " << _front->_string << std::endl; 
		return; 
	}
	_front = option; 
}

void Option::ConnectNext( Option* option )
{
	if( _next )
	{
		std::cout << "error, already connected to " << _next->_string << std::endl; 
		return; 
	}
	_next = option; 
}


Option* Option::GoFront(){
	if( _front )
	{
		_color = sf::Color::Black;
		_text.setColor( _color ); 
		_front->_color = sf::Color::Red;
		_front->_text.setColor( _front->_color ); 
		return _front;
	}
	
	return nullptr; 
}
Option* Option::GoNext()
{
	if( _next )
	{
		_color = sf::Color::Black;
		_text.setColor( _color ); 
		_next->_color = sf::Color::Red;
		_next->_text.setColor( _next->_color ); 
		return _next;
	}
	
	return nullptr; 
}


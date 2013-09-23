#include "Option.h"

Option::Option( std::string name, sf::Vector2f pos, sf::Color color ) : 
	mColor( color ),
	mString( name ), 
	mpFront( nullptr ), 
	mpNext( nullptr )
	{
	if( !mFont.loadFromFile( "..\\Art\\Fonts\\Acme.ttf" ) )
		{
		std::cout << "could not load font!\n"; 
		}
	mText.setPosition( pos );
	mText.setFont( mFont ); 
	mText.setColor( mColor ); 
	mText.setString( mString ); 
	}




Option::~Option(){std::cout << "deleting: " << mString << std::endl; }



void Option::ConnectFront( Option* option )
	{
	if( mpFront )
		{
		std::cout << "error, already connected to " << mpFront->mString << std::endl; 
		return; 
		}
	mpFront = option; 
	}

void Option::ConnectNext( Option* option )
	{
	if( mpNext )
		{
		std::cout << "error, already connected to " << mpNext->mString << std::endl; 
		return; 
		}
	mpNext = option; 
	}


Option* Option::GoFront()
	{
	if( mpFront )
		{
		mColor = sf::Color::Black;
		mText.setColor( mColor ); 
		mpFront->mColor = sf::Color::Red;
		mpFront->mText.setColor( mpFront->mColor ); 
		return mpFront;
		}
	
	return nullptr; 
	}
Option* Option::GoNext()
	{
	if( mpNext )
		{
		mColor = sf::Color::Black;
		mText.setColor( mColor ); 
		mpNext->mColor = sf::Color::Red;
		mpNext->mText.setColor( mpNext->mColor ); 
		return mpNext;
		}
	
	return nullptr; 
	}


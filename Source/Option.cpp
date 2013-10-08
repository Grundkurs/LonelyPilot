#include "Option.h"
#include "StringUtilities.h"

Option::Option( OptionName option, sf::Vector2f pos, sf::Color color ) :
	mColor( color ),
    mOptionName( option),
	mpFront( nullptr ),
	mpNext( nullptr )
	{
	string file("..\\Resources\\Fonts\\Acme.ttf");

    if( !mFont.loadFromFile( ToPlatformPath(file) ) )
		{
		std::cout << "could not load font!\n";
		}
    switch (mOptionName)
    {
    case(OptionName::BACK):
        {
        mString = "Back";
        break;
        }
    case(OptionName::EXIT):
        {
        mString = "Exit";
        break;
        }
    case(OptionName::LOAD):
        {
        mString = "Load";
        break;
        }
    case(OptionName::NEW):
        {
        mString = "New";
        break;
        }
    case(OptionName::OPTIONS):
        {
        mString = "Options";
        break;
        }
    case(OptionName::RESUME):
        {
        mString = "Resume";
        break;
        }
    case(OptionName::SAVE):
        {
        mString = "Save";
        break;
        }
    default:
        mString = "Unknown Option";
        break;
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


#include "Background.h"
#include <iostream>

Background::Background( Game* pGame ) : mpGame( pGame )
	{
	}


Background::~Background()
	{
	std::cout << "destroying Background\n";
	}

void Background::Update( const sf::Time& deltaFrame )
	{

	}

void Background::SetTexture( const sf::Texture& tex )
	{
	mSprite.setTexture( tex );
	}


const sf::Sprite& Background::GetSprite() const
	{
	return mSprite;
	}

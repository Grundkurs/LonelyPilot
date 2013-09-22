#include "Player.h"
#include "Game.h"
#include <iostream>
class Game; 
Player::Player( Game* game ) 
	: mpGame( game ), 
	mSpriteWidth( 56 ),
	mSpriteHeight( 97 ),
	mCurrentRow( 0 ),
	mVelocity( sf::Vector2f(0.f, 0.f) )
{

	sf::IntRect rect( mCurrentRow, 0, mSpriteWidth, mSpriteHeight );
	mSprite.setTextureRect( rect );
	mSprite.setPosition( ( (mpGame->mWidth/2) - (mSpriteWidth/2)), ((mpGame->mHeight/2) - (mSpriteHeight/2) ) ); 

	//set current position-Variable to the one the sprite has been setted to. 
	mPos = mSprite.getPosition();
}


Player::~Player()
{
	std::cout << "destroying player\n"; 
}


void Player::Update( const sf::Time& deltaFrame )
{
	changeRect(0);
//---------------------------------------------------
	//basic controls
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
	{
		changeRect(1); 
		mVelocity.x -= 1105.5f * deltaFrame.asSeconds(); 
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
	{
		changeRect(2);
		mVelocity.x += 1105.5f * deltaFrame.asSeconds();
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
	{
		mVelocity.y -= 505.5f * deltaFrame.asSeconds();
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
	{
		mVelocity.y += 505.5f * deltaFrame.asSeconds();
	}

//--------------------------------------------------------------------------
	//limit MaxSpeed

	if( mVelocity.x > 400.f )
	{	
		mVelocity.x = 400.f; 
	}
	if( mVelocity.x < -400.f )
	{
		mVelocity.x = -400.f; 
	}

	if( mVelocity.y > 400.f )
	{
		mVelocity.y = 400.f; 
	}
	if( mVelocity.y < -400.f )
	{	
		mVelocity.y = -400.f; 
	}

	//--------------------------------------------------------------------------
	//boarder collision
	if( mPos.x < 0 )
	{
		mPos.x = 1; 
		//inverse direction and slow down when touching border
		mVelocity.x *= -0.5f; 
	}
	//if right side of ship is outside screen
	else if( ( mPos.x + mSpriteWidth ) > mpGame->mWidth )
	{
		mPos.x = ( mpGame->mWidth - mSpriteWidth ); 
		//inverse direction and slow down when touching border
		mVelocity.x *= -0.5f; 
	}
	//--------------------------------------------------------------------------

	mPos += mVelocity * deltaFrame.asSeconds(); 
	mSprite.setPosition( mPos ); 
}

void Player::SetTexture( const sf::Texture& tex )
{
	mSprite.setTexture( tex );
}
void Player::changeRect( int row )
{
	mCurrentRow = row; 
	mSprite.setTextureRect( sf::IntRect( mCurrentRow *mSpriteWidth,0,mSpriteWidth, mSpriteHeight ) );
} 


const sf::Sprite& Player::GetSprite() const
{
	return mSprite;
}
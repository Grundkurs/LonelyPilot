#include "Player.h"
#include "Game.h"

#include "VectorUtilities.h"

#include <iostream>

#include "SFML/System.hpp"

class Game;
Player::Player( Game* pGame, GameState* pGameState )
	:
	mpGame( pGame ),
    mpGameState(pGameState),
	mSpriteWidth( 56 ),
	mSpriteHeight( 97 ),
	mCurrentRow( 0 ),
    mCurrentColumn( 0 ),
	mTriggerShot(0.0f),
    mVelocity( sf::Vector2f(0.f, 0.f) ),
    mSpeed( mpGame->mConfig.GetPlayerSpeed() ),
    mCollisionBumper(mpGame->mConfig.GetPlayerCollisionBumper()),
    mMaxSpeed(mpGame->mConfig.GetPlayerMaxSpeed()),
    mDamageBoost(0)
	{

	sf::Vector2u size = pGame->mRenderWindow.getSize();
    sf::IntRect rect( mCurrentRow, mCurrentColumn, mSpriteWidth, mSpriteHeight );
	mSprite.setTextureRect( rect );
	mSprite.setPosition( ( (size.x/2) - (mSpriteWidth/2)), ((size.y/2) - (mSpriteHeight/2) ) );

	//set current position-Variable to the one the sprite has been setted to.
	mPos = mSprite.getPosition();
	}


Player::~Player()
	{
	std::cout << "destroying player\n";
	}


void Player::Update( const sf::Time& deltaFrame )
	{
    mCurrentRow = 0;
    mCurrentColumn = 0;
//---------------------------------------------------
	//basic controls
	bool controlsMoving = false;

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
		{
        mCurrentRow = 1;
		mVelocity.x -= mSpeed.x * deltaFrame.asSeconds();
		controlsMoving = true;
		}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
		{
        mCurrentRow = 2;
		mVelocity.x += mSpeed.x * deltaFrame.asSeconds();
		controlsMoving = true;
		}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
		{
		mVelocity.y -= mSpeed.y * deltaFrame.asSeconds();
		controlsMoving = true;
		}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
		{
		mVelocity.y += mSpeed.y * deltaFrame.asSeconds();
		controlsMoving = true;
		}

	// fire lasers
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ))
        {
        mCurrentColumn = 1;
        if(mTriggerShot < mpGame->mFrameStamp.asSeconds())
            {
            mCurrentColumn = 0;  //causes shooting-fire flickering
            sf::Vector2f playerPos( mSprite.getPosition() );
            mpGame->mAudioMan.PlaySound(AudioGroups::AUDIO_LASER, sf::Vector3f(playerPos.x,playerPos.y,0.0f), 15.0f, 1.0f);
            mTriggerShot = mpGame->mFrameStamp.asSeconds() + 0.25f;
            mpGameState->ShootLaser(true,mDamageBoost);
            mpGameState->ShootLaser(false,mDamageBoost);

            }
        }

//--------------------------------------------------------------------------
	//limit MaxSpeed

    if( mVelocity.x > mMaxSpeed )
		{
        mVelocity.x = mMaxSpeed;
		}
    if( mVelocity.x < -mMaxSpeed )
		{
        mVelocity.x = -mMaxSpeed;
		}

    if( mVelocity.y > mMaxSpeed )
		{
        mVelocity.y = mMaxSpeed;
		}
    if( mVelocity.y < -mMaxSpeed)
		{
        mVelocity.y = -mMaxSpeed;
		}

	//--------------------------------------------------------------------------
	//boarder collision
	sf::Vector2u size = mpGame->mRenderWindow.getSize();
	mPos = ( mSprite.getPosition() );
	if( mPos.x < 0 )
		{
		mPos.x = 1;
		//inverse direction and slow down when touching border
        mVelocity.x *= -mCollisionBumper;
		}
	//if right side of ship is outside screen
	else if( ( mPos.x + mSpriteWidth ) > size.x )
		{
		mPos.x = ( size.x - mSpriteWidth );
		//inverse direction and slow down when touching border
        mVelocity.x *= -mCollisionBumper;
		}

	if ( mPos.y < 1 )
		{
		mPos.y = 1;
		mSprite.setPosition( mPos );
        mVelocity.y *= -mCollisionBumper;
		}
	else if ( ( mPos.y + mSpriteHeight ) > size.y )
		{
		mPos.y = ( size.y - mSpriteHeight );
        mVelocity.y *= -mCollisionBumper;
		mSprite.setPosition( mPos );
		}
	//--------------------------------------------------------------------------
	// Inertia
	if ( !controlsMoving )
		{
		mVelocity += Inertia( mVelocity, 100.0f, deltaFrame.asSeconds() );
		}

	mPos += mVelocity * deltaFrame.asSeconds();
	mSprite.setPosition( mPos );

    mSprite.setTextureRect( sf::IntRect( mCurrentRow * mSpriteWidth,mCurrentColumn * mSpriteHeight,mSpriteWidth, mSpriteHeight ) );
	}

void Player::SetTexture( const sf::Texture& tex )
	{
	mSprite.setTexture( tex );
	}


const sf::Sprite& Player::GetSprite() const
	{
	return mSprite;
	}

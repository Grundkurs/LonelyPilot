#include "Player.h"
#include "Game.h"

#include "VectorUtilities.h"

#include <iostream>

#include "SFML/System.hpp"

class Game;
Player::Player( Game* pGame )
    :
    mpGame( pGame ),
    mSpriteWidth( 56 ),
    mSpriteHeight( 97 ),
    mCurrentRow( 0 ),
    mTriggerShot(0.0f),
    mVelocity( sf::Vector2f(0.f, 0.f) ),
    mSpeed( sf::Vector2f (1105.f, 505.5f ) )
    {
    sf::Vector2u size = pGame->mRenderWindow.getSize();
    sf::IntRect rect( mCurrentRow, 0, mSpriteWidth, mSpriteHeight );
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
    changeRect(0);
//---------------------------------------------------
    //basic controls
    bool controlsMoving = false;

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
        {
        changeRect(1);
        mVelocity.x -= mSpeed.x * deltaFrame.asSeconds();
        controlsMoving = true;
        }

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
        {
        changeRect(2);
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
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && mTriggerShot < mpGame->mFrameStamp.asSeconds())
        {
        sf::Vector2f playerPos( mSprite.getPosition() );
        mpGame->mAudioMan.PlaySound(AudioGroups::AUDIO_LASER, sf::Vector3f(playerPos.x,playerPos.y,0.0f), 15.0f, 1.0f);
        mTriggerShot = mpGame->mFrameStamp.asSeconds() + 0.25f;
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
    sf::Vector2u size = mpGame->mRenderWindow.getSize();
    mPos = ( mSprite.getPosition() );
    if( mPos.x < 0 )
        {
        mPos.x = 1;
        //inverse direction and slow down when touching border
        mVelocity.x *= -0.5f;
        }
    //if right side of ship is outside screen
    else if( ( mPos.x + mSpriteWidth ) > size.x )
        {
        mPos.x = ( size.x - mSpriteWidth );
        //inverse direction and slow down when touching border
        mVelocity.x *= -0.5f;
        }

    if ( mPos.y < 1 )
        {
        mPos.y = 1;
        mSprite.setPosition( mPos );
        mVelocity.y *= -0.5f;
        }
    else if ( ( mPos.y + mSpriteHeight ) > size.y )
        {
        mPos.y = ( size.y - mSpriteHeight );
        mVelocity.y *= -0.5f;
        mSprite.setPosition( mPos );
        }
    //--------------------------------------------------------------------------


    mPos += mVelocity * deltaFrame.asSeconds();

    if ( !controlsMoving )
        {
        // NOTE: you could make seperate slow down rates for x and y
        static float slowDownRate = 150.0f;
        sf::Vector2f oppositeDir( -mVelocity );
        Normalize(oppositeDir);

        oppositeDir *= (slowDownRate * deltaFrame.asSeconds());

        if ( abs( mVelocity.x ) <= abs(oppositeDir.x ) )
            {
            mVelocity.x = 0.0f;
            oppositeDir.x = 0.0f;
            }
        if ( abs( mVelocity.y ) <= abs(oppositeDir.y ) )
            {
            mVelocity.y = 0.0f;
            oppositeDir.y = 0.0f;
            }
        mVelocity += oppositeDir;
        }
    mSprite.setPosition( mPos );
    }

void Player::SetTexture( const sf::Texture& tex )
    {
    mSprite.setTexture( tex );
    }

void Player::changeRect( int row )
    {
    mCurrentRow = row;
    mSprite.setTextureRect( sf::IntRect( mCurrentRow * mSpriteWidth,0,mSpriteWidth, mSpriteHeight ) );
    }

const sf::Sprite& Player::GetSprite() const
    {
    return mSprite;
    }

#include "Star.h"
#include <iostream>
#include "Game.h"
#include "Baldus.h"
#include <math.h>
class Game;



Star::Star( Game * pGame, std::shared_ptr<Player>player )
    :
    mpGame( pGame ),
    mPlayer( player ),
    mPos( sf::Vector2f(0.f, 0.f) ),
    mSpeedEnhancment( 1.0 )
    {

    sf::Vector2u size = mpGame->mRenderWindow.getSize();

    float xPos = mpGame->mRandomNumGenerator.getRandomInt( size.x + 30 );
    float yPos = mpGame->mRandomNumGenerator.getRandomInt( size.y + 400 );
    mSprite.setPosition( xPos, yPos );
    mPos.x = xPos;
    mPos.y = yPos;


    //makes the stars at the borders faster, which looks nicer
    if( mPos.x < 100 || mPos.x > 900 )
        {
        mSpeedEnhancment = 1.5f;
        }
    mDirection.x = 0;
    mDirection.y = ( (mPos.y /8) * mSpeedEnhancment);
    SetRandomColorAndSize( mpGame->mRandomNumGenerator );

    }

Star::Star(Game* pGame, std::shared_ptr<Player> player, sf::Vector2f position)
  : mpGame( pGame ),
    mPlayer( player ),
    mPos( sf::Vector2f(0.f, 0.f) ),
    mSpeedEnhancment( 1.0 )

{
    mSprite.setPosition(position);
}
Star::~Star()
    {
    std::cout << "destroying Star\n";
    }


void Star::Update( const sf::Time& deltaFrame )
    {
    sf::Vector2f newPos = mSprite.getPosition();
    sf::Vector2u size = mpGame->mRenderWindow.getSize();

    //bind star-movement to player-speed
    newPos.y += ( -mPlayer->mVelocity.y) * deltaFrame.asSeconds();
    newPos.x += ( -mPlayer->mVelocity.x) * deltaFrame.asSeconds() * 0.2f; //x-movement of stars 5x slower than y-movement

    //CPU-Speed independend star-movement           
	newPos += mDirection * deltaFrame.asSeconds() * mSpeedEnhancment;
	
	
	
    //offset of 20 pixels at top and bottom (788 instead of 768 for bottom and -20 instead of 0 for top)
    if( newPos.y > ( size.y + 400 ) )
        {
        newPos.y = -40.f;
        }

    mSprite.setPosition( newPos );

    }

void Star::SetTexture( const sf::Texture& tex )
    {
    mSprite.setTexture( tex );
    }


void Star::SetRandomColorAndSize( RandomNumberGenerator& random )
    {
    //TODO: Write propper and index ranged random-Generator, like getRandomInt(int, int) instead getRandomInt(int)) to make sure 0 doesnt get returned
    int divisor = mpGame->mRandomNumGenerator.getRandomInt(6);
    int number = mpGame->mRandomNumGenerator.getRandomInt(5);

    if( divisor == 0 )
        {
        divisor = 3;
        }

    //TODO: Improve scale calculation
    float scale = ( number / divisor );
    if( scale > 0.5f )
        {
        scale = 0.5f;
        }
    if ( scale  < 0.1f )
        {
        scale = .3f;
        }
    mSprite.setScale( scale, scale );


    //Color
    switch( number )
        {
        case ( 0 ):{
            mSprite.setColor(sf::Color(240,0,0));

                 break;
                 }
        case ( 1 ):{
            mSprite.setColor(sf::Color::Red);

                 break;
                 }
        case ( 2 ):{
            mSprite.setColor(sf::Color::Magenta);

                break;
                 }
        case ( 3 ):{
            mSprite.setColor(sf::Color::Blue);

                break;
                 }
        case ( 4 ):{
            mSprite.setColor(sf::Color::Red);

                 break;
                 }
        default:{
            mSprite.setColor(sf::Color::Magenta);
                break;
                }
        }

    }

const sf::Sprite& Star::GetSprite() const
    {
    return mSprite;
    }

void Star::SetRandomDirection(const sf::Vector2f baldusPos)
	{
	/*
	//center of explosion-circle should be position of exploding enemy
	sf::Vector2f center(baldusPos);
	center.x += 50.f; 
	center.y += 50.f;
	mSprite.setPosition(center);
	
	double angleX = Random::Between(0, 360);
	double angleY = Random::Between(0, 360);

	
	int even = mpGame->mRandomNumGenerator.getRandomInt(2);
	mDirection.x = Random::Between(20, 170);
	mDirection.y = Random::Between(30, 160);
	
	int even = Random::Between(0, 50);
	if (even % 2 == 0)
		{
		mDirection.x *= -1;
		mDirection.y *= -1; 
		} 
	*/
	}
void Star::SetColor(sf::Color color)
	{
	mSprite.setColor(color);
	}

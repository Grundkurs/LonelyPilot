#include "Star.h"
#include <iostream>
#include "Game.h"
class Game; 


Star::Star( Game* game, std::shared_ptr<Player>player ) : _game( game ), _player( player )
{
}

Star::Star( Game* game, RandomNumberGenerator& random, std::shared_ptr<Player>player ) 
	:	
	_game( game ),
	mPos( sf::Vector2f(0.f, 0.f) ),
	mSpeedEnhancment( 1.0 ),
	_player( player )
{

	float xPos = random.getRandomInt( _game->_width + 30 );
	float yPos = random.getRandomInt( _game->_height + 400 );
	mSprite.setPosition( xPos, yPos );
	mPos.x = xPos; 
	mPos.y = yPos; 
    

    //makes the stars at the borders faster, which looks nicer
    if( mPos.x < 100 || mPos.x > 900 )
	{
        mSpeedEnhancment = 1.5f;
    }
    mSpeed.x = 0;
    mSpeed.y = ( (mPos.y /10) * mSpeedEnhancment);
    SetRandomColorAndSize( random );

}


Star::~Star()
{
	std::cout << "destroying Star\n"; 
}


void Star::Update( const sf::Time& deltaFrame )
{
	sf::Vector2f newPos = mSprite.getPosition();

	//bind star-movement to player-speed
	newPos.y += ( -_player->_velocity.y) * deltaFrame.asSeconds();
	newPos.x += ( -_player->_velocity.x) * deltaFrame.asSeconds() * 0.2f; //x-movement of stars 5x slower than y-movement

	//independend star-movement
	newPos += mSpeed * deltaFrame.asSeconds();

	//offset of 20 pixels at top and bottom (788 instead of 768 for bottom and -20 instead of 0 for top)
    if( newPos.y > ( _game->_height + 400 ) ){
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
	int divisor = random.getRandomInt(6);
	int number = random.getRandomInt(5);
	 
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
    if ( scale  == 0.f )
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

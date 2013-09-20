#include "Star.h"
#include <iostream>
#include "Game.h"
class Game; 


Star::Star(Game* game, std::shared_ptr<Player>player) : _game(game), _player(player){
}

Star::Star(Game* game, sf::Vector2f position,RandomNumberGenerator& random, std::shared_ptr<Player>player) 
	:	_game(game),
		mPos(position),
		mSpeedEnhancment(1.0),
		_player(player)
{

	float yPos = random.getRandomInt(_game->_height); 
    _sprite.setPosition(mPos.x, yPos);

    //makes the stars at the borders faster, which looks nicer
    if(position.x < 100 || position.x > 900){
        mSpeedEnhancment = 1.5f;
    }
    mSpeed.x = 0;
    mSpeed.y = ((position.y /10) * mSpeedEnhancment);
    SetRandomColorAndSize(random);

}


Star::~Star()
{
	std::cout << "destroying Star\n"; 
}


void Star::Update(const sf::Time& deltaFrame){
	sf::Vector2f newPos = _sprite.getPosition();

	//bind star-movement to player-speed
	newPos.y += (-_player->_velocity.y) * deltaFrame.asSeconds();
	newPos.x += (-_player->_velocity.x) * deltaFrame.asSeconds() * 0.2f; //x-movement of stars 5x slower than y-movement

	//independend star-movement
	newPos += mSpeed * deltaFrame.asSeconds();

	//offset of 20 pixels at top and bottom (788 instead of 768 for bottom and -20 instead of 0 for top)
    if(newPos.y > 788){
        newPos.y = -20;
    }

    _sprite.setPosition(newPos);

}

void Star::SetTexture(const sf::Texture& tex){
	_sprite.setTexture(tex); 
}


void Star::SetRandomColorAndSize(RandomNumberGenerator& random){
	
	//TODO: Write propper and index ranged random-Generator, like getRandomInt(int, int) instead getRandomInt(int)) to make sure 0 doesnt get returned
 
	int divisor = random.getRandomInt(6);
	int number = random.getRandomInt(5);
	 
    if(divisor == 0){
    divisor = 3;
    }
    
	//TODO: Improve scale calculation
	float scale = (number / divisor);
    if(scale > 0.5f){
    scale = 0.5f;
    }
    if (scale  == 0.f){
	scale = .3f;
	}
    _sprite.setScale(scale, scale);


    //Color

    
    switch(number){
    case (0):{
		_sprite.setColor(sf::Color::Yellow);
		
             break;
             }
    case (1):{
		_sprite.setColor(sf::Color::Cyan);
		
             break;
             }
    case (2):{
		_sprite.setColor(sf::Color::Green);
		
            break;
             }
    case (3):{
		_sprite.setColor(sf::Color::Blue);
		
            break;
             }
    case (4):{
        _sprite.setColor(sf::Color::Red);
		
             break;
             }
    default:{
		_sprite.setColor(sf::Color::Magenta);
            break;
            }
    }

}

const sf::Sprite& Star::GetSprite() const {

	return _sprite;

}
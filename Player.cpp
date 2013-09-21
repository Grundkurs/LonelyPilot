#include "Player.h"
#include "Game.h"
#include <iostream>
class Game; 
Player::Player(Game* game) 
	: _game(game), 
_spriteWidth(56),
_spriteHeight(97),
_currentRow(0),
_velocity(sf::Vector2f(0.f, 0.f)){

sf::IntRect rect(_currentRow, 0, _spriteWidth, _spriteHeight);
_sprite.setTextureRect(rect);
_sprite.setPosition(((_game->_width/2) - (_spriteWidth/2)), ((_game->_height/2) - (_spriteHeight/2))); 

//set current position-Variable to the one the sprite has been setted to. 
_pos = _sprite.getPosition();
}


Player::~Player()
{
std::cout << "destroying player\n"; 
}


void Player::Update(const sf::Time& deltaFrame){
	changeRect(0);
//---------------------------------------------------
	//basic controls
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		changeRect(1); 
		_velocity.x -= 1105.5f * deltaFrame.asSeconds(); 
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		changeRect(2);
		_velocity.x += 1105.5f * deltaFrame.asSeconds();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		
		_velocity.y -= 505.5f * deltaFrame.asSeconds();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		
		_velocity.y += 505.5f * deltaFrame.asSeconds();
	}

//--------------------------------------------------------------------------
	//limit MaxSpeed

	if(_velocity.x > 400.f){
		
		_velocity.x = 400.f; 
	}
	if(_velocity.x < -400.f){
		
		_velocity.x = -400.f; 
	}

	if(_velocity.y > 400.f){
		
		_velocity.y = 400.f; 
	}
	if(_velocity.y < -400.f){
		
		_velocity.y = -400.f; 
	}

	//--------------------------------------------------------------------------
	//boarder collision
	if(_pos.x < 0){
		_pos.x = 1; 
		//inverse direction and slow down when touching border
		_velocity.x *= -0.5f; 
	}
	//if right side of ship is outside screen
	else if((_pos.x + _spriteWidth) > _game->_width){
		_pos.x = (_game->_width - _spriteWidth); 
		//inverse direction and slow down when touching border
		_velocity.x *= -0.5f; 
	}
	//--------------------------------------------------------------------------

	_pos += _velocity * deltaFrame.asSeconds(); 
	_sprite.setPosition(_pos); 
}

void Player::SetTexture(const sf::Texture& tex){
_sprite.setTexture(tex);
}
void Player::changeRect(int row){
	_currentRow = row; 
	_sprite.setTextureRect(sf::IntRect(_currentRow *_spriteWidth,0,_spriteWidth, _spriteHeight));
} 


const sf::Sprite& Player::GetSprite() const{

	return _sprite;

}
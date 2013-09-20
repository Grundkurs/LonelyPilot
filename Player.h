#ifndef PLAYER_H
#define PLAYER_H

#include "IEntity.h"
class Game;

class Player :
	public IEntity
{

	Game* _game;
	sf::Vector2f _pos;
	sf::Sprite _sprite;

	 
	sf::IntRect spriteRect; //56 x 97
	const int _spriteHeight; 
	const int _spriteWidth; 
	int _currentRow;

	void changeRect(int row); 

public:
	Player(Game* game);
	~Player();


	void SetTexture(const sf::Texture& tex);
	void Update(const sf::Time& deltaFrame);
	const sf::Sprite& GetSprite() const; 
	

	//public fields
	sf::Vector2f _velocity;


};
#endif //PLAYER_H

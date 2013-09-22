#pragma once
#include "iEntity.h"
class Game; 
class Background :
	public IEntity
{

		Game*					mpGame;
		sf::Vector2f			mPos;
		sf::Sprite				mSprite;
public:
								Background(Game* game);
								~Background();
		void					Update(const sf::Time& deltaFrame);
		void					SetTexture(const sf::Texture& tex);
const	sf::Sprite&				GetSprite() const; 

};


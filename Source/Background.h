#pragma once
#include "IEntity.h"
class Game;
class Background :
	public IEntity
{

		Game*					mpGame;
		sf::Vector2f			mPos;
		sf::Sprite				mSprite;
public:
								Background(Game * pGame);
								~Background();
		void					Update(const sf::Time& deltaFrame);
		void					SetTexture(const sf::Texture& tex);
const	sf::Sprite&				GetSprite() const;

};


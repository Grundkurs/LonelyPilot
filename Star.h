#pragma once
#include "IEntity.h"
#include "RandomNumberGenerator.h"
#include "Player.h"
#include <memory>

class Star :
	public IEntity
{
	
		sf::Sprite					mSprite;
		Game*						mpGame;
		std::shared_ptr<Player>		mPlayer; 
		sf::Vector2f				mPos;
		sf::Vector2f				mSpeed;
	    float						mSpeedEnhancment;
	 

		void						SetRandomColorAndSize(RandomNumberGenerator& random);

public:
									Star(Game* game, std::shared_ptr<Player> player);
									~Star();
						
		void						Update(const sf::Time& deltaFrame); 
		void						SetTexture(const sf::Texture& tex);
const	sf::Sprite&					GetSprite() const;
};


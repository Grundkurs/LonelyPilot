#ifndef AMBULANCE_H
#define AMBULANCE_H
#pragma once

class Game; 
class Player; 
#include "IEntity.h"
class Ambulance : public IEntity
{
		Player*						mpPlayer;
		Game*						mpGame;
		sf::Vector2f				mPos;
		sf::Sprite					mSprite;
		sf::IntRect					mSpriteRect;
		int							mWidth, mHeight;
		int							mCurrentFrame; 
		int							mTotalColumn; 
		float						mFrameCounter; 
		float						mMaxFrame; 
public:
									Ambulance(Game* game, Player* player);
									~Ambulance();

		void						Update(const sf::Time& deltaFrame); 
		void						SetTexture(const sf::Texture& tex);
const	sf::Sprite&					GetSprite() const; 
};

#endif //AMBULANCE_H
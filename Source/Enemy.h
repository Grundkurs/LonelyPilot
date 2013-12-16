#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "IEntity.h"

class Player;
class Enemy : public IEntity
{
public:
	Enemy(int width, int height);
	~Enemy();

			Game *						mpGame;
			Player*						mpPlayer;
			sf::Vector2f				mPos;
			sf::Sprite					mSprite;
			sf::IntRect					mSpriteRect;
	const 	int							mWidth;
	const 	int 						mHeight;
			int							mCurrentColumn;
			int                         mCurrentRow;
			int							mHealth;
			bool						misAlive;
            bool                        mcanBeHit;
			bool						misShutDown;

			float						mFrameRate;
			float						mVelocity;
			float						mFrameCounter;
public:

virtual		bool						isAlive() = 0;
virtual		bool						shutDown() = 0; 
virtual		void						Update(const sf::Time& deltaFrame) = 0;
virtual		void						SetTexture(const sf::Texture& tex) = 0;
virtual		void						Animation(const sf::Time& deltaFrame) = 0;
virtual		void						Movement(const sf::Time& deltaFrame) = 0;
virtual		void						HitPoint(int damageRate) = 0;
virtual	const	sf::Sprite&				GetSprite() const = 0;

};


#endif //ENEMY_H

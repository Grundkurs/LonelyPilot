#ifndef PLAYER_H
#define PLAYER_H

#include "IEntity.h"
class Game;

class Player : public IEntity
{
friend class GameState; // TODO: hack to be able to grap mPos from GameState
		Game*					mpGame;
		sf::Vector2f			mPos;
		sf::Sprite				mSprite;


		sf::IntRect				spriteRect; //56 x 97
		const	int				mSpriteHeight;
		const	int				mSpriteWidth;
		int						mCurrentRow;

		void					changeRect(int row);
		float					mTriggerShot;

public:
								Player(Game* game);
								~Player();


		void					SetTexture(const sf::Texture& tex);
		void					Update(const sf::Time& deltaFrame);
		const	sf::Sprite&		GetSprite() const;


	//public fields
	sf::Vector2f				mVelocity;
    sf::Vector2f                mSpeed;


};
#endif //PLAYER_H

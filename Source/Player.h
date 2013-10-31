#ifndef PLAYER_H
#define PLAYER_H

#include "IEntity.h"
class Game;
class GameState;


enum class Weapon	
	{
	Blue, 
	Green,
	Purple,
	Red
	};

class Player : public IEntity
{
friend class GameState; // TODO: hack to be able to grap mPos from GameState
        Game*					mpGame;
        GameState*              mpGameState;
        sf::Vector2f			mPos;
        sf::Sprite				mSprite;


        sf::IntRect				spriteRect; //56 x 97
        const	int				mSpriteWidth;
        const	int				mSpriteHeight;

        int						mCurrentRow;
        int                     mCurrentColumn;
        float					mTriggerShot;
        float                   mCollisionBumper;
        float                   mMaxSpeed;
        int                     mDamageBoost;
		Weapon					mCurrentWeapon;


public:
                                Player(Game* pGame, GameState* pGameState);
                                ~Player();

inline  int						getDamageBoost(){ return mDamageBoost; }
        void					SetTexture(const sf::Texture& tex);
        void					Update(const sf::Time& deltaFrame);
        const	sf::Sprite&		GetSprite() const;
        void                    SwitchDamageBoost(int choice);


    //public fields
    sf::Vector2f				mVelocity;
    sf::Vector2f                mSpeed;


};
#endif //PLAYER_H

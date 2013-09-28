#ifndef AMBULANCE_H
#define AMBULANCE_H
#pragma once

class Game;
class Player;
#include "IEntity.h"
class Ambulance : public IEntity
{
        Game *						mpGame;
        Player*						mpPlayer;
        sf::Vector2f				mPos;
        sf::Sprite					mSprite;
        sf::IntRect					mSpriteRect;
const 	int							mWidth;
const 	int 						mHeight;
        int							mCurrentFrame;
        int							mTotalColumn;

        float						mFrameRate;
        float						mVelocity;
        float						mFrameCounter;
public:
                                    Ambulance(Game * pGame, Player * pPlayer);
                                    ~Ambulance();

        void						Update(const sf::Time& deltaFrame);
        void						SetTexture(const sf::Texture& tex);
        void						Animation(const sf::Time& deltaFrame);
        void						Movement(const sf::Time& deltaFrame);
const	sf::Sprite&					GetSprite() const;
};

#endif //AMBULANCE_H

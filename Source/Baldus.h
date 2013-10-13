#ifndef BALDUS_H
#define BALDUS_H
#include "IEntity.h"
class Game;
class Player;



class Baldus
{
        Game *						mpGame;
        Player*						mpPlayer;
        sf::Vector2f				mPos;
        sf::Sprite					mSprite;
        sf::IntRect					mSpriteRect;
const 	int							mWidth;
const 	int 						mHeight;
        int							mCurrentColumn;
        int                         mCurrentRow;


        float						mFrameRate;
        float						mVelocity;
        float						mFrameCounter;
public:
                                    Baldus(Game * pGame, Player * pPlayer);
                                    ~Baldus();

        void						Update(const sf::Time& deltaFrame);
        void						SetTexture(const sf::Texture& tex);
        void						Animation(const sf::Time& deltaFrame);
        void						Movement(const sf::Time& deltaFrame);
const	sf::Sprite&					GetSprite() const;

};

#endif // BALDUS_H

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "IState.h"
#include "Game.h"
#include "IEntity.h"
#include "Star.h"
#include "RandomNumberGenerator.h"
#include <memory>
#include "Player.h"
#include "Background.h"
#include "Ambulance.h"
#include "Laser.h"
#include "Baldus.h"

class Game;
class ExplosionParticle;

typedef std::shared_ptr<IEntity> sptr_Entity;


class GameState : public IState
{
    Game*                           mpGame;
    bool                            mResumedGame;

    std::vector<sptr_Entity>        entities;
    std::vector<Laser>              laserShots;
	std::vector<ExplosionParticle>	explosion; 

    std::shared_ptr<Player>         mPlayer;
    std::shared_ptr<Ambulance>      mAmbulance;
    std::shared_ptr<Baldus>         mBaldus;
    std::unique_ptr<Background>     mBackground;
const   State                       mState;
int									mExplosionParticles;
bool								isBaldusExplosionFinished;



public:
                                    GameState( Game* pGame);
                                    ~GameState();
const   State                       GetStateInput();
		Baldus*						GetBaldus(); 
		sf::Vector2f				baldusLastPosition;
        void                        Update(const sf::Time& deltaFrame);
        void                        Render();
        void                        SetResumeProperty(bool resume);
        void                        ShootLaser(bool leftSide, Weapon weapon);
        void                        CleanUpLaser(std::vector<Laser>& laserShots);
		void						CreateExplosion();
};


#endif //GAMESTATE_H

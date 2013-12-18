#ifndef EXPLOSION_PARTICLE_H
#define EXPLOSION_PARTICLE_H
#include "Star.h"

class GameState; 
class ExplosionParticle : public Star
{
public:
	ExplosionParticle(Game* pGame, GameState* state,  std::shared_ptr<Player> player);
						~ExplosionParticle();

			bool		isExploding;
virtual		void		Update(const sf::Time& deltaFrame);
			void		SetRandomDirection(sf::Vector2f origin);
private:
			GameState*	mpGameState; 
			sf::Vector2f mSize; 
			void ResetSettings();
			
};


#endif //EXPLOSION_PARTICLE_H


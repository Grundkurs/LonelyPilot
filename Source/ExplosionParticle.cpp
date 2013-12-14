#include "ExplosionParticle.h"
#include "Game.h"

ExplosionParticle::ExplosionParticle(Game* pGame, GameState* state, std::shared_ptr<Player> player)
: Star{ pGame, player, sf::Vector2f(0.f,0.f) },
isExploding{false},
mpGameState{state}
	{
	}


ExplosionParticle::~ExplosionParticle()
{
}



void ExplosionParticle::Update(const sf::Time& deltaFrame)
	{
	if (isExploding) Star::Update(deltaFrame);

	}
void ExplosionParticle::SetRandomDirection(sf::Vector2f origin)
	{
		isExploding = true; 
		sf::Vector2f newPos(origin);
		newPos.x += 50.f;
		newPos.y += 50.f;
		mSprite.setPosition(newPos);


		int even = mpGame->mRandomNumGenerator.getRandomInt(2);
		mDirection.x = Random::Between(20, 170);
		mDirection.y = Random::Between(30, 160);

		if (even % 2 == 0)
		{
			mDirection.x *= -1;
			mDirection.y *= -1;
		}

	
	}
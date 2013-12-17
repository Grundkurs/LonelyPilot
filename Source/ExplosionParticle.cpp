#include "ExplosionParticle.h"
#include "Game.h"

ExplosionParticle::ExplosionParticle(Game* pGame, GameState* state, std::shared_ptr<Player> player)
    : Star (pGame, player,sf::Vector2f(-8.f,-8.f) ),
isExploding(false),
mpGameState(state)
	{
	mSpeedEnhancment = 4.f;
	}


ExplosionParticle::~ExplosionParticle()
{
}



void ExplosionParticle::Update(const sf::Time& deltaFrame)
{
	if (isExploding) Star::Update(deltaFrame);

	//if Particle outside Screen, disable movement and put outside screen
	sf::Vector2u size = mpGame->mRenderWindow.getSize();
	sf::Vector2f currPos = mSprite.getPosition();
	if (currPos.x < 0 || currPos.y > size.y) 
		{
		isExploding = false; 
		mSprite.setPosition(sf::Vector2f(-3.f, -3.f));
		}


	}
void ExplosionParticle::SetRandomDirection(sf::Vector2f enemyPos)
	{
	isExploding = true; 
	sf::Vector2f center(enemyPos);
	center.x += 50.f;
	center.y += 50.f;
	mSprite.setPosition(enemyPos);

	float angleX = Random::Between(-360, 360);
	float angleY = Random::Between(-360, 360);

	mDirection.x = angleX;
	mDirection.y = angleY;


	
	}

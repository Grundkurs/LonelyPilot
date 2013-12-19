#include "ExplosionParticle.h"
#include "Game.h"

ExplosionParticle::ExplosionParticle(Game* pGame, GameState* state, std::shared_ptr<Player> player)
    : Star (pGame, player,sf::Vector2f(-8.f,-8.f) ),
isExploding(false),
mpGameState(state),
mSize(sf::Vector2f(1.f,1.f))
	{
	mSpeedEnhancment = 1.5f;
	mSprite.setPosition(sf::Vector2f(-3.f, -3.f));
	mSprite.setScale(mSize);
	}


ExplosionParticle::~ExplosionParticle()
{
}



void ExplosionParticle::Update(const sf::Time& deltaFrame)
{
	if (isExploding)
		{
		Star::Update(deltaFrame);

		float shrinkFactor = 1.2f;
		mSize.x -= shrinkFactor * deltaFrame.asSeconds();
		mSize.y -= shrinkFactor * deltaFrame.asSeconds();
		mSprite.setScale(mSize);
		}

	//if Stars invisible, reset default position and size 
	if (mSprite.getScale().x <= 0) ResetSettings();

}

	
void ExplosionParticle::SetRandomDirection(sf::Vector2f enemyPos)
	{
	isExploding = true; 
	sf::Vector2f center(enemyPos);
	center.x += (mpGameState->GetBaldus()->GetSprite().getGlobalBounds().width / 2 );
	center.y += (mpGameState->GetBaldus()->GetSprite().getGlobalBounds().height / 2);
	mSprite.setPosition(center);

	float angleX = Random::Between(-360, 360);
	float angleY = Random::Between(-360, 360);

	mDirection.x = angleX;
	mDirection.y = angleY;

	
	
	}

void ExplosionParticle::ResetSettings()
	{
	isExploding = false;
	mSprite.setPosition(sf::Vector2f(-3.f, -3.f));
	mSize = sf::Vector2f(1.f, 1.f);
	}
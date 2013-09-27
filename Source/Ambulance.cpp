#include "Ambulance.h"
#include "Game.h"
#include "Player.h"

Ambulance::Ambulance(Game * pGame, Player * pPlayer)
	:
	mpGame(pGame),
	mpPlayer(pPlayer),
	mVelocity(50.f),
	mWidth(85),
	mHeight(107),
	mFrameCounter(0.f),
	mMaxFrame(.33f),
	mCurrentFrame(0)
	{
	mSpriteRect.width = mWidth;
	mSpriteRect.height = mHeight;
	mSprite.setPosition(sf::Vector2f(100.f, 100.f));
	}


Ambulance::~Ambulance()
	{
		std::cout << "deleting Ambulance\n";
	}




void Ambulance::Update(const sf::Time& deltaFrame)
	{
		Animation(deltaFrame);
		Movement(deltaFrame);

}

void Ambulance::SetTexture(const sf::Texture& tex)
	{
		mSprite.setTexture(tex);
	}
const sf::Sprite& Ambulance::GetSprite() const
	{
		return mSprite;
	}






void Ambulance::Movement(const sf::Time& deltaFrame)
	{
	sf::Vector2f newPos = mSprite.getPosition();

	newPos.y += (mVelocity * deltaFrame.asSeconds());

	//bind star-movement to player-speed
	newPos.y += ( -mpPlayer->mVelocity.y) * deltaFrame.asSeconds();
	newPos.x += ( -mpPlayer->mVelocity.x) * deltaFrame.asSeconds() * 0.2f; //x-movement of stars 5x slower than y-movement

	mSprite.setPosition(newPos);
	}

void Ambulance::Animation(const sf::Time& deltaFrame)
	{
		//Animation related
		//------------------------------------------
		mFrameCounter += deltaFrame.asSeconds();

		if(mFrameCounter > mMaxFrame)
			{
				mCurrentFrame++;
				if(mCurrentFrame > 3)
					{
						mCurrentFrame = 0;
					}
				mFrameCounter = 0;
			}
		mSprite.setTextureRect(sf::IntRect(mCurrentFrame * mWidth, 0, mWidth, mHeight));

	}

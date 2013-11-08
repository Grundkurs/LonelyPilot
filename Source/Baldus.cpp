#include "Baldus.h"
#include "Game.h"
#include "Player.h"

Baldus::Baldus(Game * pGame, Player * pPlayer) : Enemy(89,107)
{
	mpGame = pGame ;
	mpPlayer = pPlayer;
	mCurrentColumn = 0 ;
	mCurrentRow = 0;
	mFrameRate = .030f;
	mVelocity = 50.f ;
	mFrameCounter = 0.f ;
	mHealth = 100 ;
	misAlive = true ;
	misShutDown = false; 
    mSpriteRect.width = mWidth;
    mSpriteRect.height = mHeight;
    mSprite.setPosition(sf::Vector2f(400.f, -400.f));
}


Baldus::~Baldus()
    {}
void Baldus::Update(const sf::Time& deltaFrame)
    {
    Animation(deltaFrame);
    Movement(deltaFrame);
    }

void Baldus::SetTexture(const sf::Texture& tex)
    {
    mSprite.setTexture(tex);
    }
const sf::Sprite& Baldus::GetSprite() const
    {
    return mSprite;
    }






void Baldus::Movement(const sf::Time& deltaFrame)
    {
    sf::Vector2f newPos = mSprite.getPosition();
    sf::Vector2f chaseDirection(mpPlayer->GetSprite().getPosition() - newPos);
	//TODO: chaseDirection must be normalized before it gets added to newPos in line 56, write a own normalize-function!
	Normalize(chaseDirection);
    //bind movement to player-speed
    newPos.y += ( -mpPlayer->mVelocity.y) * deltaFrame.asSeconds();
    newPos.x += ( -mpPlayer->mVelocity.x) * deltaFrame.asSeconds() * 0.2f; //x-movement of stars 5x slower than y-movement

    //chase player
	newPos += (chaseDirection * deltaFrame.asSeconds()) * (float)150;
	
    mSprite.setPosition(newPos);
    }

bool Baldus::shutDown(){ return misShutDown; }
void Baldus::Animation(const sf::Time& deltaFrame)
    {
        //Animation related
        //------------------------------------------
	
	if (!misAlive)
	{
		//Destroy Sequence; 


		mFrameCounter += deltaFrame.asSeconds();

		if (mFrameCounter > mFrameRate)
		{
			++mCurrentColumn;
			//4
			if (mCurrentColumn >= 4)
			{
				mCurrentColumn = 0;
				++mCurrentRow;
			}			//1
			if (mCurrentRow > 3)
			{
				mCurrentColumn = 0;
				misShutDown = true; //if end of animation, kill sprite
			}
			mFrameCounter = 0;


		}
	}
	else
		{


			//at end of Sequence, destroy ship
			//misShutDown = true; 
			//end of isAlive

			mFrameCounter += deltaFrame.asSeconds();

			if (mFrameCounter > mFrameRate)
				{
					++mCurrentColumn;
					//4
					if (mCurrentColumn >= 4)
					{
						mCurrentColumn = 0;
						++mCurrentRow;
					}			//1
					if (mCurrentRow > 1)
					{
						mCurrentColumn = 0;
						mCurrentRow = 0;
					}
					mFrameCounter = 0;
				}
			
		} // end of else-statement
	mSprite.setTextureRect(sf::IntRect(mCurrentColumn * mWidth, mCurrentRow *mHeight, mWidth, mHeight));
   }

void Baldus::HitPoint(int damageRate)
	{
	int result = mHealth - damageRate;
	if (result <= 0)
		{
		mHealth = 0;
		misAlive = false;
		}
	else
		{
		mHealth = result;
		}
	}

bool Baldus::isAlive(){ return misAlive;  }
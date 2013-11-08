#include "GameState.h"
#include "Game.h"
#include <iostream>
#include <memory>
#include "StringUtilities.h"

//TODO: can I initialize entities-vector with default size like 200 star-entities and set all to nullptr? like entities[200, nullptr]
GameState::GameState( Game * pGame)
	:
    mpGame( pGame ),
	mPlayer( nullptr ),
    mAmbulance( nullptr),
    mState(State::Game)
	{
    mPlayer = std::shared_ptr<Player>( new Player(mpGame, this) );
	mPlayer->SetTexture( mpGame->mPlayerTexture );

	mAmbulance = std::shared_ptr<Ambulance>(new Ambulance(mpGame, mPlayer.get()) );
	mAmbulance->SetTexture(mpGame->mAmbulanceTexture);

    mBaldus = std::shared_ptr<Baldus>(new Baldus(mpGame, mPlayer.get() ) );
    mBaldus->SetTexture(mpGame->mBaldusTexture);

	//initialize stars;
    for(int i = 0; i < mpGame->mConfig.GetStarAmount(); ++i)
		{
        sptr_Entity star( new Star(pGame, mPlayer) );
		star->SetTexture( mpGame->mStarTexture );
		entities.push_back( std::move(star) );
		}
    //initialize BackgroundPicture
	mBackground = std::unique_ptr<Background>( new Background(mpGame) );
	mBackground->SetTexture( mpGame->mBackgroundTexture );

	/*string file = "..\\Resources\\Audio\\first_run_jingle.ogg";
	mpGame->mAudioMan.LoadAndPlayMusic( ToPlatformPath(file) );
*/
    }

GameState::~GameState()
	{
	std::cout << "Destroying GameState\n";
	}

void GameState::Update( const sf::Time& deltaFrame )
	{
    for( sptr_Entity& i : entities )
		{
		i->Update( mpGame->mFrameDelta );
		}

    for(auto i = laserShots.begin(); i != laserShots.end();)
        {
        i->Update(mpGame->mFrameDelta);
		//if baldus exists
		if (mBaldus)
			{
			//and got hit by laser 
			if (i->GetSprite().getGlobalBounds().intersects(mBaldus->GetSprite().getGlobalBounds()))
				{
					//TODO: Enemy got hit
				mBaldus->HitPoint(mPlayer->getDamageBoost());

				std::swap(*i, laserShots.back());
				laserShots.pop_back();
				break;
				}
			}
         if(i->GetSprite().getPosition().y < -200)
            {
             std::swap(*i, laserShots.back());
             laserShots.pop_back();
             break;
            }
         else
         {
             ++i;
         }

        }

	if ( mPlayer )
		mPlayer->Update( mpGame->mFrameDelta );

	if ( mAmbulance )
		mAmbulance->Update( mpGame->mFrameDelta );

    if(mBaldus)
        {
        mBaldus->Update((mpGame->mFrameDelta));
		if (mBaldus->shutDown())
			{
			mBaldus.reset();
			}
        }

	if ( mPlayer )
		{
		sf::Vector2f playerPos( mPlayer->GetSprite().getPosition() );
		mpGame->mAudioMan.SetListenerPosition( playerPos.x, playerPos.y, 0.0f );
		}


    //Clean Up if needed;
	}



void GameState::Render()
	{
	mpGame->mRenderWindow.clear( sf::Color::Black );
		//first draw background, than everything else
	mpGame->mRenderWindow.draw( mBackground->GetSprite() );

    for( sptr_Entity& i : entities )
		{
		mpGame->mRenderWindow.draw( i->GetSprite() );
		}

    for (Laser& i : laserShots)
        {
        mpGame->mRenderWindow.draw(i.GetSprite());
        }

	if ( mPlayer )
		mpGame->mRenderWindow.draw( mPlayer->GetSprite() );

	if ( mAmbulance )
		mpGame->mRenderWindow.draw( mAmbulance->GetSprite() );

    if( mBaldus)
        {
        mpGame->mRenderWindow.draw(mBaldus->GetSprite());
        }

	mpGame->mRenderWindow.display();

	}

const State GameState::GetStateInput()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                return State::Menu;
            }

        return mResumedGame ? State::Resume : State::Game;

    }


void GameState::SetResumeProperty(bool resume)
    {
    mResumedGame = resume;
    }


void GameState::ShootLaser(bool leftSide, Weapon weapon)
    {
    Laser shot(mPlayer.get(),leftSide, weapon);
    shot.SetTexture(mpGame->mLaserTexture);
    laserShots.push_back(shot);
    }

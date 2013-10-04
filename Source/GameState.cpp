#include "GameState.h"
#include "Game.h"
#include <iostream>
#include "StringUtilities.h"
//TODO: can I initialize entities-vector with default size like 200 star-entities and set all to nullptr? like entities[200, nullptr]
GameState::GameState( Game * pGame)
	:
    mpGame( pGame ),
	mPlayer( nullptr ),
    mAmbulance( nullptr),
    mState(State::Game)
	{
	mPlayer = std::shared_ptr<Player>( new Player(mpGame) );
	mPlayer->SetTexture( mpGame->mPlayerTexture );

	mAmbulance = std::shared_ptr<Ambulance>(new Ambulance(mpGame, mPlayer.get()) );
	mAmbulance->SetTexture(mpGame->mAmbulanceTexture);

	//initialize stars;
	for(int i = 0; i < 150; ++i)
		{
		sptr_entity star( new Star(pGame, mPlayer) );
		star->SetTexture( mpGame->mStarTexture );
		entities.push_back( std::move(star) );
		}

	mBackground = std::unique_ptr<Background>( new Background(mpGame) );
	mBackground->SetTexture( mpGame->mBackgroundTexture );

	string file = "..\\Resources\\Audio\\first_run_jingle.ogg";
	mpGame->mAudioMan.LoadAndPlayMusic( ToPlatformPath(file) );

	//_background->_sprite.setScale((16/9), (16/9));
	}

GameState::~GameState()
	{
	std::cout << "Destroying GameState\n";
	}

void GameState::Update( const sf::Time& deltaFrame )
	{
	for( sptr_entity& i : entities )
		{
		i->Update( mpGame->mFrameDelta );
		}

	if ( mPlayer )
		mPlayer->Update( mpGame->mFrameDelta );

	if ( mAmbulance )
		mAmbulance->Update( mpGame->mFrameDelta );

	if ( mPlayer )
		{
		sf::Vector2f playerPos( mPlayer->GetSprite().getPosition() );
		mpGame->mAudioMan.SetListenerPosition( playerPos.x, playerPos.y, 0.0f );
		}
	}



void GameState::Render()
	{
	mpGame->mRenderWindow.clear( sf::Color::Black );
		//first draw background, than everything else
	mpGame->mRenderWindow.draw( mBackground->GetSprite() );

	for( sptr_entity& i : entities )
		{
		mpGame->mRenderWindow.draw( i->GetSprite() );
		}

	if ( mPlayer )
		mpGame->mRenderWindow.draw( mPlayer->GetSprite() );

	if ( mAmbulance )
		mpGame->mRenderWindow.draw( mAmbulance->GetSprite() );

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

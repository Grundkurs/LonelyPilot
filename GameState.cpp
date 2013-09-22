#include "GameState.h"
#include "Game.h"
#include <iostream>

//TODO: can I initialize entities-vector with default size like 200 star-entities and set all to nullptr? like entities[200, nullptr]
GameState::GameState( Game* game ) 
: mpGame( game ),
mPlayer( nullptr )

{ 
	mPlayer = std::shared_ptr<Player>( new Player(mpGame) );
	mPlayer->SetTexture( mpGame->mPlayerTexture );

	//initialize stars; 
	for(int i = 0; i < 150; ++i)
	{										//little offset so when player move to right side there are still stars
       //create new star
        sptr_entity star( new Star(game, mPlayer) );
		star->SetTexture( mpGame->mStarTexture );
		entities.push_back( std::move(star) );
	}
	//menuManager = std::unique_ptr<MenuManager>(new MenuManager(this));
	
	entities.push_back( std::move(mPlayer) );
	
	mBackground = std::unique_ptr<Background>( new Background(mpGame) );
	mBackground->SetTexture( mpGame->mBackgroundTexture );
	
	//_background->_sprite.setScale((16/9), (16/9)); 
}

GameState::~GameState(){
	std::cout << "Destroying GameState\n";
}

void GameState::Update( const sf::Time& deltaFrame )
{
	
    for( sptr_entity& i : entities )
	{
		i->Update( mpGame->mFrameDelta ); 
	}
	
}



void GameState::Render(){
	
		mpGame->mRenderWindow.clear( sf::Color::Black );
		//first draw background, than everything else
		mpGame->mRenderWindow.draw( mBackground->GetSprite() );
		
        for( sptr_entity& i : entities )
		{
			mpGame->mRenderWindow.draw( i->GetSprite() );
		}
		mpGame->mRenderWindow.display(); 	
}

IState* GameState::ProcessStateInput( const sf::Event& event )
{
	if(sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
	{
		mpGame->mSwitchStateInput.reset(); 
		return new MenuState( mpGame ); 
	}
	return this; 
}

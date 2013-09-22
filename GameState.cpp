#include "GameState.h"
#include "Game.h"
#include <iostream>

//TODO: can I initialize entities-vector with default size like 200 star-entities and set all to nullptr? like entities[200, nullptr]
GameState::GameState( Game* game ) 
: _game( game ),
mPlayer( nullptr )

{ 
	mPlayer = std::shared_ptr<Player>( new Player(_game) );
	mPlayer->SetTexture( _game->_playerTexture );

	//initialize stars; 
	for(int i = 0; i < 150; ++i){										//little offset so when player move to right side there are still stars
       //create new star
        sptr_entity star( new Star(game,_game->_randomNumGenerator, mPlayer) );
		star->SetTexture( _game->_starTexture );
		entities.push_back( std::move(star) );
	}
	//menuManager = std::unique_ptr<MenuManager>(new MenuManager(this));
	
	entities.push_back( std::move(mPlayer) );
	
	mBackground = std::unique_ptr<Background>( new Background(_game) );
	mBackground->SetTexture( _game->_backgroundTexture );
	
	//_background->_sprite.setScale((16/9), (16/9)); 
}

GameState::~GameState(){
	std::cout << "Destroying GameState\n";
}

void GameState::Update( const sf::Time& deltaFrame )
{
	
    for( sptr_entity& i : entities )
	{
		i->Update( _game->_frame_delta ); 
	}
	
}



void GameState::Render(){
	
		_game->renderWindow.clear( sf::Color::Black );
		//first draw background, than everything else
		_game->renderWindow.draw( mBackground->GetSprite() );
		
        for( sptr_entity& i : entities )
		{
			_game->renderWindow.draw( i->GetSprite() );
		}
		_game->renderWindow.display(); 	
}

IState* GameState::ProcessStateInput( const sf::Event& event )
{
	if(sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
	{
		_game->_switchStateInput.reset(); 
		return new MenuState( _game ); 
	}
	return this; 
}

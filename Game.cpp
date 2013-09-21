#include "Game.h"


Game::Game( int width, int height ) 
	:
    renderWindow( sf::VideoMode(width, height), "Space Game Shooter v1.0" ),
	_width( width ),
	_height( height ),
	_currentState( new MenuState(this) ),
	_previousState( _currentState ),
	_switchStateInput( .05f )

{
	//start Clock; 
	_start_time.restart(); 
}

Game::~Game()
{
	if( _currentState )
	{
		delete _currentState;
	}
}


bool Game::Initialize()
{	
	if( !renderWindow.isOpen() ){
		std::cout << "could not open RenderWindow\n"; 
		return false; 
	}
		std::cout << "RenderWindow opened successfully\n"; 

		if( !_starTexture.loadFromFile("..\\Art\\Visual\\Star.png") )
		{
			std::cout << "error loading Star-Texture\n"; 
			return false; 
		}
		std::cout << "Star loaded successfully\n"; 

		if( !_playerTexture.loadFromFile("..\\Art\\Visual\\PlayerSheet.png") )
		{
			std::cout << "error loading player-Texture\n"; 
			return false; 
		}
		std::cout << "player-Texture loaded successfully\n"; 

		if( !_backgroundTexture.loadFromFile("..\\Art\\Visual\\StarBackground1024x768.jpg") )
		{
			std::cout << "error loading Background-Texture\n"; 
			return false;
		}
		std::cout << "Background-Texture loaded successfully\n";

	return true; 
}

int Game::Run()
{
	sf::Time lastTime = _start_time.getElapsedTime();
	sf::Time currentTime; 
	
	//main Program-Loop
	while( renderWindow.isOpen() )
	{
		currentTime = _start_time.getElapsedTime(); 
		_frame_delta = currentTime - lastTime; 
		lastTime = currentTime; 
	

		ProcessHandle(); 
		_currentState->Update(_frame_delta); 
		_currentState->Render(); 

	}
	return 0; 
}

void Game::ProcessHandle()
{
	_switchStateInput.process( _frame_delta ); 
	//_press_Button_Trigger += _frame_delta.asSeconds();  

	sf::Event event;
	
		while( renderWindow.pollEvent(event) ){
			//Global inputs
			if(event.type == sf::Event::Closed){
				renderWindow.close(); 
			}




			if( _switchStateInput.canChange() )
			{
				//Input commands depends on current State
				_currentState = _currentState->ProcessStateInput(event); 
				if( _currentState != _previousState )
				{
					delete _previousState; 
					_previousState = _currentState; 
				}
			}
			
		}//end of renderWindow.pollEvent

} //end of ProcessHandle

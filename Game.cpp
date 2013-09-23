#include "Game.h"


Game::Game( int width, int height ) 
	:
    mRenderWindow( sf::VideoMode(width, height), "Space Game Shooter v1.0" ),
	mWidth( width ),
	mHeight( height ),
	mpCurrentState( new MenuState(this) ),
	mpPreviousState( mpCurrentState ),
	mSwitchStateInput( .05f )
	{
	//start Clock; 
	mStartTime.restart(); 
	}

Game::~Game()
	{
	if( mpCurrentState )
		{
		delete mpCurrentState;
		}
	}


bool Game::Initialize()
{	
	if( !mRenderWindow.isOpen() )
		{
		std::cout << "could not open mRenderWindow\n"; 
		return false; 
		}

		std::cout << "mRenderWindow opened successfully\n"; 

		if( !mStarTexture.loadFromFile("..\\Art\\Visual\\Star.png") )
			{
			std::cout << "error loading Star-Texture\n"; 
			return false; 
			}

		std::cout << "Star loaded successfully\n"; 

		if( !mPlayerTexture.loadFromFile("..\\Art\\Visual\\PlayerSheet.png") )
			{
			std::cout << "error loading player-Texture\n"; 
			return false; 
			}

		std::cout << "player-Texture loaded successfully\n"; 

		if( !mBackgroundTexture.loadFromFile("..\\Art\\Visual\\StarBackground1024x768.jpg") )
			{
			std::cout << "error loading Background-Texture\n"; 
			return false;
			}
		std::cout << "Background-Texture loaded successfully\n";

		if( !mAmbulanceTexture.loadFromFile("..\\Art\\Visual\\Ambulance.png") )
			{
				std::cout << "error loading Ambulance-Texture!"; 
			}
		std::cout << "successfully loaded ambulance-Texture!\n"; 

	return true; 
	}

int Game::Run()
	{
	sf::Time lastTime = mStartTime.getElapsedTime();
	sf::Time currentTime; 
	
	//main Program-Loop
	while( mRenderWindow.isOpen() )
		{
		currentTime = mStartTime.getElapsedTime(); 
		mFrameDelta = currentTime - lastTime; 
		lastTime = currentTime; 
	

		ProcessHandle(); 
		mpCurrentState->Update(mFrameDelta); 
		mpCurrentState->Render(); 

		}
	return 0;
	}

void Game::ProcessHandle()
{
	mSwitchStateInput.process( mFrameDelta ); 
	//_press_Button_Trigger += mFrameDelta.asSeconds();  

	sf::Event event;
	
		while( mRenderWindow.pollEvent(event) ){
			//Global inputs
			if(event.type == sf::Event::Closed){
				mRenderWindow.close(); 
			}




			if( mSwitchStateInput.canChange() )
			{
				//Input commands depends on current State
				mpCurrentState = mpCurrentState->ProcessStateInput(event); 
				if( mpCurrentState != mpPreviousState )
				{
					delete mpPreviousState; 
					mpPreviousState = mpCurrentState; 
				}
			}
			
		}//end of mRenderWindow.pollEvent

} //end of ProcessHandle

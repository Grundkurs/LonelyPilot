#include "Game.h"

#include "RandomGenerator.h"
#include "StringUtilities.h"


Game::Game()
	:
	mRenderWindow( ),
    uPtr_CurrentState( nullptr ),
    mCurrState(State::Menu),
	mAudioMan()
	{
	//start Clock;
	mStartClock.restart();
	Random::Seed();
    mOldState = mCurrState;
    uPtr_CurrentState.reset(new MenuState(this));
	}

Game::~Game()
	{

	}


bool Game::Initialize()
	{
	string file("../Resources/Scripts/chrisSettings.xml");

	if ( !mConfig.LoadFromFile( ToPlatformPath(file) ) )
		{//this message is redunant since the LoadFromFile will print error message
		std::cout << "Failed to load config";
		return false;
		}

	mRenderWindow.create(sf::VideoMode(mConfig.GetScreenWidth(), mConfig.GetScreenHeight()), mConfig.GetWindowTitle() );
	mRenderWindow.display();

	if( !mRenderWindow.isOpen() )
		{
		std::cout << "could not open mRenderWindow\n";
		return false;
		}

	std::cout << "mRenderWindow opened successfully\n";

    //file = ("..\\Resources\\Visual\\Star.png");
    file = mConfig.GetStarTexPath();
	if( !mStarTexture.loadFromFile(ToPlatformPath(file)) )
		{
		std::cout << "error loading Star-Texture\n";
		return false;
		}

	std::cout << "Star loaded successfully\n";

    //file = "..\\Resources\\Visual\\PlayerSheet2.png";
    file = mConfig.GetPlayerTexPath();
    if( !mPlayerTexture.loadFromFile(ToPlatformPath(file)) )
		{
		std::cout << "error loading player-Texture\n";
		return false;
		}

	std::cout << "player-Texture loaded successfully\n";

	file = "..\\Resources\\Visual\\StarBackground1024x768.jpg";
	if( !mBackgroundTexture.loadFromFile(ToPlatformPath(file)) )
		{
		std::cout << "error loading Background-Texture\n";
		return false;
		}
	std::cout << "Background-Texture loaded successfully\n";

	file = "..\\Resources\\Visual\\Ambulance.png";
	if( !mAmbulanceTexture.loadFromFile(ToPlatformPath(file)) )
		{
		std::cout << "error loading Ambulance-Texture!";
		}
	std::cout << "successfully loaded ambulance-Texture!\n";

    uPtr_CurrentState.reset(new MenuState(this));

	return true;
	}

int Game::Run()
	{
	mFrameStamp = mStartClock.getElapsedTime();

	//main Program-Loop
	while( mRenderWindow.isOpen() )
		{
		sf::Time currentTime = mStartClock.getElapsedTime();
		mFrameDelta = currentTime - mFrameStamp;
		mFrameStamp = currentTime;

		ProcessHandle();
        uPtr_CurrentState->Update(mFrameDelta);
        uPtr_CurrentState->Render();

		mAudioMan.Update();
		}
	return 0;
	}

void Game::ProcessHandle()
	{

    mInputInterval.Update(mFrameDelta);
	//_press_Button_Trigger += mFrameDelta.asSeconds();

	sf::Event event;

	while( mRenderWindow.pollEvent(event) )
		{
		//Global inputs
		if(event.type == sf::Event::Closed)
			{
			mRenderWindow.close();
			}

        if(mInputInterval.CanPressButton())
           {
            mCurrState = uPtr_CurrentState->GetStateInput();
           if(mCurrState != mOldState)
               {
               mInputInterval.Reset();
               mOldState = mCurrState;
               switch (mCurrState)
                    {
                     case (State::Game):
                         {
                         if(uPtr_CurrentState)
                            {
                             uPtr_CurrentState.reset(nullptr);
                             uPtr_CurrentState.reset(new GameState(this));
                             }
                         break;
                         }
                     case (State::Menu):
                         {
                         if(uPtr_CurrentState)
                             {
                             uPtr_CurrentState.reset(nullptr);
                             uPtr_CurrentState.reset(new MenuState(this));
                             }
                         break;
                         }
                    case (State::Options):
                        {
                        uPtr_CurrentState.reset(nullptr);
                        uPtr_CurrentState.reset(new OptionState(this));
                        break;
                        }

                       } //end of switch
                   }
            }



		}//end of mRenderWindow.pollEvent

	} //end of ProcessHandle

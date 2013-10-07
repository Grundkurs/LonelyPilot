#include "Game.h"

#include "RandomGenerator.h"
#include "StringUtilities.h"


Game::Game()
	:
	mRenderWindow( ),
    mCurrState(State::Menu),
    mAudioMan(),
    uPtr_CurrentState(nullptr),
    uPtr_RunningState(nullptr)
	{
	//start Clock;
	mStartClock.restart();
	Random::Seed();
    mOldState = mCurrState;
	}

Game::~Game()
	{
    }


bool Game::Initialize()
	{
    string file("..\\Resources\\Scripts\\Settings.xml");

	if ( !mConfig.LoadFromFile( ToPlatformPath(file) ) )
        {
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
            mCurrState = uPtr_CurrentState->GetStateInput(); //get global State-Input

            if(mCurrState != mOldState) //if State changed, check...
               {
               mInputInterval.Reset();

               switch (mCurrState)
                    {
                     case (State::Game):
                         {
                        uPtr_CurrentState.reset();
                        uPtr_CurrentState = std::shared_ptr<IState>(new GameState(this));
                        uPtr_CurrentState->SetResumeProperty(false);
                        uPtr_RunningState = uPtr_CurrentState;


                         break;
                         }

                     case(State::Resume):
                           {
                            uPtr_CurrentState.reset(); //because CurrentState will here always be MenuState, you can delete it

                            //set GameState stored in RunningState-Pointer to Resume, so next cycle it returns
                            //State::Resume instead of State::Game, which would otherwise create a new GameState. Because
                            //this doesnt happen and mOldState stays same as mCurrentState, switch-statement will not be invoked
                            //and CurrentState that is set to the stored/old GameState will be updated and rendered
                            uPtr_RunningState->SetResumeProperty(true);

                            uPtr_CurrentState = uPtr_RunningState;    //assign it to currentState.



                           break;
                           }

                     case (State::Menu):
                         {
                        if(mOldState == State::Game)
                            {
                            uPtr_CurrentState = std::shared_ptr<IState>(new MenuState(this));
                            break;
                            }
                        uPtr_CurrentState.reset();
                        uPtr_CurrentState = std::shared_ptr<IState>(new MenuState(this));
                        break;

                         }
                    case (State::Options):
                        {

                         uPtr_CurrentState.reset();
                         uPtr_CurrentState = std::shared_ptr<IState>(new OptionState(this));
                         break;
                        }

                      } //end of switch
                     mOldState = mCurrState;
                   }
            }



		}//end of mRenderWindow.pollEvent

	} //end of ProcessHandle

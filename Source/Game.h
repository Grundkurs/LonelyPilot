#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include "IState.h"
#include "GameState.h"
#include "MenuState.h"
#include "RandomNumberGenerator.h"
#include "AudioManager.h"

#include <iostream>


class SwitchStateInput
{
private:
	float mPress_Button_Trigger;
	const float PRESS_RELEASE_TIME;
public:
	SwitchStateInput(float pressRelease)
		:
		PRESS_RELEASE_TIME(pressRelease),
		mPress_Button_Trigger(0.f)
		{}

	void process(const sf::Time& frameDelta)
		{
		mPress_Button_Trigger += frameDelta.asSeconds();
		}

	void reset()
		{
		mPress_Button_Trigger = 0.f;
		}

	bool canChange()
		{
		if(mPress_Button_Trigger > PRESS_RELEASE_TIME)
			{
			return true;
			}
		return false;
		}
};

class Game
{								//private copy constructor, prevents that Game can be copied
								Game(const Game& game);
public:
								Game(int width, int height);
								~Game(void);

		bool					Initialize();
		int						Run();
		void					ProcessHandle();


		//Fields
		RandomNumberGenerator	mRandomNumGenerator;
		int						mWidth, mHeight;
		sf::Clock				mStartClock;
		sf::Time				mFrameDelta;
		sf::Time				mFrameStamp;

		SwitchStateInput		mSwitchStateInput;

		sf::RenderWindow		mRenderWindow;
		//IState*					mpCurrentState;
		//IState*					mpPreviousState;
		std::unique_ptr<IState> mpCurrentState;


		sf::Texture				mStarTexture;
		sf::Texture				mPlayerTexture;
		sf::Texture				mBackgroundTexture;
		sf::Texture				mAmbulanceTexture;

		AudioManager mAudioMan;
};
#endif //GAME_H
